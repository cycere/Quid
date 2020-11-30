// Copyright (c) 2011-2016 The Cryptonote developers
// Copyright (c) 2017-2021 The Cycere developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include "QuidCore/Account.h"
#include "QuidCore/QuidFormatUtils.h"
#include "QuidCore/Currency.h"

class TransactionBuilder {
public:

  typedef std::vector<Quid::AccountKeys> KeysVector;
  typedef std::vector<Crypto::Signature> SignatureVector;
  typedef std::vector<SignatureVector> SignatureMultivector;

  struct MultisignatureSource {
    Quid::MultisignatureInput input;
    KeysVector keys;
    Crypto::PublicKey srcTxPubKey;
    size_t srcOutputIndex;
  };

  TransactionBuilder(const Quid::Currency& currency, uint64_t unlockTime = 0);

  // regenerate transaction keys
  TransactionBuilder& newTxKeys();
  TransactionBuilder& setTxKeys(const Quid::KeyPair& txKeys);

  // inputs
  TransactionBuilder& setInput(const std::vector<Quid::TransactionSourceEntry>& sources, const Quid::AccountKeys& senderKeys);
  TransactionBuilder& addMultisignatureInput(const MultisignatureSource& source);

  // outputs
  TransactionBuilder& setOutput(const std::vector<Quid::TransactionDestinationEntry>& destinations);
  TransactionBuilder& addOutput(const Quid::TransactionDestinationEntry& dest);
  TransactionBuilder& addMultisignatureOut(uint64_t amount, const KeysVector& keys, uint32_t required);

  Quid::Transaction build() const;

  std::vector<Quid::TransactionSourceEntry> m_sources;
  std::vector<Quid::TransactionDestinationEntry> m_destinations;

private:

  void fillInputs(Quid::Transaction& tx, std::vector<Quid::KeyPair>& contexts) const;
  void fillOutputs(Quid::Transaction& tx) const;
  void signSources(const Crypto::Hash& prefixHash, const std::vector<Quid::KeyPair>& contexts, Quid::Transaction& tx) const;

  struct MultisignatureDestination {
    uint64_t amount;
    uint32_t requiredSignatures;
    KeysVector keys;
  };

  Quid::AccountKeys m_senderKeys;

  std::vector<MultisignatureSource> m_msigSources;
  std::vector<MultisignatureDestination> m_msigDestinations;

  size_t m_version;
  uint64_t m_unlockTime;
  Quid::KeyPair m_txKey;
  const Quid::Currency& m_currency;
};
