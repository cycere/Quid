// Copyright (c) 2011-2016 The Cryptonote developers
// Copyright (c) 2017-2021 The Cycere developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include <vector>
#include <unordered_map>

#include "QuidCore/Account.h"
#include "QuidCore/QuidBasic.h"
#include "QuidCore/Currency.h"
#include "QuidCore/BlockchainIndices.h"
#include "crypto/hash.h"

#include "../TestGenerator/TestGenerator.h"

class TestBlockchainGenerator
{
public:
  TestBlockchainGenerator(const Quid::Currency& currency);

  //TODO: get rid of this method
  std::vector<Quid::Block>& getBlockchain();
  std::vector<Quid::Block> getBlockchainCopy();
  void generateEmptyBlocks(size_t count);
  bool getBlockRewardForAddress(const Quid::AccountPublicAddress& address);
  bool generateTransactionsInOneBlock(const Quid::AccountPublicAddress& address, size_t n);
  bool getSingleOutputTransaction(const Quid::AccountPublicAddress& address, uint64_t amount);
  void addTxToBlockchain(const Quid::Transaction& transaction);
  bool getTransactionByHash(const Crypto::Hash& hash, Quid::Transaction& tx, bool checkTxPool = false);
  const Quid::AccountBase& getMinerAccount() const;
  bool generateFromBaseTx(const Quid::AccountBase& address);

  void putTxToPool(const Quid::Transaction& tx);
  void getPoolSymmetricDifference(std::vector<Crypto::Hash>&& known_pool_tx_ids, Crypto::Hash known_block_id, bool& is_bc_actual,
    std::vector<Quid::Transaction>& new_txs, std::vector<Crypto::Hash>& deleted_tx_ids);
  void putTxPoolToBlockchain();
  void clearTxPool();

  void cutBlockchain(uint32_t height);

  bool addOrphan(const Crypto::Hash& hash, uint32_t height);
  bool getGeneratedTransactionsNumber(uint32_t height, uint64_t& generatedTransactions);
  bool getOrphanBlockIdsByHeight(uint32_t height, std::vector<Crypto::Hash>& blockHashes);
  bool getBlockIdsByTimestamp(uint64_t timestampBegin, uint64_t timestampEnd, uint32_t blocksNumberLimit, std::vector<Crypto::Hash>& hashes, uint32_t& blocksNumberWithinTimestamps);
  bool getPoolTransactionIdsByTimestamp(uint64_t timestampBegin, uint64_t timestampEnd, uint32_t transactionsNumberLimit, std::vector<Crypto::Hash>& hashes, uint64_t& transactionsNumberWithinTimestamps);
  bool getTransactionIdsByPaymentId(const Crypto::Hash& paymentId, std::vector<Crypto::Hash>& transactionHashes);

  bool getTransactionGlobalIndexesByHash(const Crypto::Hash& transactionHash, std::vector<uint32_t>& globalIndexes);
  bool getMultisignatureOutputByGlobalIndex(uint64_t amount, uint32_t globalIndex, Quid::MultisignatureOutput& out);
  void setMinerAccount(const Quid::AccountBase& account);

private:
  struct MultisignatureOutEntry {
    Crypto::Hash transactionHash;
    uint16_t indexOut;
  };

  struct KeyOutEntry {
    Crypto::Hash transactionHash;
    uint16_t indexOut;
  };
  
  void addGenesisBlock();
  void addMiningBlock();

  const Quid::Currency& m_currency;
  test_generator generator;
  Quid::AccountBase miner_acc;
  std::vector<Quid::Block> m_blockchain;
  std::unordered_map<Crypto::Hash, Quid::Transaction> m_txs;
  std::unordered_map<Crypto::Hash, std::vector<uint32_t>> transactionGlobalOuts;
  std::unordered_map<uint64_t, std::vector<MultisignatureOutEntry>> multisignatureOutsIndex;
  std::unordered_map<uint64_t, std::vector<KeyOutEntry>> keyOutsIndex;

  std::unordered_map<Crypto::Hash, Quid::Transaction> m_txPool;
  mutable std::mutex m_mutex;

  Quid::PaymentIdIndex m_paymentIdIndex;
  Quid::TimestampTransactionsIndex m_timestampIndex;
  Quid::GeneratedTransactionsIndex m_generatedTransactionsIndex;
  Quid::OrphanBlocksIndex m_orthanBlocksIndex;

  void addToBlockchain(const Quid::Transaction& tx);
  void addToBlockchain(const std::vector<Quid::Transaction>& txs);
  void addToBlockchain(const std::vector<Quid::Transaction>& txs, const Quid::AccountBase& minerAddress);
  void addTx(const Quid::Transaction& tx);

  bool doGenerateTransactionsInOneBlock(Quid::AccountPublicAddress const &address, size_t n);
};
