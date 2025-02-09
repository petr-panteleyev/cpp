//  Copyright © 2024-2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#include "serializer.h"
#include "cardclass.h"
#include "creditcardtype.h"
#include "exceptions.h"
#include "field.h"
#include "fieldtype.h"
#include "picture.h"
#include "version.h"
#include <QDate>
#include <QDomElement>
#include <QDomNamedNodeMap>
#include <QUuid>
#include <QXmlStreamWriter>

namespace Serializer {

static const QString RECORDS{"records"};

static const QString RECORD{"record"};

static const QString ELEMENT_FIELDS{"fields"};
static const QString ELEMENT_FIELD{"field"};
static const QString ELEMENT_NOTE{"note"};

static const QString ATTR_VERSION{"version"};
static const QString ATTR_RECORD_CLASS{"recordClass"};
static const QString ATTR_UUID{"uuid"};
static const QString ATTR_NAME{"name"};
static const QString ATTR_MODIFIED{"modified"};
static const QString ATTR_FAVORITE{"favorite"};
static const QString ATTR_ACTIVE{"active"};
static const QString ATTR_PICTURE{"picture"};
static const QString ATTR_TYPE{"type"};
static const QString ATTR_VALUE{"value"};

static QString getStringAttribute(const QDomNamedNodeMap &attributes, const QString &name,
                                  const QString &defaultValue) {
    if (attributes.contains(name)) {
        return attributes.namedItem(name).toAttr().value();
    } else {
        return defaultValue;
    }
}

static QUuid getUuidAttribute(const QDomNamedNodeMap &attributes, const QString &name) {
    if (attributes.contains(name)) {
        auto stringValue = attributes.namedItem(name).toAttr().value();
        return QUuid{stringValue};
    } else {
        return QUuid::createUuid();
    }
}

static long getLongAttribute(const QDomNamedNodeMap &attributes, const QString &name, long defaultValue) {
    if (attributes.contains(name)) {
        bool ok;
        auto long_value = attributes.namedItem(name).toAttr().value().toLong(&ok);
        return ok ? long_value : defaultValue;
    } else {
        return defaultValue;
    }
    return defaultValue;
}

static bool getBoolAttribute(const QDomNamedNodeMap &attributes, const QString &name, bool defaultValue) {
    if (attributes.contains(name)) {
        auto bool_value = attributes.namedItem(name).toAttr().value();
        return bool_value == "true";
    } else {
        return defaultValue;
    }
}

static Field deserializeField(const QDomElement &fieldElement) {
    auto attrs = fieldElement.attributes();

    auto fieldTypeStr = getStringAttribute(attrs, ATTR_TYPE, "STRING");
    auto &fieldType = FieldType::valueOf(fieldTypeStr.toStdString());

    auto name = getStringAttribute(attrs, ATTR_NAME, "");

    auto stringValue = getStringAttribute(attrs, ATTR_VALUE, "");
    QVariant value = Field::deserialize(stringValue, fieldType);

    return Field(fieldType, name, value);
}

static Card deserializeCard(const QDomElement &cardElement) {
    auto attrs = cardElement.attributes();

    auto cardClassAttr = getStringAttribute(attrs, ATTR_RECORD_CLASS, "CARD");
    auto &cardClass = CardClass::valueOf(cardClassAttr.toStdString());

    auto uuid = getUuidAttribute(attrs, ATTR_UUID);
    auto name = getStringAttribute(attrs, ATTR_NAME, "");
    if (name.isEmpty()) {
        throw PasswordManagerException("Mandatory attribute name is missing");
    }

    auto pictureStrValue = getStringAttribute(attrs, ATTR_PICTURE, "GENERIC");
    auto &picture = Picture::valueOf(pictureStrValue.toStdString());
    auto modified = getLongAttribute(attrs, ATTR_MODIFIED, 0L);
    bool favorite = getBoolAttribute(attrs, ATTR_FAVORITE, false);
    auto active = getBoolAttribute(attrs, ATTR_ACTIVE, true);

    // Deserialize fields
    auto fieldNodes = cardElement.elementsByTagName(ELEMENT_FIELD);
    std::vector<Field> fields;
    fields.reserve(fieldNodes.count());
    for (auto index = 0; index < fieldNodes.count(); ++index) {
        auto fieldElement = fieldNodes.at(index).toElement();
        fields.push_back(deserializeField(fieldElement));
    }

    // Deserialize note
    QString note;
    auto noteNodes = cardElement.elementsByTagName(ELEMENT_NOTE);
    if (!noteNodes.isEmpty()) {
        note = noteNodes.at(0).toElement().text();
    }

    return Card(cardClass, uuid, picture, name, modified, note, favorite, active, fields);
}

void deserialize(const QDomDocument &doc, std::vector<Card> &list) {
    auto recordNodes = doc.elementsByTagName("record");
    list.reserve(recordNodes.size());
    for (auto index = 0; index < recordNodes.size(); ++index) {
        auto node = recordNodes.at(index);
        list.push_back(deserializeCard(node.toElement()));
    }
}

static QString fieldValueToString(const Field &field) {
    auto value = field.value();
    auto &type = field.type();

    if (type == FieldType::DATE || type == FieldType::EXPIRATION_MONTH) {
        auto date = value.toDate();
        return date.toString("yyyy-MM-dd");
    } else if (type == FieldType::CARD_TYPE) {
        auto ordinal = value.toUInt();
        auto &creditCardType = CreditCardType::valueOf(ordinal);
        return QString::fromStdString(creditCardType.name());
    } else {
        return value.toString();
    }
}

static void serializeField(QXmlStreamWriter &stream, const Field &field) {
    stream.writeStartElement(ELEMENT_FIELD);
    stream.writeAttribute(ATTR_NAME, field.name());
    stream.writeAttribute(ATTR_TYPE, QString::fromStdString(field.type().name()));
    stream.writeAttribute(ATTR_VALUE, fieldValueToString(field));
    stream.writeEndElement();
}

static void serializeCard(QXmlStreamWriter &stream, const Card &card) {
    stream.writeStartElement(RECORD);

    // Attributes
    stream.writeAttribute(ATTR_RECORD_CLASS, QString::fromStdString(card.cardClass().name()));
    stream.writeAttribute(ATTR_NAME, card.name());
    stream.writeAttribute(ATTR_UUID, card.uuid().toString());
    stream.writeAttribute(ATTR_MODIFIED, QString::number(card.modified()));
    stream.writeAttribute(ATTR_PICTURE, QString::fromStdString(card.picture().name()));
    stream.writeAttribute(ATTR_FAVORITE, card.favorite() ? "true" : "false");
    stream.writeAttribute(ATTR_ACTIVE, card.active() ? "true" : "false");

    // Fields
    if (!card.fields().empty()) {
        stream.writeStartElement(ELEMENT_FIELDS);
        for (const auto &field : card.fields()) {
            serializeField(stream, field);
        }
        stream.writeEndElement(); // Fields
    }

    // Note
    stream.writeTextElement(ELEMENT_NOTE, card.note());
    stream.writeEndElement();
}

void serialize(const std::vector<Card> &list, QByteArray &byteArray) {
    QXmlStreamWriter stream{&byteArray};

    stream.writeStartDocument();

    stream.writeStartElement(RECORDS);
    stream.writeAttribute(ATTR_VERSION, QString::fromStdString(Version::projectVersion));

    for (const auto &card : list) {
        serializeCard(stream, card);
    }

    stream.writeEndElement();
    stream.writeEndDocument();
}

} // namespace Serializer
