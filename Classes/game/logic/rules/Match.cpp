//
//  Match.cpp
//  Plazma Lights Off
//
//  Created by Derek Higgs on 5/31/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

#include "Match.hpp"

#include <algorithm>
#include <cstring>

#include "Messaging.hpp"
#include "Operations.hpp"

#include "IPhaseRules.hpp"
#include "IPlayer.hpp"
#include "IBoard.hpp"

namespace {
    void nextPhase(game::IPhaseRules * phase_rules, const game::MatchContext * context, game::phase_t & io_phase) {
        io_phase = phase_rules->getNextPhase(io_phase);
        phase_rules->initializePhase(context, io_phase);
    }
} // namespace

namespace game {
    Match * Match::create(IPlayer * const * const players,
                          unsigned int number_of_players,
                          const unsigned int * const max_pieces_by_player,
                          IBoard * const board,
                          IPhaseRules * const phase_rules) {
        IPlayer ** players_copy = new IPlayer*[ number_of_players ];
        std::memcpy(players_copy, players, sizeof(*players_copy) * number_of_players);
        
        unsigned int max_pieces = kettle::math::sum(max_pieces_by_player, number_of_players);
        IPiece ** all_pieces = new IPiece*[ max_pieces ];
        IPiece *** pieces_by_player = new IPiece**[ number_of_players ];
        
        // Initialize the piece pointers with null.
        for(IPiece ** piece_ptr = all_pieces,
            **end = all_pieces + max_pieces;
            piece_ptr != end;
            ++piece_ptr) {
            piece_ptr = nullptr;
        }
        
        // Set pieces_by_player to point into all pieces.
        const unsigned int * max_pieces_iter = max_pieces_by_player;
        for(IPiece *** piece_ptr_array_iter = pieces_by_player,
            ** all_pieces_ptr_iter = all_pieces,
            *** end = pieces_by_player + number_of_players;
            piece_ptr_array_iter != end;
            ++piece_ptr_array_iter,
            all_pieces_ptr_iter += *max_pieces_iter++) {
            *piece_ptr_array_iter = all_pieces_ptr_iter;
        }
        
        unsigned int * max_pieces_by_player_copy = new unsigned int[ number_of_players ];
        std::memcpy(max_pieces_by_player_copy, max_pieces_by_player, sizeof(*max_pieces_by_player_copy) * number_of_players);
        
        kettle::utils::Messaging * messaging = new kettle::utils::Messaging();
        
        Match * match = new Match(players_copy,
                                  number_of_players,
                                  
                                  all_pieces,
                                  pieces_by_player,
                                  max_pieces_by_player_copy,
                                  
                                  board,
                                  phase_rules,
                                  messaging);
        
        phase_rules->initializePhase(&match->m_context, match->m_phase);
        
        return match;
    }
    
    Match::~Match() {
        if(m_phase != kPhaseDestroyed) {
            m_phase = kPhaseDestroyed;
            
            std::for_each(m_context.players,
                          m_context.players+getNumberOfPlayers(),
                          [](IPlayer * player){ delete player; });
            delete [] m_context.players;
            
            std::for_each(m_all_pieces,
                          m_all_pieces+getMaxPieces(),
                          [](IPiece * piece){ delete piece; });
            delete [] m_all_pieces;
            
            delete [] m_context.pieces_by_player;
            
            delete [] m_context.max_pieces_by_player;
            
            delete m_context.board;
            
            delete m_context.messaging;
            
            delete m_phase_rules;
        }
    }
    
    // High level game functions.
    
    MatchUpdateBreakReason Match::update() {
        while ( !m_phase_rules->isFinished( &m_context ) ) {
            PhaseUpdateBreakReason phase_break_reason = m_phase_rules->updatePhase(&m_context, m_phase);
            
            switch (phase_break_reason) {
                case kPhaseUpdateBreakReasonPhaseEndQuicksavePoint:
                    // Update the phase and leave the quicksave point.
                    nextPhase(m_phase_rules, &m_context, m_phase);
                    
                case kPhaseUpdateBreakReasonQuicksavePoint:
                    return kMatchUpdateBreakReasonQuicksavePoint;
                    
                case kPhaseUpdateBreakReasonPhaseEnd:
                    nextPhase(m_phase_rules, &m_context, m_phase);
                    
                    // Check to see if the phase is the end of the game.
                    if( m_phase == kPhaseEnd ) {
                        return kMatchUpdateBreakReasonMatchEnd;
                    }
                    break;
                    
                case kPhaseUpdateBreakReasonWaitingOnPlayer:
                    return kMatchUpdateBreakReasonWaitingOnPlayer;
            }
        }
        
        if(m_phase != kPhaseDestroyed) {
            m_phase = kPhaseEnd;
        }
        
        return kMatchUpdateBreakReasonMatchEnd;
    }
    
    bool Match::isFinished() const {
        return m_phase < 0;
    }
    
    bool Match::didPlayerWin(unsigned int player_index) const {
        return m_phase_rules->didPlayerWin(&m_context, player_index);
    }
    
    phase_t Match::getPhase() const {
        return m_phase;
    }
    
    kettle::utils::Messaging * const Match::getMessaging() {
        return m_context.messaging;
    }
    
    // Game information.
    
    const IPlayer * Match::getPlayer(unsigned int player_index) const {
        return m_context.getPlayer(player_index);
    }
    
    unsigned int Match::getNumberOfPlayers() const {
        return m_context.number_of_players;
    }
    
    unsigned int Match::getCurrentPlayerTurn() const {
        return m_context.current_player_turn;
    }
    
    const IPiece * const * Match::getPieces(unsigned int player_index) const {
        return m_context.getPieces(player_index);
    }
    
    const IPiece * Match::getPiece(unsigned int player_index,
                                   unsigned int piece_index) const {
        return m_context.getPiece(player_index, piece_index);
    }
    
    unsigned int Match::getMaxPieces(unsigned int player_index) const {
        return m_context.getMaxPieces(player_index);
    }
    
    unsigned int Match::getMaxPieces() const {
        return m_context.getMaxPieces();
    }
    
    const IBoard * Match::getBoard() const {
        return m_context.board;
    }
    
    Match::Match(IPlayer * const * players,
                 unsigned int number_of_players,
                 
                 IPiece ** all_pieces,
                 IPiece ** const * pieces_by_player,
                 const unsigned int * max_pieces_by_player,
                 
                 IBoard * const board,
                 IPhaseRules * phase_rules,
                 kettle::utils::Messaging * messaging) :
            m_context({players,
                pieces_by_player,
                max_pieces_by_player,
                board,
                messaging,
                number_of_players,
                0
            }),
            m_all_pieces(all_pieces),
            m_phase_rules(phase_rules),
            m_phase(kPhaseInitial) {}
} // namespace game