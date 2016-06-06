//
//  EndCondition.hpp
//  tests
//
//  Created by Derek Higgs on 6/5/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

#ifndef EndCondition_hpp
#define EndCondition_hpp

#include "IMatchCondition.hpp"

namespace game {
    /**
     * Condition for the end of the game made by defining the win condition for
     * each player.
     *
     * Mind that multiple players could win.
     *
     * Note that no players could win by having more win conditions than
     * players. If an extra condition returns true and none of the actual player
     * conditions returns true, then the game has ended with no players winning.
     */
    class EndCondition : public IMatchCondition {
    public:
        /**
         * Constructs the end condition to be met when a player has met their
         * win condition.
         *
         * @param player_win_conditions     An array of conditions indexed by
         *                                  the player. When a condition is
         *                                  true, then the associated player has
         *                                  won. Takes ownership of each
         *                                  condition and the array.
         * @param number_of_players         The number of players.
         */
        EndCondition(const IMatchCondition * const * player_win_conditions,
                     unsigned int player_count);
        
        /**
         * Deconstructor
         */
        ~EndCondition();
        
        /**
         * Checks to see if the player has won.
         *
         * @param context       The game context.
         * @param player_index  The player index to check on winning.
         * @return              True if the player has won.
         */
        bool didPlayerWin(const MatchContext * context,
                          unsigned int player_index) const;
        
        /**
         * Checks to see if the game has ended by a player winning.
         */
        bool isMet(const MatchContext * context) const;
        
    protected:
        /**
         * An array of conditions indexed by the player. When a condition is
         * true, then the associated player has won.
         */
        const IMatchCondition * const * m_player_win_conditions;
        const unsigned int m_player_count;
        
    private:
        // disable copy and assign
        EndCondition(const EndCondition &);
        void operator=(const EndCondition &);
    }; // class EndCondition
} //

#endif /* EndCondition_hpp */
