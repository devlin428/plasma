//
//  Match.hpp
//  Plazma Lights Off
//
//  Created by Derek Higgs on 5/31/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//
//  High level game logic.

#ifndef Match_hpp
#define Match_hpp

#include "MatchContext.hpp"
#include "RuleTypes.h"

namespace game {
    
    class IPhaseRules;
    
    /**
     * Reasons for an update to end.
     */
    enum MatchUpdateBreakReason {
        /**
         * The game has just reached a point where a quicksave can be performed.
         */
        kMatchUpdateBreakReasonQuicksavePoint,
        
        /**
         * A player is deciding on a move.
         */
        kMatchUpdateBreakReasonWaitingOnPlayer,
        
        /**
         * The match has ended.
         */
        kMatchUpdateBreakReasonMatchEnd
    }; // enum MatchUpdateBreakReason
    
    /**
     * Handles the high level game logic.
     */
    class Match {
    public:
        /**
         * Creates a match.
         *
         * @param players               The players in the match. The first turn
         *                              goes to the player at index 0. The match
         *                              takes ownership of the players, but not
         *                              the array to allow a fixed sized array
         *                              as an input.
         * @param number_of_players     The number of players in the match.
         * @param max_pieces_by_player  An array of the maximum number of pieces
         *                              for a player. Index by the player index.
         * @param board                 The board for the match. Takes ownership
         *                              of the board.
         * @param phase_rules           The rules of the match. Takes ownership.
         * @return                      The newly created match or NULL if the
         *                              creation failed.
         */
        static Match * create(IPlayer * const * players,
                              unsigned int number_of_players,
                              const unsigned int * max_pieces_by_player,
                              IBoard * board,
                              IPhaseRules * phase_rules);
        
        /**
         * Destructor.
         */
        ~Match();
        
        // High level game functions.
        
        /**
         * Updates the game. Will stop at each state of the game a quicksave can
         * be performed or is waiting on a response from a player.
         *
         * @return  The reason the update function ended.
         */
        MatchUpdateBreakReason update();
        
        /**
         * Checks to see if the match has ended.
         */
        bool isFinished() const;
        
        /**
         * Checks to see if a player has won.
         *
         * @param player_index  The index of the player.
         * @return              True if the player has won.
         */
        bool didPlayerWin(unsigned int player_index) const;
        
        /**
         * Gets the current phase.
         */
        phase_t getPhase() const;
        
        /**
         * Gets the broadcast manager to send game events.
         */
        kettle::utils::Messaging * const getMessaging();
        
        // Game information.
        
        /**
         * Gets the player by the index.
         *
         * @param player_index  The index of the player.
         * @return              The player.
         */
        const IPlayer * getPlayer(unsigned int player_index) const;
        
        /**
         * Get the number of players.
         */
        unsigned int getNumberOfPlayers() const;
        
        /**
         * Gets the index of the player currently peforming a turn.
         */
        unsigned int getCurrentPlayerTurn() const;
        
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
         * @return              The piece pointers for the player and index.
         */
        const IPiece * getPiece(unsigned int player_index,
                                unsigned int piece_index) const;
        
        /**
         * Gets the maximum number of pieces for the player.
         *
         * @param player_index  The index of the player.
         * @return              The maximum number of pieces for the player.
         */
        unsigned int getMaxPieces(unsigned int player_index) const;
        
        /**
         * Get the maximum number of pieces at any one time durring the match.
         */
        unsigned int getMaxPieces() const;
        
        /**
         * Gets the game board.
         */
        const IBoard * getBoard() const;
        
    protected:
        /**
         * The game context.
         */
        MatchContext m_context;
        
        /**
         * An array of all of the piece pointers.
         */
        IPiece ** const m_all_pieces;
        
        /**
         * The rules for each of the phases.
         */
        IPhaseRules * const m_phase_rules;
        
        /**
         * The current state of the match.
         */
        phase_t m_phase;
        
        /**
         * Constructor
         *
         * @param players                   The players in the match. The match
         *                                  takes ownership of the array and
         *                                  players.
         * @param number_of_players         The number of players in the match.
         *
         * @param all_pieces                An array to store all of the piece
         *                                  pointers. Takes ownership.
         * @param pieces_by_player          An array of arrays of piece
         *                                  pointers. First index by the player
         *                                  index, then by the piece index.
         *                                  Takes ownership.
         * @param max_pieces_by_player      An array of the maximum number of
         *                                  pieces for a player. Index by the
         *                                  player index. Takes ownership.
         *
         * @param board                     The board to play the match. Takes
         *                                  ownership.
         * @param phase_rules               The rules for each phase. Takes
         *                                  ownership.
         * @param messaging                 The game's broadcast manager. Takes
         *                                  ownership.
         */
        Match(IPlayer * const * players,
              unsigned int number_of_players,
              
              IPiece ** all_pieces,
              IPiece ** const * pieces_by_player,
              const unsigned int * max_pieces_by_player,
              
              IBoard * const board,
              IPhaseRules * phase_rules,
              kettle::utils::Messaging * messaging);
        
    private:
        // disable copy and assign
        Match(const Match &);
        void operator=(const Match &);
    }; // class Match
} // namespace game

#endif /* Match_hpp */
