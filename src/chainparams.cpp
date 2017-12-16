// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2017 The ColossusCoinXT developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "bignum.h"
#include "chainparams.h"

#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
boost::assign::map_list_of
( 0, uint256("0x001"));

static const Checkpoints::CCheckpointData data = {
&mapCheckpoints,
1513389723, // * UNIX timestamp of last checkpoint block
0,    // * total number of transactions between genesis and last checkpoint
            //   (the tx=... number in the SetBestChain debug.log lines)
2000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
boost::assign::map_list_of
( 0, uint256("0x001"));

static const Checkpoints::CCheckpointData dataTestnet = {
&mapCheckpointsTestnet,
1513389723,
0,
250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
boost::assign::map_list_of
( 0, uint256("0x001"));

static const Checkpoints::CCheckpointData dataRegtest = {
&mapCheckpointsRegtest,
1513389723,
0,
100};

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x53;
        pchMessageStart[1] = 0x4b;
        pchMessageStart[2] = 0x49;
        pchMessageStart[3] = 0x4e;
        vAlertPubKey = ParseHex("04989235e6c1513366081f275522cba97a2a2703ee9af9ad30228132a553f3aa04dcbf0f2697a1b265f266a04398247ddcf733bde22805bec1f3719064037c925e");
        nDefaultPort = 7546;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // Skin starting difficulty is 1 / 2^12
        nSubsidyHalvingInterval = 210000;
        nMaxReorganizationDepth = 30;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 120; // Skin: 2 minute
        nTargetSpacing = 1 * 120;  // Skin: 2 minute
        nLastPOWBlock = 350;
        nMaturity = 50;
        nMasternodeCountDrift = 20;
        nModifierUpdateBlock = 0;
        nMaxMoneyOut = int64_t(20000000000) * COIN;
        nModifierInterval = 60;
        nModifierIntervalRatio = 3;
        //nBudgetPercent = 5;
        nMinStakeAge = 60*60*8; // 8 Hours
        nMasternodeRewardPercent = 60; // % of block reward that goes to masternodes
        nRequiredMasternodeCollateral = 4000 * COIN; //10,000,000

        /**
         * Build the genesis block. Note that the output of the genesis coinbase cannot
         * be spent as it did not originally exist in the database.
         *
         * CBlock(hash=00000ffd590b14, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=e0028e, nTime=1390095618, nBits=1e0ffff0, nNonce=28917698, vtx=1)
         *   CTransaction(hash=e0028e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
         *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d01044c5957697265642030392f4a616e2f3230313420546865204772616e64204578706572696d656e7420476f6573204c6976653a204f76657273746f636b2e636f6d204973204e6f7720416363657074696e6720426974636f696e73)
         *     CTxOut(nValue=50.00000000, scriptPubKey=0xA9037BAC7050C479B121CF)
         *   vMerkleTree: e0028e
         */
        const char* pszTimestamp = "2017-12-15 Soweto man overcomes depression to get engineering degree";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 5654 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04e899addc55804061f2941e21fc6ffda9052d03b0dda80005fe9dccffc08dbeefbbbb5dee75318ded2f2869de0e0b0b3e71200e4cb06ef8719e97d7d5880491cf") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1513389723;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 6013941;

        hashGenesisBlock = uint256("0000004903bce55e27c02b21b83d11dc9dddf2fca983793a8b8eaa9ba61f42e6");
        if (true && genesis.GetHash() != hashGenesisBlock)
        {
            printf("Searching for main net genesis block...\n");
            uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
            uint256 thash;

            while (true)
            {
                thash = genesis.GetHash();
                if (thash <= hashTarget)
                    break;
                if ((genesis.nNonce & 0xFFF) == 0)
                {
                    printf("nonce %08X: hash = %s (target = %s)\n", genesis.nNonce, thash.ToString().c_str(), hashTarget.ToString().c_str());
                }
                ++genesis.nNonce;
                if (genesis.nNonce == 0)
                {
                    printf("NONCE WRAPPED, incrementing time\n");
                    ++genesis.nTime;
                }
            }
            printf("genesis.nTime = %u \n", genesis.nTime);
            printf("genesis.nNonce = %u \n", genesis.nNonce);
            printf("genesis.nVersion = %u \n", genesis.nVersion);
            printf("genesis.GetHash = %s\n", genesis.GetHash().ToString().c_str()); //first this, then comment this line out and uncomment the one under.
            printf("genesis.hashMerkleRoot = %s \n", genesis.hashMerkleRoot.ToString().c_str()); //improvised. worked for me, to find merkle root

        }

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0000004903bce55e27c02b21b83d11dc9dddf2fca983793a8b8eaa9ba61f42e6"));
        assert(genesis.hashMerkleRoot == uint256("969e88fc67fc3a800a048ba0fd01d9e966684d544c28d52f08bb9121e691a243"));

        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("104.131.23.88", "104.131.23.88")); 
        vSeeds.push_back(CDNSSeedData("104.131.30.157", "104.131.30.157")); 
        //vSeeds.push_back(CDNSSeedData("67.199.118.93", "67.199.118.93")); 

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 0x53);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 0x4b);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 0x56);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(83)(75)(73)(78).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(83)(69)(88)(89).convert_to_container<std::vector<unsigned char> >();
        // 	BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x77).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = true;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;

        strSporkKey = "04B433E6598390C992F4F022F20D3B4CBBE691652EE7C48243B81701CBDB7CC7D7BF0EE09E154E6FCBF2043D65AF4E9E97B89B5DBAF830D83B9B7F469A6C45A717";
        strObfuscationPoolDummyAddress = "D87q2gC9j6nNrnzCsg4aY6bHMLsT9nUhEw";
        nStartMasternodePayments = 1403728576; //Wed, 25 Jun 2014 20:36:16 GMT
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0x73;
        pchMessageStart[1] = 0x6b;
        pchMessageStart[2] = 0x69;
        pchMessageStart[3] = 0x6e;
        vAlertPubKey = ParseHex("04bd62aa79235c0549f8e139aea728c0cc3f2ad19e2daecca9847870b21012b3d7e88190f63f557e5215559533b9e92980964e96d330f8feffeb615a2505081ec4");
        nDefaultPort = 17546;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // Skin: 1 day
        nTargetSpacing = 1 * 60;  // Skin: 1 minute
        nLastPOWBlock = 200;
        nMaturity = 15;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 0; //approx Mon, 17 Apr 2017 04:00:00 GMT
        nMaxMoneyOut = 1200000000 * COIN;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1513389723;
        genesis.nNonce = 8543586;

        hashGenesisBlock = uint256("000000a631d7449c4bdca6208b5f2f2b2ce2b9eb2db2f459589b121d1f26038d");
        if (true && genesis.GetHash() != hashGenesisBlock)
        {
            printf("Searching for test net genesis block...\n");
            uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
            uint256 thash;

            while (true)
            {
                thash = genesis.GetHash();
                if (thash <= hashTarget)
                    break;
                if ((genesis.nNonce & 0xFFF) == 0)
                {
                    printf("nonce %08X: hash = %s (target = %s)\n", genesis.nNonce, thash.ToString().c_str(), hashTarget.ToString().c_str());
                }
                ++genesis.nNonce;
                if (genesis.nNonce == 0)
                {
                    printf("NONCE WRAPPED, incrementing time\n");
                    ++genesis.nTime;
                }
            }
            printf("genesis.nTime = %u \n", genesis.nTime);
            printf("genesis.nNonce = %u \n", genesis.nNonce);
            printf("genesis.nVersion = %u \n", genesis.nVersion);
            printf("genesis.GetHash = %s\n", genesis.GetHash().ToString().c_str()); //first this, then comment this line out and uncomment the one under.
            printf("genesis.hashMerkleRoot = %s \n", genesis.hashMerkleRoot.ToString().c_str()); //improvised. worked for me, to find merkle root

        }

        //hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("000000a631d7449c4bdca6208b5f2f2b2ce2b9eb2db2f459589b121d1f26038d"));
        assert(genesis.hashMerkleRoot == uint256("969e88fc67fc3a800a048ba0fd01d9e966684d544c28d52f08bb9121e691a243"));
        
        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 8); // Testnet pivx addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 133);  // Testnet pivx script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 127);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
         // Testnet pivx BIP32 pubkeys start with 'DRKV'
         base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(177)(60)(206)(172).convert_to_container<std::vector<unsigned char> >();
         // Testnet pivx BIP32 prvkeys start with 'DRKP'
         base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(177)(61)(214)(147).convert_to_container<std::vector<unsigned char> >();
         // Testnet Skin BIP44 coin type is '1' (All coin's testnet default)
         base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "04348C2F50F90267E64FACC65BFDC9D0EB147D090872FB97ABAE92E9A36E6CA60983E28E741F8E7277B11A7479B626AC115BA31463AC48178A5075C5A9319D4A38";
        strObfuscationPoolDummyAddress = "y57cqfGRkekRyDRNeJiLtYVEbvhXrNbmox";
        nStartMasternodePayments = 1420837558; //Fri, 09 Jan 2015 21:05:58 GMT
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0x53;
        pchMessageStart[1] = 0x45;
        pchMessageStart[2] = 0x58;
        pchMessageStart[3] = 0x59;
        nSubsidyHalvingInterval = 150;
        nDefaultPort = 27546;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // Pivx: 1 day
        nTargetSpacing = 1 * 60;        // Pivx: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1513389723;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 12350;

        hashGenesisBlock = uint256("30614f105e300e231da3adea85b090861ab451eb51210352f016081bfd5e270b");
        if (true && genesis.GetHash() != hashGenesisBlock)
        {
            printf("Searching for reg test net genesis block...\n");
            uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
            uint256 thash;

            while (true)
            {
                thash = genesis.GetHash();
                if (thash <= hashTarget)
                    break;
                if ((genesis.nNonce & 0xFFF) == 0)
                {
                    printf("nonce %08X: hash = %s (target = %s)\n", genesis.nNonce, thash.ToString().c_str(), hashTarget.ToString().c_str());
                }
                ++genesis.nNonce;
                if (genesis.nNonce == 0)
                {
                    printf("NONCE WRAPPED, incrementing time\n");
                    ++genesis.nTime;
                }
            }
            printf("genesis.nTime = %u \n", genesis.nTime);
            printf("genesis.nNonce = %u \n", genesis.nNonce);
            printf("genesis.nVersion = %u \n", genesis.nVersion);
            printf("genesis.GetHash = %s\n", genesis.GetHash().ToString().c_str()); //first this, then comment this line out and uncomment the one under.
            printf("genesis.hashMerkleRoot = %s \n", genesis.hashMerkleRoot.ToString().c_str()); //improvised. worked for me, to find merkle root

        }

        assert(hashGenesisBlock == uint256("30614f105e300e231da3adea85b090861ab451eb51210352f016081bfd5e270b"));
        assert(genesis.hashMerkleRoot == uint256("969e88fc67fc3a800a048ba0fd01d9e966684d544c28d52f08bb9121e691a243"));
        
        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 51478;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}