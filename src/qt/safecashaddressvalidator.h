// Copyright (c) 2011-2014 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef SAFECASH_QT_SAFECASHADDRESSVALIDATOR_H
#define SAFECASH_QT_SAFECASHADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class SafeCashAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit SafeCashAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** SafeCash address widget validator, checks for a valid SafeCash address.
 */
class SafeCashAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit SafeCashAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // SAFECASH_QT_SAFECASHADDRESSVALIDATOR_H
