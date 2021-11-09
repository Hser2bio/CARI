// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2020 The PIVX developers
// Copyright (c) 2020-2020 The CARI developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "chainparamsseeds.h"
#include "consensus/merkle.h"
#include "util.h"
#include "utilstrencodings.h"

#include <boost/assign/list_of.hpp>

#include <assert.h>

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;
    txNew.fPoWAlternative = false;

    CBlock genesis;
    genesis.vtx.push_back(std::make_shared<const CTransaction>(std::move(txNew)));
    genesis.hashPrevBlock.SetNull();
    genesis.nVersion = nVersion;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

/**
 * Build the genesis block. Note that the output of the genesis coinbase cannot
 * be spent as it did not originally exist in the database.
 *
 *  CBlock(hash=000005bd970b7d83eb879472fb48b2c01ed8155d7126ac3e0c201755c0c85c23, ver=1, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000, hashMerkleRoot=848a9da56df8cf4057ef911b7a1837048bea98c1e782b6eff779fd0325c77530, nTime=1594502306, nBits=1e0ffff0, nNonce=4438800, vtx=1)
 *    CTransaction(hash=848a9da56d, ver=1, vin.size=1, vout.size=1, nLockTime=0, fPoWAlternative=false)
 *      CTxIn(COutPoint(0000000000000000000000000000000000000000000000000000000000000000, 4294967295), coinbase 04ffff001d01044c4c323032302d30372d31312054686520776f726c64277320666972737420636172626f6e206372656469742067656e65726174696e6720626c6f636b636861696e206279205a696f4661627279)
 *      CTxOut(nValue=0.00000000, scriptPubKey=4104678afdb0fe5548271967f1a671)
 **/
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "2020-07-11 The world's first carbon credit generating blockchain by ZioFabry";
    const CScript genesisOutputScript = CScript() << ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (      0, uint256S("000005bd970b7d83eb879472fb48b2c01ed8155d7126ac3e0c201755c0c85c23"))
    (    800, uint256S("0000032ba1ac42c466307ebe6cf2e39c7e50b8d3c86fe93e0a2b3897737357c5"))
    (   1500, uint256S("00000235815b134488cb8e2ea9312314df5bc6c5f875120b55b9642cbd9e273d"))
    (   7500, uint256S("1e0eeb216f0dbcda9f34bc6f9ed397ef4bdba9da1eed663e142a6d24daf0be3e"))
    (  20000, uint256S("eea7971a52f3c869af0482638a8b37b017dec0686ce9ed9d5c0aa0f8f555e2c5"))
    (  45000, uint256S("f51494906258213c0761621ba4887d215165c936bdbdbf86ff318807e8202bc8"))
    ( 100000, uint256S("71f9a834ea05b936537b0923d3c98a72847548171d2df8e8983a67de2d9b53d1"))
    ( 150000, uint256S("c01196cb4a618c145ac501fe0d733b07dd87593759d797d5c92b86e30e4eecb0"))
    ( 200000, uint256S("418dbf23123919b9c52a0667f84c3d826cb1ee8d0a492e298be87be54c5597cf"))
    ( 250000, uint256S("8c420647e7ed9b8913e3e8093a5c52d177dd4b9f4a1af5ac0cc09d8ce3c2f4c2"))
    ( 275000, uint256S("528bada99df6b399f9b50b416f9d7904cc97a6008a7d15f297d32a064eec1761"))
    ( 295000, uint256S("32b67a3654cae319bbddc983a0230e020da269c1d4568693dade111b393a2baf"))
    ( 300000, uint256S("e169c8d0afc24b626c5ede4fba20e4db7d1db4c19a1cc070c085d3e1cdc93aa2")) 
    ( 320000, uint256S("966849e2f81a2862a3266736e945fb3749e1245bce9da30eb6196c7a3dfcf459"))
    ( 350000, uint256S("a5fb457b0d31d068b40be4e3d6c1020b50b176da524899ca57ef62d327630af6"))
    ( 390000, uint256S("9aa8e3094224ceffcb5d35227b9d30080ab7abf253fe8cff0b238dbbd56be3a8"))
    ( 400000, uint256S("75f842e54cf0c35895777c672ecba6b33e3a0fbab7f71ac0368264ef90c60a19"))
    ( 435000, uint256S("f57b6f7c0c911ace40039c20658e4af77f10a37ff6a386063f2014750f628450"))
    ( 470000, uint256S("bb251983f92c46b275917f78b77741f2530bebacdcf990421df103a99c488120"))
    ( 510000, uint256S("a32c8cdd712165bb111354514f7708f7433c86608b1ddb287a8141762031ceec"))
    ( 528000, uint256S("3dc10708d4d32f3cfe1eff5bec02ee1e5842a3a0ebc6652b91180754a65920e4"))
    ( 565800, uint256S("df19acca8408c3aa6cbde62051243c643655a93d7a5de2fedb886c27fb070e8f"))
    ( 600000, uint256S("5dc04579ef3d3cd6a287cdcc4f3666bf2c8d7741549222dd46a2d3722bf316b0"))
    ( 678000, uint256S("3c065e1e96296d882b3ec0834cd62d84cd8fc4de81dda09ddcae3f4d7b90db50"))
    ( 678846, uint256S("4cf2ee567fa1e4357fe2e82d4e454d1812e1970373b69bb8493cdc4fdf6e8937")) 
    ;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1636449060, // * UNIX timestamp of last checkpoint block
    1356539,        // * total number of transactions between genesis and last checkpoint (the tx=... number in the UpdateTip debug.log lines)
    3000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of
    (0, uint256S("0x001"));
    //(201, uint256S("6ae7d52092fd918c8ac8d9b1334400387d3057997e6e927a88e57186dc395231"));     // v5 activation (PoS/Sapling)
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1454124731,
    0,
    3000};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256S("0x001"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1594502306,
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
         *  CBlock(hash=000005bd970b7d83eb879472fb48b2c01ed8155d7126ac3e0c201755c0c85c23, ver=1, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000, hashMerkleRoot=848a9da56df8cf4057ef911b7a1837048bea98c1e782b6eff779fd0325c77530, nTime=1594502306, nBits=1e0ffff0, nNonce=4438800, vtx=1)
         *    CTransaction(hash=848a9da56d, ver=1, vin.size=1, vout.size=1, nLockTime=0, fPoWAlternative=false)
         *      CTxIn(COutPoint(0000000000000000000000000000000000000000000000000000000000000000, 4294967295), coinbase 04ffff001d01044c4c323032302d30372d31312054686520776f726c64277320666972737420636172626f6e206372656469742067656e65726174696e6720626c6f636b636861696e206279205a696f4661627279)
         *      CTxOut(nValue=0.00000000, scriptPubKey=4104678afdb0fe5548271967f1a671)
         */
        genesis = CreateGenesisBlock(1594502306, 4438800, 0x1e0ffff0, 1, 0 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x000005bd970b7d83eb879472fb48b2c01ed8155d7126ac3e0c201755c0c85c23"));
        assert(genesis.hashMerkleRoot     == uint256S("0x848a9da56df8cf4057ef911b7a1837048bea98c1e782b6eff779fd0325c77530"));

        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // PIVX starting difficulty is 1 / 2^12
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nBudgetCycleBlocks = 43200;       // approx. 1 every 30 days
        consensus.nBudgetFeeConfirmations = 6;      // Number of confirmations for the finalization fee
        consensus.nCoinbaseMaturity = 100;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMasternodeCountDrift = 20;       // num of MN we allow the see-saw payments to be off by
        consensus.nMaxMoneyOut = 10191520 * COIN;
        consensus.nPoolMaxTransactions = 3;
        consensus.nProposalEstablishmentTime = 60 * 60 * 24;    // must be at least a day old to make it into a budget
        consensus.nStakeMinAge = 60 * 60;
        consensus.nStakeMinDepth = 600;
        consensus.nTargetTimespan = 40 * 60;
        consensus.nTargetTimespanV2 = 30 * 60;
        consensus.nTargetSpacing = 1 * 60;
        consensus.nTimeSlotLength = 15;
        consensus.nMaxProposalPayments = 6;

        // spork keys
        consensus.strSporkPubKey                         = "045383382ba6fb469d8acd2c5de66ebbad0c636cf5bb23d82096aecd5262914a0fc230d6a1229dfe142325c3df867913f1efc159921a2292942628f2b500f65b06";
        consensus.strSporkPubKeyOld                      = "";
        consensus.nTime_EnforceNewSporkKey               = 0;
        consensus.nTime_RejectOldSporkKey                = 0;

        // height-based activations
        consensus.height_last_ZC_AccumCheckpoint         = 0;
        consensus.height_last_ZC_WrappedSerials          = 0;
        consensus.height_start_InvalidUTXOsCheck         = 999999999;
        consensus.height_start_ZC_InvalidSerials         = 0;
        consensus.height_start_ZC_SerialRangeCheck       = 999999999;
        consensus.height_ZC_RecalcAccumulators           = 999999999;

        // validation by-pass
        consensus.nCariBadBlockTime                      = 1471401614;    // Skip nBit validation of Block 259201 per PR #915
        consensus.nCariBadBlockBits                      = 0x1c056dac;    // Skip nBit validation of Block 259201 per PR #915

        // Zerocoin-related params
        consensus.ZC_Modulus = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
                "4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
                "6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
                "7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
                "8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
                "31438167899885040445364023527381951378636564391212010397122822120720357";
        consensus.ZC_MaxPublicSpendsPerTx = 637;    // Assume about 220 bytes each input
        consensus.ZC_MaxSpendsPerTx = 7;            // Assume about 20kb each input
        consensus.ZC_MinMintConfirmations = 20;
        consensus.ZC_MinMintFee = 1 * CENT;
        consensus.ZC_MinStakeDepth = 200;
        consensus.ZC_TimeStart                           = 1594503306;

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight =
                Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight =
                Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight           = 5001;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight        = 5010;
        consensus.vUpgrades[Consensus::UPGRADE_ZC].nActivationHeight            = 5050;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].nActivationHeight         = 5100;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight         = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].nActivationHeight     = 6000;
        consensus.vUpgrades[Consensus::UPGRADE_V3_4].nActivationHeight          = 5300;
        consensus.vUpgrades[Consensus::UPGRADE_V4_0].nActivationHeight          = 5400;
        consensus.vUpgrades[Consensus::UPGRADE_V5_0].nActivationHeight          = 2700500;

        consensus.vUpgrades[Consensus::UPGRADE_ZC].hashActivationBlock          = uint256S("0x1");
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].hashActivationBlock       = uint256S("0x1");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock       = uint256S("0x000002c598d8323498d1e491f1d59ce4622e67d276bdd1398ff39cd7f67b63bf");
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].hashActivationBlock   = uint256S("0x1");
        consensus.vUpgrades[Consensus::UPGRADE_V3_4].hashActivationBlock        = uint256S("0x1");
        consensus.vUpgrades[Consensus::UPGRADE_V4_0].hashActivationBlock        = uint256S("0x1");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x8e;
        pchMessageStart[1] = 0xc3;
        pchMessageStart[2] = 0xfb;
        pchMessageStart[3] = 0xe8;
        nDefaultPort       = 31813;

        // Note that of those with the service bits flag, most only support a subset of possible options
        vSeeds.push_back(CDNSSeedData("cri.eco", "mainnet.seed.cri.eco", true));                        // Official DNS Seeder
        vSeeds.push_back(CDNSSeedData("ziofabry.twt.it", "mainnet.cari.seed.ziofabry.twt.it", true));   // Secondary DNS Seeder from ZioFabry

        base58Prefixes[PUBKEY_ADDRESS]  = std::vector<unsigned char>(1, 28);        // Start with 'C' from https://en.bitcoin.it/wiki/List_of_address_prefixes
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 13);
        base58Prefixes[STAKING_ADDRESS] = std::vector<unsigned char>(1, 63);     // starting with 'S'
        base58Prefixes[SECRET_KEY]      = std::vector<unsigned char>(1, 43);        // Start with 'J' from https://en.bitcoin.it/wiki/List_of_address_prefixes
        base58Prefixes[EXT_PUBLIC_KEY]  = boost::assign::list_of(0x04)(0x2F)(0x27)(0x36).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY]  = boost::assign::list_of(0x04)(0x1F)(0x35)(0x2E).convert_to_container<std::vector<unsigned char> >();
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE]   = boost::assign::list_of(0x80)(0x00)(0x03)(0x5f).convert_to_container<std::vector<unsigned char> >();   // 0x8000035f

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        // Sapling
        bech32HRPs[SAPLING_PAYMENT_ADDRESS]      = "ps";
        bech32HRPs[SAPLING_FULL_VIEWING_KEY]     = "pviews";
        bech32HRPs[SAPLING_INCOMING_VIEWING_KEY] = "pivks";
        bech32HRPs[SAPLING_EXTENDED_SPEND_KEY]   = "p-secret-spending-key-main";
        bech32HRPs[SAPLING_EXTENDED_FVK]         = "pxviews";
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }

};
static CMainParams mainParams;

/**
 * Testnet (v5)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";

        /**
         *  CBlock(hash=000005bd970b7d83eb879472fb48b2c01ed8155d7126ac3e0c201755c0c85c23, ver=1, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000, hashMerkleRoot=848a9da56df8cf4057ef911b7a1837048bea98c1e782b6eff779fd0325c77530, nTime=1594502306, nBits=1e0ffff0, nNonce=4438800, vtx=1)
         *    CTransaction(hash=848a9da56d, ver=1, vin.size=1, vout.size=1, nLockTime=0, fPoWAlternative=false)
         *      CTxIn(COutPoint(0000000000000000000000000000000000000000000000000000000000000000, 4294967295), coinbase 04ffff001d01044c4c323032302d30372d31312054686520776f726c64277320666972737420636172626f6e206372656469742067656e65726174696e6720626c6f636b636861696e206279205a696f4661627279)
         *      CTxOut(nValue=0.00000000, scriptPubKey=4104678afdb0fe5548271967f1a671)
         */
        genesis = CreateGenesisBlock(1594502306, 4438800, 0x1e0ffff0, 1, 0 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x000005bd970b7d83eb879472fb48b2c01ed8155d7126ac3e0c201755c0c85c23"));
        assert(genesis.hashMerkleRoot     == uint256S("0x848a9da56df8cf4057ef911b7a1837048bea98c1e782b6eff779fd0325c77530"));

        consensus.fPowAllowMinDifficultyBlocks           = false;
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // PIVX starting difficulty is 1 / 2^12
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nBudgetCycleBlocks                     = 43200;                  // approx. 1 every 30 days
        consensus.nBudgetFeeConfirmations                = 6;                      // Number of confirmations for the finalization fee
        consensus.nCoinbaseMaturity                      = 100;
        consensus.nFutureTimeDriftPoW                    = 7200;
        consensus.nFutureTimeDriftPoS                    = 180;
        consensus.nMasternodeCountDrift                  = 20;                     // num of MN we allow the see-saw payments to be off by
        consensus.nMaxMoneyOut                           = 10191520 * COIN;
        consensus.nPoolMaxTransactions                   = 3;
        consensus.nProposalEstablishmentTime             = 60 * 60 * 24;           // must be at least a day old to make it into a budget
        consensus.nStakeMinAge = 60 * 60;
        consensus.nStakeMinDepth                         = 600;
        consensus.nTargetTimespan = 40 * 60;
        consensus.nTargetTimespanV2 = 30 * 60;
        consensus.nTargetSpacing = 1 * 60;
        consensus.nTimeSlotLength = 15;
        consensus.nMaxProposalPayments = 20;

        // spork keys
        consensus.strSporkPubKey                         = "049704039ba627d532b2737bfa83c5d65e964e472207432c52114981001a369de959343e61435c540f832d5297708b062e832d47efa0624966c5283fdd6c38cd9d";
        consensus.strSporkPubKeyOld                      = "";
        consensus.nTime_EnforceNewSporkKey               = 0;
        consensus.nTime_RejectOldSporkKey                = 0;

        // height based activations
        consensus.height_last_ZC_AccumCheckpoint         = 0;
        consensus.height_last_ZC_WrappedSerials          = 0;
        consensus.height_start_InvalidUTXOsCheck = 999999999;
        consensus.height_start_ZC_InvalidSerials         = 0;
        consensus.height_start_ZC_SerialRangeCheck       = 999999999;
        consensus.height_ZC_RecalcAccumulators = 999999999;

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight =
                Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight =
                Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight           = 5001;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight        = 5010;
        consensus.vUpgrades[Consensus::UPGRADE_ZC].nActivationHeight            = 5050;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].nActivationHeight         = 5100;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight         = 201;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].nActivationHeight     = 5200;
        consensus.vUpgrades[Consensus::UPGRADE_V3_4].nActivationHeight          = 5300;
        consensus.vUpgrades[Consensus::UPGRADE_V4_0].nActivationHeight          = 5400;
        consensus.vUpgrades[Consensus::UPGRADE_V5_0].nActivationHeight          = 201;

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x8c;
        pchMessageStart[1] = 0xc2;
        pchMessageStart[2] = 0xfa;
        pchMessageStart[3] = 0xe7;
        nDefaultPort       = 31815;

        // Note that of those with the service bits flag, most only support a subset of possible options
        vSeeds.push_back(CDNSSeedData("cri.eco", "testnet.seed.cri.eco", true));                        // Official DNS Seeder
        vSeeds.push_back(CDNSSeedData("ziofabry.twt.it", "mainnet.cari.seed.ziofabry.twt.it", true));   // Secondary DNS Seeder from ZioFabry

        base58Prefixes[PUBKEY_ADDRESS]  = std::vector<unsigned char>(1, 88);        // Start with 'c' from https://en.bitcoin.it/wiki/List_of_address_prefixes
        base58Prefixes[SCRIPT_ADDRESS]  = std::vector<unsigned char>(1, 11);        // Start with '5' from https://en.bitcoin.it/wiki/List_of_address_prefixes
        base58Prefixes[STAKING_ADDRESS] = std::vector<unsigned char>(1,125);        // Start with 's' from https://en.bitcoin.it/wiki/List_of_address_prefixes
        base58Prefixes[SECRET_KEY]      = std::vector<unsigned char>(1,105);        // Start with 'j' from https://en.bitcoin.it/wiki/List_of_address_prefixes

        base58Prefixes[EXT_PUBLIC_KEY]  = boost::assign::list_of(0x04)(0x2C)(0x25)(0x34).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY]  = boost::assign::list_of(0x04)(0x1C)(0x33)(0x2C).convert_to_container<std::vector<unsigned char> >();

        // Testnet pivx BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        // Sapling
        bech32HRPs[SAPLING_PAYMENT_ADDRESS]      = "ptestsapling";
        bech32HRPs[SAPLING_FULL_VIEWING_KEY]     = "pviewtestsapling";
        bech32HRPs[SAPLING_INCOMING_VIEWING_KEY] = "pivktestsapling";
        bech32HRPs[SAPLING_EXTENDED_SPEND_KEY]   = "p-secret-spending-key-test";
        bech32HRPs[SAPLING_EXTENDED_FVK]         = "pxviewtestsapling";
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

        /**
         *  CBlock(hash=000005bd970b7d83eb879472fb48b2c01ed8155d7126ac3e0c201755c0c85c23, ver=1, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000, hashMerkleRoot=848a9da56df8cf4057ef911b7a1837048bea98c1e782b6eff779fd0325c77530, nTime=1594502306, nBits=1e0ffff0, nNonce=4438800, vtx=1)
         *    CTransaction(hash=848a9da56d, ver=1, vin.size=1, vout.size=1, nLockTime=0, fPoWAlternative=false)
         *      CTxIn(COutPoint(0000000000000000000000000000000000000000000000000000000000000000, 4294967295), coinbase 04ffff001d01044c4c323032302d30372d31312054686520776f726c64277320666972737420636172626f6e206372656469742067656e65726174696e6720626c6f636b636861696e206279205a696f4661627279)
         *      CTxOut(nValue=0.00000000, scriptPubKey=4104678afdb0fe5548271967f1a671)
         */
        genesis = CreateGenesisBlock(1594502306, 4438800, 0x1e0ffff0, 1, 0 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x000005bd970b7d83eb879472fb48b2c01ed8155d7126ac3e0c201755c0c85c23"));
        assert(genesis.hashMerkleRoot     == uint256S("0x848a9da56df8cf4057ef911b7a1837048bea98c1e782b6eff779fd0325c77530"));

        consensus.fPowAllowMinDifficultyBlocks           = false;
        consensus.powLimit                               = ~UINT256_ZERO >> 20;    // CARI starting difficulty is 1 / 2^12
        consensus.posLimitV1                             = ~UINT256_ZERO >> 24;
        consensus.posLimitV2                             = ~UINT256_ZERO >> 20;
        consensus.nBudgetCycleBlocks                     = 43200;                  // approx. 1 every 30 days
        consensus.nBudgetFeeConfirmations                = 6;                      // Number of confirmations for the finalization fee
        consensus.nCoinbaseMaturity                      = 100;
        consensus.nFutureTimeDriftPoW                    = 7200;
        consensus.nFutureTimeDriftPoS                    = 180;
        consensus.nMasternodeCountDrift                  = 20;                     // num of MN we allow the see-saw payments to be off by
        consensus.nMaxMoneyOut                           = 10191520 * COIN;
        consensus.nPoolMaxTransactions                   = 3;
        consensus.nProposalEstablishmentTime             = 60 * 60 * 24;           // must be at least a day old to make it into a budget
        consensus.nStakeMinAge                           = 60 * 60;
        consensus.nStakeMinDepth                         = 600;
        consensus.nTargetTimespan                        = 40 * 60;
        consensus.nTargetTimespanV2                      = 30 * 60;
        consensus.nTargetSpacing                         = 1 * 60;
        consensus.nTimeSlotLength                        = 15;

        // spork keys

        /*
         *  {
         *      "PublicKey": "04887731e4049029f4d41bf745016960256bf903ccffdd2eb341e444946ccb87122ce46d12f3941fb643b6fa3a6e384d94db60aa670ed44ff016a5fdff1254fe46",
         *      "PrivateKey": "4Y739MmKdfhXwdrCDz52CgR9aK2Ctcm8zz1qBbpCTk95tZwzJHK"
         *  }
         */

        consensus.strSporkPubKey                         = "04887731e4049029f4d41bf745016960256bf903ccffdd2eb341e444946ccb87122ce46d12f3941fb643b6fa3a6e384d94db60aa670ed44ff016a5fdff1254fe46";
        consensus.strSporkPubKeyOld                      = "";
        consensus.nTime_EnforceNewSporkKey               = 0;
        consensus.nTime_RejectOldSporkKey                = 0;

        // height-based activations
        consensus.height_last_ZC_AccumCheckpoint         = 0;
        consensus.height_last_ZC_WrappedSerials          = 0;
        consensus.height_start_InvalidUTXOsCheck         = 999999999;
        consensus.height_start_ZC_InvalidSerials         = 0;
        consensus.height_start_ZC_SerialRangeCheck       = 999999999;
        consensus.height_ZC_RecalcAccumulators           = 999999999;

        // validation by-pass
        consensus.nCariBadBlockTime                      = 1471401614;    // Skip nBit validation of Block 259201 per PR #915
        consensus.nCariBadBlockBits                      = 0x1c056dac;    // Skip nBit validation of Block 259201 per PR #915

        // Zerocoin-related params
        consensus.ZC_Modulus = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
                "4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
                "6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
                "7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
                "8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
                "31438167899885040445364023527381951378636564391212010397122822120720357";
        consensus.ZC_MaxPublicSpendsPerTx = 637;    // Assume about 220 bytes each input
        consensus.ZC_MaxSpendsPerTx = 7;            // Assume about 20kb each input
        consensus.ZC_MinMintConfirmations                = 20;
        consensus.ZC_MinMintFee = 1 * CENT;
        consensus.ZC_MinStakeDepth                       = 200;
        consensus.ZC_TimeStart                           = 1508214600;  // October 17, 2017 4:30:00 AM

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight =
                Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight =
                Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight           = 5001;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight        = 5010;
        consensus.vUpgrades[Consensus::UPGRADE_ZC].nActivationHeight            = 5050;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_V2].nActivationHeight         = 5100;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight         =
                Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_ZC_PUBLIC].nActivationHeight     = 5200;
        consensus.vUpgrades[Consensus::UPGRADE_V3_4].nActivationHeight          = 5300;
        consensus.vUpgrades[Consensus::UPGRADE_V4_0].nActivationHeight          = 5400;
        consensus.vUpgrades[Consensus::UPGRADE_V5_0].nActivationHeight          = 300;

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xa0;
        pchMessageStart[1] = 0xb0;
        pchMessageStart[2] = 0xc0;
        pchMessageStart[3] = 0xe0;
        nDefaultPort       = 31817;

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }

    void UpdateNetworkUpgradeParameters(Consensus::UpgradeIndex idx, int nActivationHeight)
    {
        assert(idx > Consensus::BASE_NETWORK && idx < Consensus::MAX_NETWORK_UPGRADES);
        consensus.vUpgrades[idx].nActivationHeight = nActivationHeight;
    }
};
static CRegTestParams regTestParams;

static CChainParams* pCurrentParams = 0;

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

void UpdateNetworkUpgradeParameters(Consensus::UpgradeIndex idx, int nActivationHeight)
{
    regTestParams.UpdateNetworkUpgradeParameters(idx, nActivationHeight);
}
