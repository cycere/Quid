// Copyright (c) 2011-2016 The Cryptonote developers
// Copyright (c) 2017-2021 The Cycere developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "IQuidProtocolQueryStub.h"

bool IQuidProtocolQueryStub::addObserver(Quid::IQuidProtocolObserver* observer) {
  return false;
}

bool IQuidProtocolQueryStub::removeObserver(Quid::IQuidProtocolObserver* observer) {
  return false;
}

uint32_t IQuidProtocolQueryStub::getObservedHeight() const {
  return observedHeight;
}

size_t IQuidProtocolQueryStub::getPeerCount() const {
  return peers;
}

bool IQuidProtocolQueryStub::isSynchronized() const {
  return synchronized;
}

void IQuidProtocolQueryStub::setPeerCount(uint32_t count) {
  peers = count;
}

void IQuidProtocolQueryStub::setObservedHeight(uint32_t height) {
  observedHeight = height;
}

void IQuidProtocolQueryStub::setSynchronizedStatus(bool status) {
    synchronized = status;
}
