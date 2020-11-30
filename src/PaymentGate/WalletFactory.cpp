// Copyright (c) 2011-2016 The Cryptonote developers
// Copyright (c) 2017-2021 The Cycere developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "WalletFactory.h"

#include "NodeRpcProxy/NodeRpcProxy.h"
#include "Wallet/WalletGreen.h"
#include "QuidCore/Currency.h"

#include <stdlib.h>
#include <future>

namespace PaymentService {

WalletFactory WalletFactory::factory;

WalletFactory::WalletFactory() {
}

WalletFactory::~WalletFactory() {
}

Quid::IWallet* WalletFactory::createWallet(const Quid::Currency& currency, Quid::INode& node, System::Dispatcher& dispatcher) {
  Quid::IWallet* wallet = new Quid::WalletGreen(dispatcher, currency, node);
  return wallet;
}

}
