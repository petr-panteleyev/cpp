/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#ifndef PICTURE_H
#define PICTURE_H

#include "enumclass.h"
#include <QIcon>
#include <functional>
#include <string>

class Picture final : Common::EnumClass<Picture> {
  public:
    static const Picture ICON;
    static const Picture SMILING_FACE;
    static const Picture SAD_FACE;
    static const Picture LAUGHING_FACE;
    static const Picture RED_FLAG;
    static const Picture BLACK_FLAG;

  public:
    const QIcon &icon() const;

  private:
    explicit Picture(const std::string &name, const QString &fileName) : EnumClass{name}, fileName_{fileName} {}

  private:
    const QString fileName_;
};

using PictureRef = std::reference_wrapper<const Picture>;

#endif // PICTURE_H
