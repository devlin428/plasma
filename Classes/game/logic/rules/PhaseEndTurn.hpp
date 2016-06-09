//
//  PhaseEndTurn.hpp
//  tests
//
//  Created by Derek Higgs on 6/9/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

#ifndef PhaseEndTurn_hpp
#define PhaseEndTurn_hpp

#include "IPhaseRule.hpp"

namespace game {
    /**
     * A phase for changing the current player's turn.
     */
    class PhaseEndTurn : public IPhaseRule {
    public:
        /**
         * Constructs the phase to change the turn by the specified amount.
         *
         * @param quicksave         Set to true to let a quicksave happen at the
         *                          end of the phase.
         * @param turn_increment    How many players to pass the turn over. The
         *                          default, 1, just changes turns to the next
         *                          player.
         */
        PhaseEndTurn(bool quicksave = true, unsigned int turn_increment = 1);
        
        /**
         * Deconstructor.
         */
        ~PhaseEndTurn();
        
        /**
         * Initializes the phase data.
         *
         * @param context           The match context.
         */
        void initialize(const MatchContext * context);
        
        /**
         * Updates the phase.
         *
         * @param context           The match context.
         * @return                  The reason this function returned.
         */
        PhaseUpdateBreakReason update(MatchContext * context);
        
    protected:
        /**
         * How many players to pass the turn over.
         */
        unsigned int m_turn_increment;
        
        /**
         * Whether the phase should end with a quicksave point.
         */
        bool m_quicksave;
        
    private:
        // disable copy and assign
        PhaseEndTurn(const PhaseEndTurn &);
        void operator=(const PhaseEndTurn &);
    }; // class PhaseEndTurn
} // namespace game

#endif /* PhaseEndTurn_hpp */
