//  Copyright © 2025 Petr Panteleyev
//  SPDX-License-Identifier: BSD-2-Clause

#include "translation.h"
#include "categorytype.h"
#include "contacttype.h"
#include "transactiontype.h"
#include <stdexcept>
#include <string>
#include <unordered_map>

namespace Translation {

static const std::unordered_map<unsigned, QString> TRANSACTION_TYPE_TRANSLATION{
    {TransactionType::CARD_PAYMENT.ordinal(), "Оплата картой"},
    {TransactionType::SBP_PAYMENT.ordinal(), "Платеж через СБП"},
    {TransactionType::CASH_PURCHASE.ordinal(), "Покупка за наличные"},
    {TransactionType::CHEQUE.ordinal(), "Чек"},
    {TransactionType::TRANSFER.ordinal(), "Перевод"},
    {TransactionType::SBP_TRANSFER.ordinal(), "Перевод через СБП"},
    {TransactionType::DEPOSIT.ordinal(), "Депозит"},
    {TransactionType::WITHDRAWAL.ordinal(), "Снятие наличных"},
    {TransactionType::INTEREST.ordinal(), "Проценты"},
    {TransactionType::INCOME.ordinal(), "Доход"},
    {TransactionType::FEE.ordinal(), "Комиссия"},
    {TransactionType::CACHIER.ordinal(), "Транзакция в банкомате"},
    {TransactionType::DIVIDEND.ordinal(), "Дивиденды"},
    {TransactionType::DIRECT_BILLING.ordinal(), "Прямое дебетование"},
    {TransactionType::CHARGE.ordinal(), "Списание"},
    {TransactionType::PURCHASE.ordinal(), "Покупка"},
    {TransactionType::SALE.ordinal(), "Продажа"},
    {TransactionType::REFUND.ordinal(), "Возврат"},
    {TransactionType::UNDEFINED.ordinal(), "Неизвестно"},
};

static const std::unordered_map<unsigned, QString> CATEGORY_TYPE_TRANSLATION{
    {CategoryType::BANKS_AND_CASH.ordinal(), "Банки"}, {CategoryType::INCOMES.ordinal(), "Доходы"},
    {CategoryType::EXPENSES.ordinal(), "Расходы"},     {CategoryType::DEBTS.ordinal(), "Долги"},
    {CategoryType::PORTFOLIO.ordinal(), "Портфель"},   {CategoryType::ASSETS.ordinal(), "Активы"},
    {CategoryType::STARTUP.ordinal(), "Стартап"},
};

static const std::unordered_map<unsigned, QString> CONTACT_TYPE_TRANSLATION{
    {ContactType::PERSONAL.ordinal(), "Личное"},       {ContactType::CLIENT.ordinal(), "Клиент"},
    {ContactType::SUPPLIER.ordinal(), "Поставщик"},    {ContactType::EMPLOYEE.ordinal(), "Сотрудник"},
    {ContactType::EMPLOYER.ordinal(), "Работодатель"}, {ContactType::SERVICE.ordinal(), "Услуга"},
};

const QString &translateCategoryType(unsigned type) {
    if (!CATEGORY_TYPE_TRANSLATION.contains(type)) {
        throw std::out_of_range("No CategoryType transalation for " + std::to_string(type));
    }

    return CATEGORY_TYPE_TRANSLATION.at(type);
}

const QString &translateContactType(unsigned type) {
    if (!CONTACT_TYPE_TRANSLATION.contains(type)) {
        throw std::out_of_range("No ContactType transalation for " + std::to_string(type));
    }

    return CONTACT_TYPE_TRANSLATION.at(type);
}

const QString &translateTransactionType(unsigned type) {
    if (!TRANSACTION_TYPE_TRANSLATION.contains(type)) {
        throw std::out_of_range("No TransactionType transalation for " + std::to_string(type));
    }

    return TRANSACTION_TYPE_TRANSLATION.at(type);
}

} // namespace Translation
