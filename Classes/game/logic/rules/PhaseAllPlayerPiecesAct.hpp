//
//  PhaseAllPlayerPiecesAct.hpp
//  tests
//
//  Created by Derek Higgs on 6/9/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

#ifndef PhaseAllPlayerPiecesAct_hpp
#define PhaseAllPlayerPiecesAct_hpp

#include "StringHash.hpp"

#include "IPhaseRule.hpp"

namespace game {
    /**
     * A phase that tells all of the pieces for the current player to act.
     */
    class PhaseAllPlayerPiecesAct : public IPhaseRule {
    public:
        /**
         * Constructs a phase that sends a given code to all of the pieces for
         * the current player.
         *
         * @param piece_action  The action each piece will perform.
         * @param quicksave     Set to true to let a quicksave happen at the end
         *                      of the phase.
         */
        PhaseAllPlayerPiecesAct(kettle::utils::hash_t piece_action,
                                bool quicksave = true);
        
        /**
         * Deconstructor.
         */
        ~PhaseAllPlayerPiecesAct();
        
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
         * The action each piece will perform.
         */
        kettle::utils::hash_t m_piece_action;
        
        /**
         * Whether the phase should end with a quicksave point.
         */
        bool m_quicksave;
        
    private:
        // disable copy and assign
        PhaseAllPlayerPiecesAct(const PhaseAllPlayerPiecesAct &);
        void operator=(const PhaseAllPlayerPiecesAct &);
    }; // class PhaseAllPlayerPiecesAct
} // namespace game

#endif /* PhaseAllPlayerPiecesAct_hpp */
