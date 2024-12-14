#ifndef RECORDTYPE_H
#define RECORDTYPE_H

#include "enumclass.h"
#include "field.h"
#include "picture.h"

class RecordType;
using RecordTypeRef = std::reference_wrapper<const RecordType>;

class RecordType final : public Common::EnumClass<RecordType> {
  public:
    static const RecordType EMPTY;
    static const RecordType CREDIT_CARD;
    static const RecordType PASSWORD;

  public:
    const Picture               &picture() const noexcept { return picture_; }
    const std::vector<FieldPtr> &fields() const noexcept { return fields_; }

  private:
    RecordType(const std::string &name, const Picture &picture, const std::vector<FieldPtr> &fields)
        : EnumClass{name}, picture_{picture}, fields_{fields} {}

  private:
    const Picture              &picture_;
    const std::vector<FieldPtr> fields_;
};

#endif // RECORDTYPE_H
