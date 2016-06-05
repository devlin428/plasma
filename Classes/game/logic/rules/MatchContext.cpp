//
//  MatchContext.cpp
//  Plazma Lights Off
//
//  Created by Derek Higgs on 6/1/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

#include "MatchContext.hpp"

#include "Operations.hpp"

#include "IPiece.hpp"

namespace game {
    
    MatchContext & MatchContext::setPiece(IPiece * piece,
                                          unsigned int player_index,
                                          unsigned int piece_index) {
        IPiece ** piece_ptr_ptr =  getPieces( player_index ) + piece_index;
        if(*piece_ptr_ptr != nullptr) {
            delete *piece_ptr_ptr;
        }
        *piece_ptr_ptr = piece;
        return *this;
    }
    
    MatchContext & MatchContext::removePiece(unsigned int player_index,
                                             unsigned int piece_index) {
        IPiece ** piece_ptr_ptr =  getPieces( player_index ) + piece_index;
        if(*piece_ptr_ptr != nullptr) {
            delete *piece_ptr_ptr;
            *piece_ptr_ptr = nullptr;
        }
        return *this;
    }
    
    unsigned int MatchContext::getMaxPieces() const {
        return kettle::math::sum(max_pieces_by_player, number_of_players);
    }
    
} // namespace game
