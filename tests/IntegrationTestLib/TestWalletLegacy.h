// Copyright (c) 2011-2016 The Cryptonote developers
// Copyright (c) 2017-2021 The Cycere developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include "QuidCore/Currency.h"
#include "INode.h"
#include "IWalletLegacy.h"
#include "System/Dispatcher.h"
#include "System/Event.h"
#include "WalletLegacy/WalletLegacy.h"

namespace Tests {
namespace Common {

class TestWalletLegacy : private Quid::IWalletLegacyObserver {
public:
  TestWalletLegacy(System::Dispatcher& dispatcher, const Quid::Currency& currency, Quid::INode& node);
  ~TestWalletLegacy();

  std::error_code init();
  std::error_code sendTransaction(const std::string& address, uint64_t amount, Crypto::Hash& txHash);
  void waitForSynchronizationToHeight(uint32_t height);
  Quid::IWalletLegacy* wallet();
  Quid::AccountPublicAddress address() const;

protected:
  virtual void synchronizationCompleted(std::error_code result) override;
  virtual void synchronizationProgressUpdated(uint32_t current, uint32_t total) override;

private:
  System::Dispatcher& m_dispatcher;
  System::Event m_synchronizationCompleted;
  System::Event m_someTransactionUpdated;

  Quid::INode& m_node;
  const Quid::Currency& m_currency;
  std::unique_ptr<Quid::IWalletLegacy> m_wallet;
  std::unique_ptr<Quid::IWalletLegacyObserver> m_walletObserver;
  uint32_t m_currentHeight;
  uint32_t m_synchronizedHeight;
  std::error_code m_lastSynchronizationResult;
};

}
}
