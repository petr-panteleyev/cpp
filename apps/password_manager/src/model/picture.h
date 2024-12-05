/*
  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
  SPDX-License-Identifier: BSD-2-Clause
*/

#ifndef PICTURE_H
#define PICTURE_H

#include <QIcon>
#include <string>

class Picture;
enum class PictureEnum : unsigned { FAVORITES, GENERIC, MOBILE, NOTE, TRASH };

class Picture final {
  public:
    static const Picture FAVORITES;
    static const Picture GENERIC;
    static const Picture MOBILE;
    static const Picture NOTE;
    static const Picture TRASH;

  public:
    const std::string &name() const { return name_; }
    const QIcon       &icon() const;

    static const Picture &valueOf(const std::string &name);

  private:
    Picture(PictureEnum ordinal, const std::string &name, const QString &fileName)
        : ordinal_{ordinal}, name_{name}, fileName_{fileName} {}
    Picture(const Picture &) = delete;
    Picture(const Picture &&) = delete;

  private:
    const PictureEnum ordinal_;
    const std::string name_;
    const QString     fileName_;
};

#endif // PICTURE_H
