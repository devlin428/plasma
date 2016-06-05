namespace game {
    inline IPlayer * MatchContext::getPlayer(unsigned int player_index) {
        return players[ player_index ];
    }
    
    inline const IPlayer * MatchContext::getPlayer(unsigned int player_index) const {
        return players[ player_index ];
    }
    
    inline IPiece ** MatchContext::getPieces(unsigned int player_index) {
        return pieces_by_player[ player_index ];
    }
    
    inline const IPiece * const * MatchContext::getPieces(unsigned int player_index) const {
        return pieces_by_player[ player_index ];
    }
    
    inline IPiece * MatchContext::getPiece(unsigned int player_index,
                                           unsigned int piece_index) {
        return getPieces( player_index )[ piece_index ];
    }
    
    inline const IPiece * MatchContext::getPiece(unsigned int player_index,
                                                 unsigned int piece_index) const {
        return getPieces( player_index )[ piece_index ];
    }
    
    inline unsigned int MatchContext::getMaxPieces(unsigned int player_index) const {
        return max_pieces_by_player[ player_index ];
    }
} // namespace game
