//  Copyright © 2025 Petr Panteleyev <petr@panteleyev.org>
//  SPDX-License-Identifier: BSD-2-Clause

#ifndef TRANSACTIONTYPE_H
#define TRANSACTIONTYPE_H

#include "enumclass.h"
#include <functional>
#include <string>

class TransactionType final : public Common::EnumClass<TransactionType> {
  public:
    static const TransactionType CARD_PAYMENT;
    static const TransactionType SBP_PAYMENT;
    static const TransactionType CASH_PURCHASE;
    static const TransactionType CHEQUE;
    static const TransactionType S1;
    static const TransactionType WITHDRAWAL;
    static const TransactionType CACHIER;
    static const TransactionType DEPOSIT;
    static const TransactionType TRANSFER;
    static const TransactionType SBP_TRANSFER;
    static const TransactionType S2;
    static const TransactionType INTEREST;
    static const TransactionType DIVIDEND;
    static const TransactionType S3;
    static const TransactionType DIRECT_BILLING;
    static const TransactionType CHARGE;
    static const TransactionType FEE;
    static const TransactionType S4;
    static const TransactionType INCOME;
    static const TransactionType PURCHASE;
    static const TransactionType SALE;
    static const TransactionType S5;
    static const TransactionType REFUND;
    static const TransactionType UNDEFINED;

  public:
    ~TransactionType() = default;
    bool isSeparator() const noexcept { return separator_; }

  private:
    explicit TransactionType(const std::string &name, bool separator) noexcept
        : EnumClass{name}, separator_{separator} {}
    explicit TransactionType(const std::string &name) noexcept : TransactionType{name, false} {}

  private:
    bool separator_;
};

using TransactionTypeRef = std::reference_wrapper<const TransactionType>;

const inline TransactionType TransactionType::CARD_PAYMENT{"CARD_PAYMENT"};
const inline TransactionType TransactionType::SBP_PAYMENT{"SBP_PAYMENT"};
const inline TransactionType TransactionType::CASH_PURCHASE{"CASH_PURCHASE"};
const inline TransactionType TransactionType::CHEQUE{"CHEQUE"};
const inline TransactionType TransactionType::S1{"S1", true};
const inline TransactionType TransactionType::WITHDRAWAL{"WITHDRAWAL"};
const inline TransactionType TransactionType::CACHIER{"CACHIER"};
const inline TransactionType TransactionType::DEPOSIT{"DEPOSIT"};
const inline TransactionType TransactionType::TRANSFER{"TRANSFER"};
const inline TransactionType TransactionType::SBP_TRANSFER{"SBP_TRANSFER"};
const inline TransactionType TransactionType::S2{"S2", true};
const inline TransactionType TransactionType::INTEREST{"INTEREST"};
const inline TransactionType TransactionType::DIVIDEND{"DIVIDEND"};
const inline TransactionType TransactionType::S3{"S3", true};
const inline TransactionType TransactionType::DIRECT_BILLING{"DIRECT_BILLING"};
const inline TransactionType TransactionType::CHARGE{"CHARGE"};
const inline TransactionType TransactionType::FEE{"FEE"};
const inline TransactionType TransactionType::S4{"S4", true};
const inline TransactionType TransactionType::INCOME{"INCOME"};
const inline TransactionType TransactionType::PURCHASE{"PURCHASE"};
const inline TransactionType TransactionType::SALE{"SALE"};
const inline TransactionType TransactionType::S5{"S5", true};
const inline TransactionType TransactionType::REFUND{"REFUND"};
const inline TransactionType TransactionType::UNDEFINED{"UNDEFINED"};

template <>
const inline std::vector<TransactionTypeRef> Common::EnumClass<TransactionType>::values_{
    std::cref(TransactionType::CARD_PAYMENT),
    std::cref(TransactionType::SBP_PAYMENT),
    std::cref(TransactionType::CASH_PURCHASE),
    std::cref(TransactionType::CHEQUE),
    std::cref(TransactionType::S1),
    std::cref(TransactionType::WITHDRAWAL),
    std::cref(TransactionType::CACHIER),
    std::cref(TransactionType::DEPOSIT),
    std::cref(TransactionType::TRANSFER),
    std::cref(TransactionType::SBP_TRANSFER),
    std::cref(TransactionType::S2),
    std::cref(TransactionType::INTEREST),
    std::cref(TransactionType::DIVIDEND),
    std::cref(TransactionType::S3),
    std::cref(TransactionType::DIRECT_BILLING),
    std::cref(TransactionType::CHARGE),
    std::cref(TransactionType::FEE),
    std::cref(TransactionType::S4),
    std::cref(TransactionType::INCOME),
    std::cref(TransactionType::PURCHASE),
    std::cref(TransactionType::SALE),
    std::cref(TransactionType::S5),
    std::cref(TransactionType::REFUND),
    std::cref(TransactionType::UNDEFINED),
};

#endif // TRANSACTIONTYPE_H
