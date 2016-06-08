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
    
    namespace on_surrender_parameters {
        /**
         * Message user info key for the player index.
         */
        const kettle::utils::StringHash kMessageKeyPlayerIndex("Player index");
    }
    
    /**
     * Handles the current player surrendering. Sends this event as a message.
     *
     * @param context   The game context.
     */
    void onPlayerSurrender(MatchContext * context);
} // namespace game

#endif /* OnPlayerSurrender_hpp */
