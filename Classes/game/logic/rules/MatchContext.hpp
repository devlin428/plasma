//
//  MatchContext.hpp
//  Plazma Lights Off
//
//  Created by Derek Higgs on 6/1/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//
//  Bundled game data for the current state of the game.

#ifndef MatchContext_hpp
#define MatchContext_hpp

namespace kettle {
namespace utils {
    class Messaging;
} // namespace utils
} // namespace kettle

namespace game {
    class IPlayer;
    class IBoard;
    class IPiece;
    
    /**
     * Bundled game data for the current state of the game.
     */
    struct MatchContext {
        /**
         * An array of player points.
         */
        IPlayer * const * const players;
        
        /**
         * An array of arrays of piece pointers. First index by the player
         * index, then by the piece index. This is referenced by
         * m_context.pieces_by_player.
         */
        IPiece * * const * const pieces_by_player;
        
        /**
         * An array of the maximum number of pieces for a player. Index by the
         * player index.
         */
        const unsigned int * const max_pieces_by_player;
        
        /**
         * The game board.
         */
        IBoard * const board;
        
        /**
         * The broadcast manager to send game events.
         */
        kettle::utils::Messaging * const messaging;
        
        /**
         * The total number of players.
         */
        const unsigned int number_of_players;
        
        /**
         * The index of the player currently peforming a turn.
         */
        unsigned int current_player_turn;
        
        // Functions for making array access easier.
        
        /**
         * Gets the player by the index.
         *
         * @param player_index  The index of the player.
         * @return              The player.
         */
        IPlayer * getPlayer(unsigned int player_index);
        
        /**
         * Gets the player by the index.
         *
         * @param player_index  The index of the player.
         * @return              The player.
         */
        const IPlayer * getPlayer(unsigned int player_index) const;
        
        /**
         * Gets the pieces for a player.
         *
         * @param player_index  The index of the player.
         * @return              The array of piece pointers for the player.
         */
        IPiece ** getPieces(unsigned int player_index);
        
        /**
         * Gets the pieces for a player.
         *
         * @param player_index  The index of the player.
         * @return              The array of piece pointers for the player.
         */
        const IPiece * const * getPieces(unsigned int player_index) const;
        
        /**
         * Gets a specific piece.
         *
         * @param player_index  The index of the player.
         * @param piece_index   The index of the piece.
         * @return              The piece pointer for the player and index.
         */
        IPiece * getPiece(unsigned int player_index,
                          unsigned int piece_index);
        
        /**
         * Gets a specific piece.
         *
         * @param player_index  The index of the player.
         * @param piece_index   The index of the piece.
         * @return              The piece pointer for the player and index.
         */
        const IPiece * getPiece(unsigned int player_index,
                                unsigned int piece_index) const;
        
        /**
         * Sets a piece.
         *
         * @param piece         The piece to set.
         * @param player_index  The index of the player.
         * @param piece_index   The index of the piece.
         * @return              This instance.
         */
        MatchContext & setPiece(IPiece * piece,
                                unsigned int player_index,
                                unsigned int piece_index);
        
        /**
         * Adds a piece to the player's list of pieces.
         *
         * @param piece         The piece to add.
         * @param player_index  The index of the player.
         * @return              True if the piece was added.
         */
        bool addPiece(IPiece * piece, unsigned int player_index);
        
        /**
         * Gets the maximum number of pieces for the player.
         *
         * @param player_index  The index of the player.
         * @return              The maximum number of pieces for the player.
         */
        unsigned int getMaxPieces(unsigned int player_index) const;
        
        // Functions for summarizing the context
        
        /**
         * Get the maximum number of pieces at any one time durring the match.
         */
        unsigned int getMaxPieces() const;
        
        /**
         * Counts how many pieces the player has in play.
         *
         * @param player_index  The index of the player.
         * @return              The number of pieces the player has in play.
         */
        unsigned int countPiecesForPlayer(unsigned int player_index) const;
        
        // Functions about the current player
        
        /**
         * Gets the player currently performing a turn.
         */
        IPlayer * getCurrentPlayer();
        
        /**
         * Gets the player currently performing a turn.
         */
        const IPlayer * getCurrentPlayer() const;
        
        /**
         * Gets the pieces for the current player.
         */
        IPiece ** getCurrentPlayerPieces();
        
        /**
         * Gets the pieces for the current player.
         */
        const IPiece * const * getCurrentPlayerPieces() const;
        
        /**
         * Gets the piece for the current player.
         *
         * @param piece_index   The index of the piece.
         * @return              The piece pointer at the index.
         */
        IPiece * getCurentPlayerPiece(unsigned int piece_index);
        
        /**
         * Gets the piece for the current player.
         *
         * @param piece_index   The index of the piece.
         * @return              The piece pointer at the index.
         */
        const IPiece * getCurentPlayerPiece(unsigned int piece_index) const;
        
        /**
         * Sets a piece for the current player.
         *
         * @param piece         The piece to set.
         * @param piece_index   The index of the piece.
         * @return              This instance.
         */
        MatchContext & setCurrentPlayerPiece(IPiece * piece,
                                             unsigned int piece_index);
        
        /**
         * Adds a piece to the current player's list of pieces.
         *
         * @param piece         The piece to add.
         * @return              True if the piece was added.
         */
        bool addPieceToCurrentPlayer(IPiece * piece);
        
        /**
         * Gets the maximum number of pieces for the current player.
         */
        unsigned int getMaxPiecesForCurrentPlayer() const;
        
        /**
         * Counts how many pieces the current player has in play.
         */
        unsigned int countPiecesForCurrentPlayer() const;
    }; // struct MatchContext
} // namespace game

#include "MatchContext.inl"

#endif /* MatchContext_hpp */
