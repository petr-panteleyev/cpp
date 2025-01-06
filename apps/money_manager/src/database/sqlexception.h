#ifndef SQLEXCEPTION_H
#define SQLEXCEPTION_H

#include <stdexcept>

class SqlException final : public std::runtime_error {
  public:
    explicit SqlException(const std::string &message) : std::runtime_error{message} {}
};

#endif // SQLEXCEPTION_H
