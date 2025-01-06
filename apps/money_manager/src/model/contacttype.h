//  Copyright © 2024 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef CONTACTTYPE_H
#define CONTACTTYPE_H

#include "enumclass.h"
#include <functional>
#include <string>

class ContactType final : public Common::EnumClass<ContactType> {
  public:
    static const ContactType PERSONAL;
    static const ContactType CLIENT;
    static const ContactType SUPPLIER;
    static const ContactType EMPLOYEE;
    static const ContactType EMPLOYER;
    static const ContactType SERVICE;

  public:
    ~ContactType() = default;

  private:
    explicit ContactType(const std::string &name) : EnumClass{name} {}
};

using ContactTypeRef = std::reference_wrapper<const ContactType>;

const inline ContactType ContactType::PERSONAL{"PERSONAL"};
const inline ContactType ContactType::CLIENT{"CLIENT"};
const inline ContactType ContactType::SUPPLIER{"SUPPLIER"};
const inline ContactType ContactType::EMPLOYEE{"EMPLOYEE"};
const inline ContactType ContactType::EMPLOYER{"EMPLOYER"};
const inline ContactType ContactType::SERVICE{"SERVICE"};

template <>
const inline std::vector<ContactTypeRef> Common::EnumClass<ContactType>::values_{
    std::cref(ContactType::PERSONAL), std::cref(ContactType::CLIENT),   std::cref(ContactType::SUPPLIER),
    std::cref(ContactType::EMPLOYEE), std::cref(ContactType::EMPLOYER), std::cref(ContactType::SERVICE),
};

#endif // CONTACTTYPE_H
