//
//  CollisionLayer.hpp
//  Plazma Lights Off
//
//  Created by Derek Higgs on 5/30/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

/**
 * Flags are used to set what board spaces allow passing and moving.
 *
 * If a piece shares a block flag with a board space, then that piece cannot
 * land on that space. If a piece shares a pass flag with a board space, then
 * that piece may move over that space.
 *
 * If a space can be passed, but is blocked, then the piece can move over that
 * space, but not land on it. If a space is unblocked, but cannot be passed,
 * then the piece would have to land on that space.
 */

#ifndef CollisionLayer_hpp
#define CollisionLayer_hpp

#include "BoardTypes.h"

namespace game {

    const flags32_t BLOCK_ALL_FLAGS   = 0xffffffff;
    const flags32_t BLOCK_NONE_FLAGS  = 0x00000000;
    const flags32_t PASS_ALL_FLAGS    = 0xffffffff;
    const flags32_t PASS_NONE_FLAGS   = 0x00000000;

    flags32_t layerToFlag(collisionlayer_t collision_layer);
    
    void setFlag(collisionlayer_t collision_layer, flags32_t & io_flags);
    
    flags32_t stackCanBlockFlags(flags32_t flags_a, flags32_t flags_b);
    flags32_t stackCanPassFlags(flags32_t flags_a, flags32_t flags_b);
    
    bool isBlocked(flags32_t block_flags_a, flags32_t block_flags_b);
    bool isPassable(flags32_t pass_flags_a, flags32_t pass_flags_b);
} // namespace game

#endif /* CollisionLayer_hpp */
