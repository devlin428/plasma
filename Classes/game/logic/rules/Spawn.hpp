//
//  Spawn.hpp
//  tests
//
//  Created by Derek Higgs on 6/8/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

#ifndef Spawn_hpp
#define Spawn_hpp

#include "BoardTypes.h"

#include "StringHash.hpp"

namespace kettle {
namespace utils {
    class ISender;
    class UserInfo;
} // namespace utils
} // namespace kettle

namespace game {
    struct MatchContext;
    
    /**
     * Message for a spawn action failing.
     */
    const kettle::utils::hash_t kSpawnFailed = kettle::utils::hashCString("Spawn Failed");
    
    /**
     * Spawns a piece.
     *
     * @param context                               The match context.
     * @param spawn_positions_by_player_index       The spawn positions for
     *                                              each player.
     * @param spawn_position_count_by_player_index  The spawn limit for each
     *                                              player.
     * @param message_sender                        The sender of the message
     *                                              for the spawn message.
     * @param action_parameters                     The parameters to perform
     *                                              the spawn.
     */
    void spawnPiece(MatchContext * context,
                    const positionid_t * const * spawn_positions_by_player_index,
                    const unsigned int * spawn_position_count_by_player_index,
                    const kettle::utils::ISender * message_sender,
                    const kettle::utils::UserInfo * action_parameters);
}

#endif /* Spawn_hpp */
