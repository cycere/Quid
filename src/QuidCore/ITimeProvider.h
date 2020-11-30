// Copyright (c) 2011-2016 The Cryptonote developers
// Copyright (c) 2017-2021 The Cycere developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include <time.h>

namespace Quid {

  struct ITimeProvider {
    virtual time_t now() = 0;
    virtual ~ITimeProvider() {}
  };

  struct RealTimeProvider : public ITimeProvider {
    virtual time_t now() override {
      return time(nullptr);
    }
  };

}
