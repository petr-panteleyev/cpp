//  Copyright © 2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#include "serializer.hpp"
#include "creditcardtype.hpp"
#include "exceptions.hpp"
#include "field.hpp"
#include "version.hpp"
#include <QDate>
#include <QFile>
#include <QString>
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

QString XtoQ(const XMLCh *x) {
    return QString::fromUtf16(x);
}

const XMLCh *QtoX(const QString &s) {
    return reinterpret_cast<const XMLCh *>(s.utf16());
}

class PasswordManagerErrorHandler : public DefaultHandler {
  public:
    void fatalError(const SAXParseException &exc) override { handle(exc); }
    void error(const SAXParseException &exc) override { handle(exc); }
    void warning(const SAXParseException &exc) override { handle(exc); }

  private:
    void handle(const SAXParseException &exc) { throw PasswordManagerException(XtoQ(exc.getMessage())); }
};

static const XMLCh *WALLET{u"wallet"};
static const XMLCh *RECORDS{u"records"};

static const XMLCh *IMPL{u"LS"};

static const XMLCh *RECORD{u"record"};

static const XMLCh *ELEMENT_FIELDS{u"fields"};
static const XMLCh *ELEMENT_FIELD{u"field"};
static const XMLCh *ELEMENT_NOTE{u"note"};

static const XMLCh *ATTR_VERSION{u"version"};
static const XMLCh *ATTR_RECORD_CLASS{u"recordClass"};
static const XMLCh *ATTR_UUID{u"uuid"};
static const XMLCh *ATTR_NAME{u"name"};
static const XMLCh *ATTR_MODIFIED{u"modified"};
static const XMLCh *ATTR_FAVORITE{u"favorite"};
static const XMLCh *ATTR_ACTIVE{u"active"};
static const XMLCh *ATTR_PICTURE{u"picture"};
static const XMLCh *ATTR_TYPE{u"type"};
static const XMLCh *ATTR_VALUE{u"value"};

// XSD schema buffer
static QByteArray XSD_SCHEMA;

static const XMLCh *fieldValueToString(const Field &field) {
    auto value = field.value();
    const auto &type = field.type();

    QString str;
    if (type == FieldType::DATE || type == FieldType::EXPIRATION_MONTH) {
        auto date = value.toDate();
        str = date.toString("yyyy-MM-dd");
    } else if (type == FieldType::CARD_TYPE) {
        auto ordinal = value.toUInt();
        auto &creditCardType = CreditCardType::valueOf(ordinal);
        str = QString::fromStdString(creditCardType.name());
    } else {
        str = value.toString();
    }
    return QtoX(str);
}

QString getStringAttribute(const DOMNamedNodeMap *attributes, const XMLCh *name, const QString &defaultValue) {
    auto node = attributes->getNamedItem(name);
    if (node == nullptr) {
        return defaultValue;
    }

    auto value = node->getNodeValue();
    if (value == nullptr) {
        return defaultValue;
    }

    return XtoQ(value);
}

QUuid getUuidAttribute(const DOMNamedNodeMap *attributes, const XMLCh *name) {
    auto node = attributes->getNamedItem(name);
    if (node == nullptr) {
        return QUuid::createUuid();
    }

    auto value = node->getNodeValue();
    if (value == nullptr) {
        return QUuid::createUuid();
    }

    return QUuid{XtoQ(value)};
}

long getLongAttribute(const DOMNamedNodeMap *attributes, const XMLCh *name, long defaultValue) {
    auto stringValue = ::getStringAttribute(attributes, name, QString::fromStdString(std::to_string(defaultValue)));
    bool ok;
    auto long_value = stringValue.toLong(&ok);
    return ok ? long_value : defaultValue;
}

bool getBoolAttribute(const DOMNamedNodeMap *attributes, const XMLCh *name, bool defaultValue) {
    auto stringValue = ::getStringAttribute(attributes, name, QString::fromStdString(std::to_string(defaultValue)));
    return stringValue == "true";
}

void deserializeField(const DOMElement *fieldElement, std::vector<Field> &fields) {
    auto attrs = fieldElement->getAttributes();

    auto fieldTypeStr = ::getStringAttribute(attrs, ATTR_TYPE, "STRING");
    auto &fieldType = FieldType::valueOf(fieldTypeStr.toStdString());

    auto name = ::getStringAttribute(attrs, ATTR_NAME, "");

    auto stringValue = ::getStringAttribute(attrs, ATTR_VALUE, "");
    QVariant value = Field::deserialize(stringValue, fieldType);

    fields.emplace_back(fieldType, name, value);
}

static void deserializeCard(const DOMElement *cardElement, std::vector<Card> &cards) {
    auto attrs = cardElement->getAttributes();

    auto cardClassAttr = ::getStringAttribute(attrs, ATTR_RECORD_CLASS, "CARD");
    auto &cardClass = CardClass::valueOf(cardClassAttr.toStdString());

    auto uuid = ::getUuidAttribute(attrs, ATTR_UUID);
    auto name = ::getStringAttribute(attrs, ATTR_NAME, "");
    if (name.isEmpty()) {
        throw PasswordManagerException("Mandatory attribute name is missing");
    }

    auto pictureStrValue = ::getStringAttribute(attrs, ATTR_PICTURE, "GENERIC");
    auto &picture = Picture::valueOf(pictureStrValue.toStdString());
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
    QString note;
    auto noteNodes = cardElement->getElementsByTagName(ELEMENT_NOTE);
    if (noteNodes != nullptr && noteNodes->getLength() != 0) {
        auto nodeElement = reinterpret_cast<DOMElement *>(noteNodes->item(0));
        note = XtoQ(nodeElement->getTextContent());
    }

    cards.emplace_back(cardClass, uuid, picture, name, modified, note, favorite, active, fields);
}

} // namespace

namespace Serializer {

void initialize() {
    xercesc::XMLPlatformUtils::Initialize();
    QString fileName(":/xsd/password-manager.xsd");
    QFile file(fileName);
    file.open(QIODeviceBase::ReadOnly);
    XSD_SCHEMA = file.readAll();
}

void deserialize(const std::span<char> &content, std::vector<Card> &cards) {
    MemBufInputSource inputSource(reinterpret_cast<XMLByte *>(content.data()), content.size(), "bufferid");
    MemBufInputSource xsdInputSource(reinterpret_cast<XMLByte *>(XSD_SCHEMA.data()), XSD_SCHEMA.size(), "xsd");

    XercesDOMParser parser;

    if (parser.loadGrammar(xsdInputSource, Grammar::GrammarType::SchemaGrammarType, true) == nullptr) {
        throw PasswordManagerException("Failed to load XSD schema");
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
        throw PasswordManagerException("Error parsing document");
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

static void serializeField(DOMDocument *doc, DOMElement *parent, const Field &field) {
    auto fieldElement = doc->createElement(ELEMENT_FIELD);

    fieldElement->setAttribute(ATTR_NAME, QtoX(field.name()));
    fieldElement->setAttribute(ATTR_TYPE, QtoX(QString::fromStdString(field.type().name())));
    fieldElement->setAttribute(ATTR_VALUE, fieldValueToString(field));

    parent->appendChild(fieldElement);
}

static void serializeCard(DOMDocument *doc, DOMElement *parent, const Card &card) {
    XMLCh buffer[10];

    auto record = doc->createElement(RECORD);
    parent->appendChild(record);

    // Attributes
    record->setAttribute(ATTR_RECORD_CLASS, QtoX(QString::fromStdString(card.cardClass().name())));
    record->setAttribute(ATTR_NAME, QtoX(card.name()));
    record->setAttribute(ATTR_UUID, QtoX(card.uuid().toString(QUuid::WithoutBraces)));
    record->setAttribute(ATTR_MODIFIED, QtoX(QString::number(card.modified())));
    record->setAttribute(ATTR_PICTURE, QtoX(QString::fromStdString(card.picture().name())));
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
    note->setTextContent(QtoX(card.note()));
}

void serialize(const std::vector<Card> &list, QByteArray &byteArray) {
    try {
        auto impl = DOMImplementationRegistry::getDOMImplementation(IMPL);

        auto doc = ::autoReleased(impl->createDocument(nullptr, WALLET, nullptr));

        auto root = doc->getDocumentElement();
        root->setAttribute(ATTR_VERSION, QtoX(QString::fromStdString(Version::projectVersion)));

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
        throw PasswordManagerException(XtoQ(ex.getMessage()));
    } catch (const DOMException &ex) {
        throw PasswordManagerException(XtoQ(ex.getMessage()));
    } catch (...) {
        throw PasswordManagerException("Unknown exception while writing document");
    }
}

} // namespace Serializer
