//
//  OnPlayerSurrender.hpp
//  tests
//
//  Created by Derek Higgs on 6/6/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

#ifndef OnPlayerSurrender_hpp
#define OnPlayerSurrender_hpp

#include "StringHash.hpp"

namespace game {
    struct MatchContext;
    
    /**
     * Handles the current player surrendering. Sends this event as a message.
     *
     * @param context   The game context.
     */
    void onPlayerSurrender(MatchContext * context);
} // namespace game

#endif /* OnPlayerSurrender_hpp */
