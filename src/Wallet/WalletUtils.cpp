// Copyright (c) 2011-2016 The Cryptonote developers
// Copyright (c) 2017-2021 The Cycere developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "WalletUtils.h"

#include "Quid.h"

namespace Quid {

bool validateAddress(const std::string& address, const Quid::Currency& currency) {
  Quid::AccountPublicAddress ignore;
  return currency.parseAccountAddressString(address, ignore);
}

}
