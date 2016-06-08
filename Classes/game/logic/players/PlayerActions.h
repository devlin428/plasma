//
//  PlayerActions.h
//  tests
//
//  Created by Derek Higgs on 6/6/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

#ifndef PlayerActions_h
#define PlayerActions_h

#include "StringHash.hpp"

namespace game {
    namespace player_action {
        /**
         * Type to specify to the player the current phase to know what actions
         * are legal.
         */
        typedef kettle::utils::StringHash phase_t;
        
        /**
         * Type for keying parameters for a player acting for a phase.
         */
        typedef kettle::utils::StringHash player_parameter_key_t;
        
        /**
         * Type for the player's actions.
         */
        typedef kettle::utils::StringHash action_t;
        
        /**
         * Type for keying parameters for a player action.
         */
        typedef kettle::utils::StringHash action_parameter_key_t;
        
        /**
         * Common action for the player to not make a move right now.
         */
        const action_t kThinking("Thinking");
        
        /**
         * Common action for leaving a game abrubtly. The phase rules should
         * handle this action whenever the player can act.
         */
        const action_t kSurrender("Surrender");
    } // namespace player_action
} // namespace game

#endif /* PlayerActions_h */
