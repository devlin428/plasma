//
//  PhaseEndTurn.cpp
//  tests
//
//  Created by Derek Higgs on 6/9/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

#include "PhaseEndTurn.hpp"

#include "MatchContext.hpp"

namespace game {
    PhaseEndTurn::PhaseEndTurn(bool quicksave, unsigned int turn_increment) :
            m_turn_increment(turn_increment),
            m_quicksave(quicksave) {}
    
    PhaseEndTurn::~PhaseEndTurn() {}
    
    void PhaseEndTurn::initialize(const game::MatchContext *context) {}
    
    PhaseUpdateBreakReason PhaseEndTurn::update(game::MatchContext *context) {
        context->current_player_turn += m_turn_increment;
        context->current_player_turn %= context->number_of_players;
        return m_quicksave ? kPhaseUpdateBreakReasonPhaseEndQuicksavePoint :
                             kPhaseUpdateBreakReasonPhaseEnd;
    }
} // namespace game
