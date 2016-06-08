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
    
    bool MatchContext::addPiece(IPiece * piece, unsigned int player_index) {
        IPiece ** pieces = getPieces( player_index );
        unsigned int max_pieces = getMaxPieces( player_index );
        for(IPiece ** piece_iter = pieces,
            ** piece_end = pieces + max_pieces;
            piece_iter != piece_end;
            ++piece_iter) {
            if(*piece_iter == nullptr) {
                *piece_iter = piece;
                return true;
            }
        }
        return false;
    }
    
    unsigned int MatchContext::getMaxPieces() const {
        return kettle::math::sum(max_pieces_by_player, number_of_players);
    }
    
    unsigned int MatchContext::countPiecesForPlayer(unsigned int player_index) const {
        unsigned int count = 0;
        
        const IPiece * const * pieces = getPieces( player_index );
        unsigned int max_pieces = getMaxPieces( player_index );
        for(const IPiece * const * piece_iter = pieces,
            * const * piece_end = pieces + max_pieces;
            piece_iter != piece_end;
            ++piece_iter) {
            count += !!(*piece_iter);
        }
        
        return count;
    }
} // namespace game
