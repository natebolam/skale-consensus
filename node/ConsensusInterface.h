/*
    Copyright (C) 2018-2019 SKALE Labs

    This file is part of skale-consensus.

    skale-consensus is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published
    by the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    skale-consensus is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with skale-consensus.  If not, see <https://www.gnu.org/licenses/>.

    @file ConsensusInterface.h
    @author Stan Kladko
    @date 2018
*/

#ifndef CONSENSUSINTERFACE_H
#define CONSENSUSINTERFACE_H

#pragma GCC diagnostic ignored "-Wnon-virtual-dtor"

#include<boost/multiprecision/cpp_int.hpp>

#include <string>
#include <vector>

using u256 = boost::multiprecision::number<boost::multiprecision::backends::cpp_int_backend<256, 256,
        boost::multiprecision::unsigned_magnitude, boost::multiprecision::unchecked, void> >;

class ConsensusInterface {
public:
    virtual ~ConsensusInterface() = default;

    virtual void parseFullConfigAndCreateNode(const std::string &fullPathToConfigFile) = 0;

    virtual void startAll() = 0;

    virtual void bootStrapAll() = 0;

    virtual void exitGracefully() = 0;

    virtual u256 getPriceForBlockId(uint64_t _blockId) const = 0;

    virtual uint64_t getEmptyBlockIntervalMs() const { return -1; }

    virtual void setEmptyBlockIntervalMs(uint64_t) {}
};

/**
 * Through this interface Consensus interacts with the rest of the system
 */
class ConsensusExtFace {
public:
    typedef std::vector<std::vector<uint8_t> > transactions_vector;

    // Returns hashes and bytes of new transactions as well as state root to put into block proposal
    virtual transactions_vector pendingTransactions(size_t _limit, u256& _stateRoot) = 0;

    // Creates new block with specified transactions AND removes them from the queue
    virtual void createBlock(const transactions_vector &_approvedTransactions, uint64_t _timeStamp,
                             uint32_t _timeStampMillis, uint64_t _blockID, u256 _gasPrice,
                             u256 _stateRoot) = 0;

    virtual ~ConsensusExtFace() = default;

    virtual void terminateApplication() {};
};

#endif  // CONSENSUSINTERFACE_H
