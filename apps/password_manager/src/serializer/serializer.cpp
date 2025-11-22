//  Copyright © 2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#include "serializer.hpp"
#include "creditcardtype.hpp"
#include "exceptions.hpp"
#include "field.hpp"
#include "localdate.hpp"
#include "uuid.hpp"
#include "version.hpp"
#include "xsd_schema.h"
#include <memory>
#include <string>
#include <vector>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMNode.hpp>
#include <xercesc/framework/MemBufFormatTarget.hpp>
#include <xercesc/framework/MemBufInputSource.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/Xerces_autoconf_config.hpp>

using namespace xercesc;

namespace {

template <typename T>
auto autoReleased(T *p) {
    return std::unique_ptr<T, void (*)(T *)>{p, [](auto *ptr) {
                                                 ptr->release();
                                             }};
}

struct AutoReleasedXmlCh {
    XMLCh *data_;
    bool autoRelease_;

    AutoReleasedXmlCh(XMLCh *data, bool autoRelease = true) : data_{data}, autoRelease_{autoRelease} {}
    ~AutoReleasedXmlCh() {
        if (autoRelease_) {
            XMLString::release(&data_);
        }
    }
};

std::string toUtf8(const XMLCh *str) {
    auto utf8 = XMLString::transcode(str);
    std::string result{utf8};
    XMLString::release(&utf8);
    return result;
}

AutoReleasedXmlCh toXmlCh(const std::string &str) {
    return AutoReleasedXmlCh(XMLString::transcode(str.c_str()));
}

class PasswordManagerErrorHandler : public DefaultHandler {
  public:
    void fatalError(const SAXParseException &exc) override { handle(exc); }
    void error(const SAXParseException &exc) override { handle(exc); }
    void warning(const SAXParseException &exc) override { handle(exc); }

  private:
    void handle(const SAXParseException &exc) { throw PasswordManagerException(exc.getMessage()); }
};

const XMLCh *WALLET{u"wallet"};
const XMLCh *RECORDS{u"records"};

const XMLCh *IMPL{u"LS"};

const XMLCh *RECORD{u"record"};

const XMLCh *ELEMENT_FIELDS{u"fields"};
const XMLCh *ELEMENT_FIELD{u"field"};
const XMLCh *ELEMENT_NOTE{u"note"};

const XMLCh *ATTR_VERSION{u"version"};
const XMLCh *ATTR_RECORD_CLASS{u"recordClass"};
const XMLCh *ATTR_UUID{u"uuid"};
const XMLCh *ATTR_NAME{u"name"};
const XMLCh *ATTR_MODIFIED{u"modified"};
const XMLCh *ATTR_FAVORITE{u"favorite"};
const XMLCh *ATTR_ACTIVE{u"active"};
const XMLCh *ATTR_PICTURE{u"picture"};
const XMLCh *ATTR_TYPE{u"type"};
const XMLCh *ATTR_VALUE{u"value"};

AutoReleasedXmlCh fieldValueToString(const Field &field) {
    const auto &value = field.value();
    const auto &type = field.type();

    if (type == FieldType::DATE || type == FieldType::EXPIRATION_MONTH) {
        auto &date = std::get<std::chrono::year_month_day>(value);
        const auto &formatted = LocalDate::toIsoString(date);
        return XMLString::transcode(formatted.c_str());
    } else if (type == FieldType::CARD_TYPE) {
        auto ordinal = std::get<unsigned int>(value);
        auto &creditCardType = CreditCardType::valueOf(ordinal);
        return XMLString::transcode(creditCardType.name().c_str());
    } else {
        return AutoReleasedXmlCh{const_cast<XMLCh *>(field.valueAsString().c_str()), false};
    }
}

Field::FieldValue deserializeFieldValue(const XMLCh *str, const FieldType &type) {
    if (type == FieldType::DATE || type == FieldType::EXPIRATION_MONTH || type == FieldType::CARD_TYPE) {
        auto utf8 = toUtf8(str);
        if (type == FieldType::CARD_TYPE) {
            return utf8.empty() ? CreditCardType::OTHER.ordinal() : CreditCardType::valueOf(utf8).ordinal();
        } else {
            if (utf8.empty()) {
                return LocalDate::now();
            }
            auto date = LocalDate::fromIsoString(utf8);
            return date.ok() ? date : LocalDate::now();
        }
    } else {
        return str;
    }
}

const XMLCh *getRawAttribute(const DOMNamedNodeMap *attributes, const XMLCh *name) {
    auto node = attributes->getNamedItem(name);
    return node == nullptr ? nullptr : node->getNodeValue();
}

std::string getString8Attribute(const DOMNamedNodeMap *attributes, const XMLCh *name,
                                const std::string_view &defaultValue) {
    auto value = getRawAttribute(attributes, name);
    if (value == nullptr) {
        return std::string{defaultValue};
    }

    return toUtf8(value);
}

std::u16string getString16Attribute(const DOMNamedNodeMap *attributes, const XMLCh *name,
                                    const std::u16string &defaultValue) {
    auto value = getRawAttribute(attributes, name);
    if (value == nullptr) {
        return defaultValue;
    }

    return value;
}

UUID::UUID getUuidAttribute(const DOMNamedNodeMap *attributes, const XMLCh *name) {
    auto value = getRawAttribute(attributes, name);
    if (value == nullptr) {
        return UUID::randomUuid();
    }

    auto utf8 = toUtf8(value);
    return UUID::fromStdString(utf8);
}

long getLongAttribute(const DOMNamedNodeMap *attributes, const XMLCh *name, long defaultValue) {
    auto value = getRawAttribute(attributes, name);
    if (value == nullptr) {
        return defaultValue;
    }

    try {
        auto utf8 = toUtf8(value);
        return std::stol(utf8);
    } catch (...) {
        return defaultValue;
    }
}

bool getBoolAttribute(const DOMNamedNodeMap *attributes, const XMLCh *name, bool defaultValue) {
    auto stringValue = ::getString8Attribute(attributes, name, std::to_string(defaultValue));
    return stringValue == "true";
}

void deserializeField(const DOMElement *fieldElement, std::vector<Field> &fields) {
    auto attrs = fieldElement->getAttributes();

    auto &fieldType = FieldType::valueOf(::getString8Attribute(attrs, ATTR_TYPE, "STRING"));
    auto name = ::getString16Attribute(attrs, ATTR_NAME, u"");
    auto value = deserializeFieldValue(getRawAttribute(attrs, ATTR_VALUE), fieldType);
    fields.emplace_back(fieldType, name, value);
}

void deserializeCard(const DOMElement *cardElement, std::vector<Card> &cards) {
    auto attrs = cardElement->getAttributes();

    auto &cardClass = CardClass::valueOf(::getString8Attribute(attrs, ATTR_RECORD_CLASS, "CARD"));

    auto uuid = ::getUuidAttribute(attrs, ATTR_UUID);
    auto name = ::getString16Attribute(attrs, ATTR_NAME, u"");
    if (name.empty()) {
        throw PasswordManagerException(u"Mandatory attribute name is missing");
    }

    auto &picture = Picture::valueOf(::getString8Attribute(attrs, ATTR_PICTURE, "GENERIC"));
    auto modified = ::getLongAttribute(attrs, ATTR_MODIFIED, 0L);
    bool favorite = ::getBoolAttribute(attrs, ATTR_FAVORITE, false);
    auto active = ::getBoolAttribute(attrs, ATTR_ACTIVE, true);

    // Deserialize fields
    auto fieldNodes = cardElement->getElementsByTagName(ELEMENT_FIELD);
    std::vector<Field> fields;
    fields.reserve(fieldNodes->getLength());
    for (XMLSize_t index = 0; index < fieldNodes->getLength(); ++index) {
        auto fieldElement = reinterpret_cast<DOMElement *>(fieldNodes->item(index));
        deserializeField(fieldElement, fields);
    }

    // Deserialize note
    std::u16string note;
    auto noteNodes = cardElement->getElementsByTagName(ELEMENT_NOTE);
    if (noteNodes != nullptr && noteNodes->getLength() != 0) {
        auto nodeElement = reinterpret_cast<DOMElement *>(noteNodes->item(0));
        note = nodeElement->getTextContent();
    }

    cards.emplace_back(cardClass, uuid, picture, name, modified, note, favorite, active, fields);
}

static void serializeField(DOMDocument *doc, DOMElement *parent, const Field &field) {
    auto fieldElement = doc->createElement(ELEMENT_FIELD);

    fieldElement->setAttribute(ATTR_NAME, field.name().c_str());
    fieldElement->setAttribute(ATTR_TYPE, toXmlCh(field.type().name()).data_);

    auto fieldValue = fieldValueToString(field);
    fieldElement->setAttribute(ATTR_VALUE, fieldValue.data_);

    parent->appendChild(fieldElement);
}

static void serializeCard(DOMDocument *doc, DOMElement *parent, const Card &card) {
    XMLCh buffer[10];

    auto record = doc->createElement(RECORD);
    parent->appendChild(record);

    // Attributes
    record->setAttribute(ATTR_RECORD_CLASS, toXmlCh(card.cardClass().name()).data_);
    record->setAttribute(ATTR_NAME, card.name().c_str());
    record->setAttribute(ATTR_UUID, toXmlCh(UUID::toStdString(card.uuid())).data_);
    record->setAttribute(ATTR_MODIFIED, toXmlCh(std::to_string(card.modified())).data_);
    record->setAttribute(ATTR_PICTURE, toXmlCh(card.picture().name()).data_);
    XMLString::transcode(card.favorite() ? "true" : "false", buffer, 9);
    record->setAttribute(ATTR_FAVORITE, buffer);
    XMLString::transcode(card.active() ? "true" : "false", buffer, 9);
    record->setAttribute(ATTR_ACTIVE, buffer);

    // Fields
    if (!card.fields().empty()) {
        auto fields = doc->createElement(ELEMENT_FIELDS);
        record->appendChild(fields);
        for (const auto &field : card.fields()) {
            serializeField(doc, fields, field);
        }
    }

    // Note
    auto note = doc->createElement(ELEMENT_NOTE);
    record->appendChild(note);

    note->setTextContent(card.note().c_str());
}

} // namespace

namespace Serializer {

void initialize() {
    xercesc::XMLPlatformUtils::Initialize();
}

void deserialize(const std::span<char> &content, std::vector<Card> &cards) {
    MemBufInputSource inputSource(reinterpret_cast<XMLByte *>(content.data()), content.size(), "bufferid");
    MemBufInputSource xsdInputSource(xsd::XSD_SCHEMA.bytes_, xsd::XSD_SCHEMA.size_, "xsd");

    XercesDOMParser parser;

    if (parser.loadGrammar(xsdInputSource, Grammar::GrammarType::SchemaGrammarType, true) == nullptr) {
        throw PasswordManagerException(u"Failed to load XSD schema");
    }

    ::PasswordManagerErrorHandler errorHandler;
    parser.setErrorHandler(&errorHandler);

    parser.setValidationScheme(XercesDOMParser::Val_Always);
    parser.setDoSchema(true);
    parser.setDoNamespaces(true);
    parser.useCachedGrammarInParse(true);
    parser.setValidationConstraintFatal(true);
    parser.setValidationSchemaFullChecking(true);

    parser.parse(inputSource);

    if (parser.getErrorCount() != 0) {
        throw PasswordManagerException(u"Error parsing document");
    }

    auto doc = parser.getDocument();
    auto root = doc->getDocumentElement();

    auto nodeList = root->getElementsByTagName(RECORD);
    XMLSize_t length = nodeList->getLength();
    cards.reserve(length);
    for (XMLSize_t i = 0; i < length; i++) {
        auto node = reinterpret_cast<DOMElement *>(nodeList->item(i));
        deserializeCard(node, cards);
    }
}

void serialize(const std::vector<Card> &list, std::vector<char> &byteArray) {
    try {
        auto impl = DOMImplementationRegistry::getDOMImplementation(IMPL);

        auto doc = ::autoReleased(impl->createDocument(nullptr, WALLET, nullptr));

        auto root = doc->getDocumentElement();
        root->setAttribute(ATTR_VERSION, toXmlCh(Version::projectVersion).data_);

        auto records = doc->createElement(RECORDS);
        root->appendChild(records);

        for (const auto &card : list) {
            serializeCard(doc.get(), records, card);
        }

        auto serializer = ::autoReleased(impl->createLSSerializer());
        auto output = ::autoReleased(impl->createLSOutput());

        auto target = MemBufFormatTarget();
        output->setByteStream(&target);

        serializer->write(doc.get(), output.get());

        auto bufferSize = target.getLen();
        byteArray.resize(bufferSize);
        std::memcpy(byteArray.data(), target.getRawBuffer(), bufferSize);
    } catch (const XMLException &ex) {
        throw PasswordManagerException(ex.getMessage());
    } catch (const DOMException &ex) {
        throw PasswordManagerException(ex.getMessage());
    } catch (...) {
        throw PasswordManagerException(u"Unknown exception while writing document");
    }
}

} // namespace Serializer
