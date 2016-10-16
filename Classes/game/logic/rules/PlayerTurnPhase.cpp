//
//  PlayerTurnPhase.cpp
//  tests
//
//  Created by Derek Higgs on 6/9/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

#include "PlayerTurnPhase.hpp"

#include "MatchContext.hpp"

namespace game {
    PlayerTurnPhase::PlayerTurnPhase() {}
    
    PlayerTurnPhase::~PlayerTurnPhase() {}
    
    void PlayerTurnPhase::initialize(const game::MatchContext *context) {
        m_did_piece_act_flags.clear();
        m_piece_moves_left = kMaxPiecesMoves;
    }
    
    PhaseUpdateBreakReason PlayerTurnPhase::update(MatchContext * context) {
        //IPlayer * player = context->getCurrentPlayer();
        
        
        
        // TODO
        return kPhaseUpdateBreakReasonWaitingOnPlayer;
    }
} // namespace game
