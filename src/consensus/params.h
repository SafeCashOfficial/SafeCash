// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2017 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef SAFECASH_CONSENSUS_PARAMS_H
#define SAFECASH_CONSENSUS_PARAMS_H

#include <uint256.h>
#include <limits>
#include <map>
#include <string>

/** SafeCash Values */
static const int BLOCK_REWARD_MAX = 1000;
static const int BLOCK_REWARD_MIN = 20;
static const int HOURS_IN_DAY = 24;
static const int DAYS_IN_WEEK = 7;
static const int WEEKS_IN_MONTH = 4;
static const int MONTHS_IN_YEAR = 12;
static const int BONUS_DIVISOR = 100; // Bonus blocks pay out 1% of the max reward of the preceding blocks


namespace Consensus {

enum DeploymentPos
{
    DEPLOYMENT_TESTDUMMY,
    DEPLOYMENT_CSV, // Deployment of BIP68, BIP112, and BIP113.
    DEPLOYMENT_SEGWIT, // Deployment of BIP141, BIP143, and BIP147.
    // NOTE: Also add new deployments to VersionBitsDeploymentInfo in versionbits.cpp
    MAX_VERSION_BITS_DEPLOYMENTS
};

/**
 * Struct for each individual consensus rule change using BIP9.
 */
struct BIP9Deployment {
    /** Bit position to select the particular bit in nVersion. */
    int bit;
    /** Start MedianTime for version bits miner confirmation. Can be a date in the past */
    int64_t nStartTime;
    /** Timeout/expiry MedianTime for the deployment attempt. */
    int64_t nTimeout;

    /** Constant for nTimeout very far in the future. */
    static constexpr int64_t NO_TIMEOUT = std::numeric_limits<int64_t>::max();

    /** Special value for nStartTime indicating that the deployment is always active.
     *  This is useful for testing, as it means tests don't need to deal with the activation
     *  process (which takes at least 3 BIP9 intervals). Only tests that specifically test the
     *  behaviour during activation cannot use this. */
    static constexpr int64_t ALWAYS_ACTIVE = -1;
};

/**
 * Parameters that influence chain consensus.
 */
struct Params {
    uint256 hashGenesisBlock;
    uint32_t timeGenesisBlock;
    int nSubsidyHalvingInterval;
    /** Block height at which BIP16 becomes active */
    int BIP16Height;
    /** Block height and hash at which BIP34 becomes active */
    int BIP34Height;
    uint256 BIP34Hash;
    /** Block height at which BIP65 becomes active */
    int BIP65Height;
    /** Block height at which BIP66 becomes active */
    int BIP66Height;
    /**
     * Minimum blocks including miner confirmation of the total of 2016 blocks in a retargeting period,
     * (nPowTargetTimespan / nPowTargetSpacing) which is also used for BIP9 deployments.
     * Examples: 1916 for 95%, 1512 for testchains.
     */
    uint32_t nRuleChangeActivationThreshold;
    uint32_t nMinerConfirmationWindow;
    BIP9Deployment vDeployments[MAX_VERSION_BITS_DEPLOYMENTS];
    /** Proof of work parameters */
    uint256 powLimit;
    bool fPowAllowMinDifficultyBlocks;
    bool fPowNoRetargeting;
    int64_t nPowTargetSpacing;
    int64_t nPowTargetTimespan;
    int64_t DifficultyAdjustmentInterval() const { return nPowTargetTimespan / nPowTargetSpacing; }
    uint256 nMinimumChainWork;
    uint256 defaultAssumeValid;
    int64_t nPowAveragingWindow;
    int64_t nPowMaxAdjustDown;
    int64_t nPowMaxAdjustUp;
    int64_t AveragingWindowTimespan() const { return nPowAveragingWindow * nPowTargetSpacing; }
    int64_t MinActualTimespan() const { return (AveragingWindowTimespan() * (100 - nPowMaxAdjustUp  )) / 100; }
    int64_t MaxActualTimespan() const { return (AveragingWindowTimespan() * (100 + nPowMaxAdjustDown)) / 100; }
    // SafeCash PoW
    int nSuperBlockInterval;
    // Big Block Interval Calculation
    int GetUltraBlockInterval() const 
    {
        return nSuperBlockInterval * DAYS_IN_WEEK * WEEKS_IN_MONTH * MONTHS_IN_YEAR;
    }
    int GetMegaBlockInterval() const 
    {
        return nSuperBlockInterval * DAYS_IN_WEEK * WEEKS_IN_MONTH;
    }
    int GetSuperBlockInterval() const 
    {
        return nSuperBlockInterval * DAYS_IN_WEEK;
    }
    int GetBonusBlockInterval() const 
    {
        return nSuperBlockInterval;
    }
    int GetLastFoundersRewardBlockHeight() const 
    {
        return 483840; // 1 year's worth of blocks
    }    
    uint32_t GetLastFoundersRewardBlockTime() const 
    {
        return timeGenesisBlock + 31536000; // 1 year from genesis block time
    }
    bool IsBigBlock(int nHeight) const
    {
        if  ((nHeight >= GetUltraBlockInterval() && (nHeight % GetUltraBlockInterval()) == 0) ||
            (nHeight >= GetMegaBlockInterval() && (nHeight % GetMegaBlockInterval()) == 0) ||
            (nHeight >= GetSuperBlockInterval() && (nHeight % GetSuperBlockInterval()) == 0) ||
            (nHeight >= GetBonusBlockInterval() && (nHeight % GetBonusBlockInterval()) == 0))
        {
            return true;
        }
        else
        {
            return false;
        }
    }    
};
} // namespace Consensus

#endif // SAFECASH_CONSENSUS_PARAMS_H
