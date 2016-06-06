//
//  PhaseRulesByInterfaces.hpp
//  tests
//
//  Created by Derek Higgs on 6/5/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

#ifndef PhaseRulesByInterfaces_hpp
#define PhaseRulesByInterfaces_hpp

#include "IPhaseRules.hpp"

#include "EndCondition.hpp"

namespace game {
    class IMatchCondition;
    class IPhaseRule;
    
    /**
     * Pairs together a phase rule with the next phase to make creating a
     * PhaseRulesByInterfaces easier.
     */
    struct PhaseRuleWithNext {
        /**
         * The rule for this phase.
         */
        IPhaseRule * phase_rule;
        
        /**
         * The phase index that follows after this phase.
         */
        unsigned int next_phase;
    }; // struct PhaseRule
    
    /**
     * Creates a new IPhaseRules made of the phase rules and the player win
     * conditions.
     *
     * @param phase_rules_with_next     The phase rules with the next phase
     *                                  index. Takes ownership of each
     *                                  phase_rule.
     * @param phase_count               The number of phases.
     * @param player_win_conditions     An array of conditions indexed by
     *                                  the player. When a condition is
     *                                  true, then the associated player has
     *                                  won. Takes ownership of each
     *                                  condition, but not the array to allow
     *                                  fixed sized arrays as inputs.
     * @param number_of_players         The number of players.
     * @return
     */
    IPhaseRules * createPhaseRules(const PhaseRuleWithNext * phase_rules_with_next,
                                   unsigned int phase_count,
                                   const IMatchCondition * const * player_win_conditions,
                                   unsigned int number_of_players);
    
    /**
     * An implementation of IPhaseRules that uses a IPhaseRule to perform each
     * phase.
     */
    class PhaseRulesByInterfaces : public IPhaseRules {
    public:
        /**
         * Constructor.
         *
         * @param phase_rules               The phase rule for each phase. Takes
         *                                  ownership of each phase and the
         *                                  array.
         * @param next_phase                The next phase indexed by the
         *                                  previous phase. Takes ownership.
         * @param phase_count               The number of phases.
         * @param player_win_conditions     The win condition index by the
         *                                  player index. Takes ownership
         *                                  of each condition and the array.
         * @param number_of_players         The number of players.
         */
        PhaseRulesByInterfaces(IPhaseRule * const * phase_rules,
                               const phase_t * next_phase,
                               unsigned int phase_count,
                               const IMatchCondition * const * player_win_conditions,
                               unsigned int number_of_players);
        
        /**
         * Deconstructor.
         */
        ~PhaseRulesByInterfaces();
        
        /**
         * Initializes the phase. This is for setting up data such as limits to
         * player actions.
         *
         * @param current_phase     The current phase of the game.
         * @return                  This instance.
         */
        IPhaseRules * initializePhase(phase_t current_phase);
        
        /**
         * Updates the phase.
         *
         * @param context           The match context.
         * @param current_phase     The current phase of the game.
         * @return                  The reason this function returned.
         */
        PhaseUpdateBreakReason updatePhase(MatchContext * context,
                                           phase_t current_phase);
        
        /**
         * Gets the next phase.
         *
         * @param current_phase     The current phase of the game.
         * @return                  The next phase.
         */
        phase_t getNextPhase(phase_t current_phase) const;
        
        /**
         * Checks to see if a player has won.
         *
         * @param context           The match context.
         * @param player_index      The index of the player being checked.
         * @return                  True if the player has won.
         */
        bool didPlayerWin(const MatchContext * context,
                          unsigned int player_index) const;
        
        /**
         * Checks to see if the end condition has been met.
         *
         * @param context   The match context.
         * @return          True if the match has finished.
         */
        bool isFinished(const MatchContext * context) const;
        
    protected:
        /**
         * The rules for each phase index by phase_t.
         */
        IPhaseRule * const * m_phase_rules;
        
        /**
         * The next phase after each phase index by phase_t.
         */
        const phase_t * m_next_phase;
        
        /**
         * The end condition.
         */
        EndCondition m_end_condition;
        
        /**
         * The number of phases.
         */
        const unsigned int m_phase_count;
        
    private:
        // disable copy and assign
        PhaseRulesByInterfaces(const PhaseRulesByInterfaces &);
        void operator=(const PhaseRulesByInterfaces &);
    }; // class PhaseRulesByInterfaces
    
} // namespace game

#endif /* PhaseRulesByInterfaces_hpp */
