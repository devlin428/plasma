//
//  IPhaseRules.hpp
//  Plazma Lights Off
//
//  Created by Derek Higgs on 6/4/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

#ifndef IPhaseRules_hpp
#define IPhaseRules_hpp

#include "RuleTypes.h"

namespace game {
    // Special phase codes.
    
    /**
     * The first phase of the match. This should perform all of the setup steps.
     */
    const phase_t kPhaseInitial     = 0;
    
    /**
     * The last phase of the match signaling the match is over.
     */
    const phase_t kPhaseEnd         = -1;
    
    /**
     * The match has been destroyed.
     */
    const phase_t kPhaseDestroyed   = -2;
    
    /**
     * The rules for each phase of the match.
     */
    class IPhaseRules {
    public:
        /**
         * Deconstructor.
         */
        virtual ~IPhaseRules() {}
        
        /**
         * Initializes the phase. This is for setting up data such as limits to
         * player actions.
         *
         * @param current_phase     The current phase of the game.
         * @return                  This instance.
         */
        virtual IPhaseRules * initializePhase(phase_t current_phase) = 0;
        
        /**
         * Updates the phase.
         *
         * @param context           The match context.
         * @param current_phase     The current phase of the game.
         * @return                  The reason this function returned.
         */
        virtual PhaseUpdateBreakReason updatePhase(MatchContext * context,
                                                   phase_t current_phase) = 0;
        
        /**
         * Gets the next phase.
         *
         * @param current_phase     The current phase of the game.
         * @return                  The next phase.
         */
        virtual phase_t getNextPhase(phase_t current_phase) const = 0;
        
        /**
         * Checks to see if a player has won.
         *
         * @param context           The match context.
         * @param player_index      The index of the player being checked.
         * @return                  True if the player has won.
         */
        virtual bool didPlayerWin(const MatchContext * context,
                                  unsigned int player_index) const = 0;
        
        /**
         * Checks to see if the end condition has been met.
         *
         * @param context   The match context.
         * @return          True if the match has finished.
         */
        virtual bool isFinished(const MatchContext * context) const = 0;
        
    protected:
        /**
         * Constructor.
         */
        IPhaseRules() {}
        
    private:
        // disable copy and assign
        IPhaseRules(const IPhaseRules &);
        void operator=(const IPhaseRules &);
    }; // class IPhaseRules
} // namespace game

#endif /* IPhaseRules_hpp */
