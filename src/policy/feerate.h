// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2017 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef SAFECASH_POLICY_FEERATE_H
#define SAFECASH_POLICY_FEERATE_H

#include <amount.h>
#include <serialize.h>

#include <string>

extern const std::string CURRENCY_UNIT;

/**
 * Fee rate in scashis per kilobyte: CAmount / kB
 */
class CFeeRate
{
private:
    CAmount nScashisPerK; // unit is scashis-per-1,000-bytes

public:
    /** Fee rate of 0 scashis per kB */
    CFeeRate() : nScashisPerK(0) { }
    template<typename I>
    CFeeRate(const I _nScashisPerK): nScashisPerK(_nScashisPerK) {
        // We've previously had bugs creep in from silent double->int conversion...
        static_assert(std::is_integral<I>::value, "CFeeRate should be used without floats");
    }
    /** Constructor for a fee rate in scashis per kB. The size in bytes must not exceed (2^63 - 1)*/
    CFeeRate(const CAmount& nFeePaid, size_t nBytes);
    CFeeRate(const CFeeRate& other) { nScashisPerK = other.nScashisPerK; }
    /**
     * Return the fee in scashis for the given size in bytes.
     */
    CAmount GetFee(size_t nBytes) const;
    /**
     * Return the fee in scashis for a size of 1000 bytes
     */
    CAmount GetFeePerK() const { return GetFee(1000); }
    friend bool operator<(const CFeeRate& a, const CFeeRate& b) { return a.nScashisPerK < b.nScashisPerK; }
    friend bool operator>(const CFeeRate& a, const CFeeRate& b) { return a.nScashisPerK > b.nScashisPerK; }
    friend bool operator==(const CFeeRate& a, const CFeeRate& b) { return a.nScashisPerK == b.nScashisPerK; }
    friend bool operator<=(const CFeeRate& a, const CFeeRate& b) { return a.nScashisPerK <= b.nScashisPerK; }
    friend bool operator>=(const CFeeRate& a, const CFeeRate& b) { return a.nScashisPerK >= b.nScashisPerK; }
    friend bool operator!=(const CFeeRate& a, const CFeeRate& b) { return a.nScashisPerK != b.nScashisPerK; }
    CFeeRate& operator+=(const CFeeRate& a) { nScashisPerK += a.nScashisPerK; return *this; }
    std::string ToString() const;

    ADD_SERIALIZE_METHODS;

    template <typename Stream, typename Operation>
    inline void SerializationOp(Stream& s, Operation ser_action) {
        READWRITE(nScashisPerK);
    }
};

#endif //  SAFECASH_POLICY_FEERATE_H
