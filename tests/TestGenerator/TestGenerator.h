// Copyright (c) 2011-2016 The Cryptonote developers
// Copyright (c) 2017-2021 The Cycere developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include <cstdint>
#include <list>
#include <vector>
#include <unordered_map>

#include "crypto/hash.h"
#include "QuidCore/QuidBasic.h"
#include "QuidCore/QuidBasicImpl.h"
#include "QuidCore/QuidFormatUtils.h"
#include "QuidCore/Currency.h"
#include "QuidCore/Difficulty.h"


class test_generator
{
public:
  struct BlockInfo {
    BlockInfo()
      : previousBlockHash()
      , alreadyGeneratedCoins(0)
      , blockSize(0) {
    }

    BlockInfo(Crypto::Hash aPrevId, uint64_t anAlreadyGeneratedCoins, size_t aBlockSize)
      : previousBlockHash(aPrevId)
      , alreadyGeneratedCoins(anAlreadyGeneratedCoins)
      , blockSize(aBlockSize) {
    }

    Crypto::Hash previousBlockHash;
    uint64_t alreadyGeneratedCoins;
    size_t blockSize;
  };

  enum BlockFields {
    bf_none      = 0,
    bf_major_ver = 1 << 0,
    bf_minor_ver = 1 << 1,
    bf_timestamp = 1 << 2,
    bf_prev_id   = 1 << 3,
    bf_miner_tx  = 1 << 4,
    bf_tx_hashes = 1 << 5,
    bf_diffic    = 1 << 6
  };

  test_generator(const Quid::Currency& currency, uint8_t majorVersion = Quid::BLOCK_MAJOR_VERSION_1,
                 uint8_t minorVersion = Quid::BLOCK_MINOR_VERSION_0)
    : m_currency(currency), defaultMajorVersion(majorVersion), defaultMinorVersion(minorVersion) {
  }


  uint8_t defaultMajorVersion;
  uint8_t defaultMinorVersion;

  const Quid::Currency& currency() const { return m_currency; }

  void getBlockchain(std::vector<BlockInfo>& blockchain, const Crypto::Hash& head, size_t n) const;
  void getLastNBlockSizes(std::vector<size_t>& blockSizes, const Crypto::Hash& head, size_t n) const;
  uint64_t getAlreadyGeneratedCoins(const Crypto::Hash& blockId) const;
  uint64_t getAlreadyGeneratedCoins(const Quid::Block& blk) const;

  void addBlock(const Quid::Block& blk, size_t tsxSize, uint64_t fee, std::vector<size_t>& blockSizes,
    uint64_t alreadyGeneratedCoins);
  bool constructBlock(Quid::Block& blk, uint32_t height, const Crypto::Hash& previousBlockHash,
    const Quid::AccountBase& minerAcc, uint64_t timestamp, uint64_t alreadyGeneratedCoins,
    std::vector<size_t>& blockSizes, const std::list<Quid::Transaction>& txList);
  bool constructBlock(Quid::Block& blk, const Quid::AccountBase& minerAcc, uint64_t timestamp);
  bool constructBlock(Quid::Block& blk, const Quid::Block& blkPrev, const Quid::AccountBase& minerAcc,
    const std::list<Quid::Transaction>& txList = std::list<Quid::Transaction>());

  bool constructBlockManually(Quid::Block& blk, const Quid::Block& prevBlock,
    const Quid::AccountBase& minerAcc, int actualParams = bf_none, uint8_t majorVer = 0,
    uint8_t minorVer = 0, uint64_t timestamp = 0, const Crypto::Hash& previousBlockHash = Crypto::Hash(),
    const Quid::difficulty_type& diffic = 1, const Quid::Transaction& baseTransaction = Quid::Transaction(),
    const std::vector<Crypto::Hash>& transactionHashes = std::vector<Crypto::Hash>(), size_t txsSizes = 0, uint64_t fee = 0);
  bool constructBlockManuallyTx(Quid::Block& blk, const Quid::Block& prevBlock,
    const Quid::AccountBase& minerAcc, const std::vector<Crypto::Hash>& transactionHashes, size_t txsSize);
  bool constructMaxSizeBlock(Quid::Block& blk, const Quid::Block& blkPrev,
    const Quid::AccountBase& minerAccount, size_t medianBlockCount = 0,
    const std::list<Quid::Transaction>& txList = std::list<Quid::Transaction>());

private:
  const Quid::Currency& m_currency;
  std::unordered_map<Crypto::Hash, BlockInfo> m_blocksInfo;
};

inline Quid::difficulty_type getTestDifficulty() { return 1; }
void fillNonce(Quid::Block& blk, const Quid::difficulty_type& diffic);

bool constructMinerTxManually(const Quid::Currency& currency, uint32_t height, uint64_t alreadyGeneratedCoins,
  const Quid::AccountPublicAddress& minerAddress, Quid::Transaction& tx, uint64_t fee,
  Quid::KeyPair* pTxKey = 0);
bool constructMinerTxBySize(const Quid::Currency& currency, Quid::Transaction& baseTransaction, uint32_t height,
  uint64_t alreadyGeneratedCoins, const Quid::AccountPublicAddress& minerAddress,
  std::vector<size_t>& blockSizes, size_t targetTxSize, size_t targetBlockSize, uint64_t fee = 0);
