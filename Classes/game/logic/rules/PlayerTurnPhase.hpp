//
//  PlayerTurnPhase.hpp
//  tests
//
//  Created by Derek Higgs on 6/9/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

#ifndef PlayerTurnPhase_hpp
#define PlayerTurnPhase_hpp

#include "Flags32.hpp"

#include "IPhaseRule.hpp"

namespace game {
    const unsigned int kMaxPiecesMoves = 1;
    
    class PlayerTurnPhase : public IPhaseRule {
    public:
        /**
         * Constructor.
         */
        PlayerTurnPhase();
        
        /**
         * Deconstructor.
         */
        ~PlayerTurnPhase();
        
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
        kettle::utils::Flags32 m_did_piece_act_flags;
        unsigned int m_piece_moves_left;
        
    private:
        // disable copy and assign
        PlayerTurnPhase(const PlayerTurnPhase &);
        void operator=(const PlayerTurnPhase &);
    }; // class PlayerTurnPhase
} // namespace game

#endif /* PlayerTurnPhase_hpp */
