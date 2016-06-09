//
//  PhaseAllPlayerPiecesAct.cpp
//  tests
//
//  Created by Derek Higgs on 6/9/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

#include "PhaseAllPlayerPiecesAct.hpp"

#include <algorithm>

#include "MatchContext.hpp"
#include "IPiece.hpp"

namespace game {
    PhaseAllPlayerPiecesAct::PhaseAllPlayerPiecesAct(kettle::utils::hash_t piece_action,
                                                     bool quicksave) :
            m_piece_action(piece_action),
            m_quicksave(quicksave) {}
    
    PhaseAllPlayerPiecesAct::~PhaseAllPlayerPiecesAct() {}
    
    void PhaseAllPlayerPiecesAct::initialize(const MatchContext * context) {}
    
    PhaseUpdateBreakReason PhaseAllPlayerPiecesAct::update(MatchContext * context) {
        IPiece * const * pieces = context->getCurrentPlayerPieces();
        unsigned int piece_count = context->getMaxPiecesForCurrentPlayer();
        
        for(IPiece * const * piece_iter = pieces,
            * const * piece_end = pieces + piece_count;
            piece_iter != piece_end;
            ++piece_iter) {
            
            if(*piece_iter) {
                (**piece_iter).act(context, m_piece_action, nullptr, nullptr);
            }
        }
        
        return m_quicksave ? kPhaseUpdateBreakReasonPhaseEndQuicksavePoint :
                             kPhaseUpdateBreakReasonPhaseEnd;
    }
}
