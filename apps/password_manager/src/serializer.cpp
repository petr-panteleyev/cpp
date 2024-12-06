/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#include "serializer.h"
#include "exceptions.h"
#include "model/cardclass.h"
#include "model/picture.h"
#include <QDate>
#include <QDomElement>
#include <QDomNamedNodeMap>
#include <QUuid>

namespace Serializer {

static const QString RECORD{"record"};
static const QString RECORD_CLASS{"recordClass"};

static const QString ATTR_UUID{"uuid"};
static const QString ATTR_NAME{"name"};
static const QString ATTR_MODIFIED{"modified"};
static const QString ATTR_FAVORITE{"favorite"};
static const QString ATTR_ACTIVE{"active"};
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
        auto long_value = attributes.namedItem(name).toAttr().name().toLong(&ok);
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

static FieldPtr deserializeField(const QDomElement &fieldElement) {
    auto attrs = fieldElement.attributes();

    auto  fieldTypeStr = getStringAttribute(attrs, ATTR_TYPE, "STRING");
    auto &fieldType = FieldType::valueOf(fieldTypeStr.toStdString());

    auto name = getStringAttribute(attrs, ATTR_NAME, "");

    auto     stringValue = getStringAttribute(attrs, ATTR_VALUE, "");
    QVariant value = Field::deserialize(stringValue, fieldType);

    return std::make_shared<Field>(fieldType, name, value);
}

static CardPtr deserializeCard(const QDomElement &cardElement) {
    auto attrs = cardElement.attributes();

    auto  cardClassAttr = getStringAttribute(attrs, RECORD_CLASS, "CARD");
    auto &cardClass = CardClass::valueOf(cardClassAttr.toStdString());

    QUuid   uuid = getUuidAttribute(attrs, ATTR_UUID);
    QString name = getStringAttribute(attrs, ATTR_NAME, "");
    if (name.isEmpty()) {
        throw PasswordManagerException("Mandatory attribute name is missing");
    }

    auto  pictureStrValue = getStringAttribute(attrs, "picture", "GENERIC");
    auto &picture = Picture::valueOf(pictureStrValue.toStdString());
    auto  modified = getLongAttribute(attrs, ATTR_MODIFIED, 0L);
    bool  favorite = getBoolAttribute(attrs, ATTR_FAVORITE, false);
    auto  active = getBoolAttribute(attrs, ATTR_ACTIVE, true);

    // Deserialize fields
    std::vector<FieldPtr> fields;

    auto fieldNodes = cardElement.elementsByTagName("field");
    for (auto index = 0; index < fieldNodes.count(); ++index) {
        auto fieldElement = fieldNodes.at(index).toElement();
        auto field = deserializeField(fieldElement);
        fields.push_back(field);
    }

    // Deserialize note
    QString note;
    auto    noteNodes = cardElement.elementsByTagName("note");
    if (!noteNodes.isEmpty()) {
        note = noteNodes.at(0).toElement().text();
    }

    return std::make_shared<Card>(cardClass, uuid, picture, name, modified, note, favorite, active, fields);
}

void deserialize(const QDomDocument &doc, std::vector<CardPtr> &list) {
    auto recordNodes = doc.elementsByTagName("record");
    for (auto index = 0; index < recordNodes.size(); ++index) {
        auto node = recordNodes.at(index);
        auto card = deserializeCard(node.toElement());
        list.push_back(card);
    }
}

} // namespace Serializer
