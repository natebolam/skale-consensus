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

    @file BVBroadcastMessage.cpp
    @author Stan Kladko
    @date 2018
*/

#include "SkaleCommon.h"
#include "Log.h"
#include "exceptions/FatalError.h"

#include "messages/NetworkMessage.h"

#include "chains/Schain.h"
#include "protocols/ProtocolKey.h"
#include "protocols/ProtocolInstance.h"
#include "BinConsensusInstance.h"

#include "BVBroadcastMessage.h"


BVBroadcastMessage::BVBroadcastMessage(block_id _blockID, schain_index _blockProposerIndex, bin_consensus_round r,
                                       bin_consensus_value value, BinConsensusInstance &sourceProtocolInstance)
        : NetworkMessage(MSG_BVB_BROADCAST, _blockID, _blockProposerIndex, r, value,
                         sourceProtocolInstance) {
    printPrefix = "b";
}


BVBroadcastMessage::BVBroadcastMessage(node_id _srcNodeID, block_id _blockID, schain_index _blockProposerIndex,
                                       bin_consensus_round _r,
                                       bin_consensus_value _value, schain_id _schainId, msg_id _msgID,
                                       schain_index _srcSchainIndex,
                                       Schain *_sChain)
    : NetworkMessage(
        MSG_BVB_BROADCAST, _srcNodeID, _blockID, _blockProposerIndex, _r, _value, _schainId, _msgID,
        nullptr,
        _srcSchainIndex, _sChain->getCryptoManager()) {
    printPrefix = "b";
};

