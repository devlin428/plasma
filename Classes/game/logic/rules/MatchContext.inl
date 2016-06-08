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
    
    inline IPlayer * MatchContext::getCurrentPlayer() {
        return getPlayer(current_player_turn);
    }
    
    inline const IPlayer * MatchContext::getCurrentPlayer() const {
        return getPlayer(current_player_turn);
    }
    
    inline IPiece ** MatchContext::getCurrentPlayerPieces() {
        return getPieces(current_player_turn);
    }
    
    inline const IPiece * const * MatchContext::getCurrentPlayerPieces() const {
        return getPieces(current_player_turn);
    }
    
    inline IPiece * MatchContext::getCurentPlayerPiece(unsigned int piece_index) {
        return getPiece(current_player_turn, piece_index);
    }
    
    inline const IPiece * MatchContext::getCurentPlayerPiece(unsigned int piece_index) const {
        return getPiece(current_player_turn, piece_index);
    }
    
    inline MatchContext & MatchContext::setCurrentPlayerPiece(IPiece * piece,
                                                              unsigned int piece_index) {
        return setPiece(piece, current_player_turn, piece_index);
    }
    
    inline bool MatchContext::addPieceToCurrentPlayer(IPiece * piece) {
        return addPiece(piece, current_player_turn);
    }
    
    inline unsigned int MatchContext::getMaxPiecesForCurrentPlayer() const {
        return getMaxPieces(current_player_turn);
    }
    
    inline unsigned int MatchContext::countPiecesForCurrentPlayer() const {
        return countPiecesForPlayer(current_player_turn);
    }
} // namespace game
