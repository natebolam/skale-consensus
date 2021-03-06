/*
    Copyright (C) 2019 SKALE Labs

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

    @file MsgDB.cpp
    @author Stan Kladko
    @date 2019
*/


#include "SkaleCommon.h"
#include "Log.h"
#include "crypto/SHAHash.h"
#include "chains/Schain.h"
#include "exceptions/InvalidStateException.h"
#include "messages/NetworkMessage.h"

#include "MsgDB.h"
#include "network/Buffer.h"
#include "CacheLevelDB.h"


MsgDB::MsgDB(Schain *_sChain, string &_dirName, string &_prefix, node_id _nodeId, uint64_t _maxDBSize)
        : CacheLevelDB(_sChain, _dirName, _prefix,
                       _nodeId, _maxDBSize, false) {
}


bool
MsgDB::saveMsg(ptr<NetworkMessage> _msg) {

    static atomic<uint64_t> msgCounter = 0;

    lock_guard<recursive_mutex> lock(m);

    try {


        CHECK_STATE(_msg);


        auto s = _msg->serializeToString();

        auto currentCounter = msgCounter++;

        auto key = createKey(_msg->getBlockID(), currentCounter);

        auto previous = readString(*key);

        if (previous == nullptr) {
            writeString(*key, *s);
            return true;
        }

        return (*previous == *s);

    } catch (...) {
        throw_with_nested(InvalidStateException(__FUNCTION__, __CLASS_NAME__));
    }

}

ptr<vector<ptr<NetworkMessage>>> MsgDB::getMessages(block_id _blockID) {


    auto result = make_shared<vector<ptr<NetworkMessage>>>();

    lock_guard<recursive_mutex> lock(m);



    try {


        string prefix = getFormatVersion() + ":" + to_string(_blockID);

        auto messages = readPrefixRange(prefix);

        if (!messages)
            return result;

        for (auto&& message : *messages) {
            result->push_back(NetworkMessage::parseMessage(message.second, getSchain()));
        }

        return result;


    } catch (...) {
        throw_with_nested(InvalidStateException(__FUNCTION__, __CLASS_NAME__));
    }

}

const string MsgDB::getFormatVersion() {
    return "1.0";
}





