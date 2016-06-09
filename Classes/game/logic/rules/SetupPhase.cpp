//
//  SetupPhase.cpp
//  tests
//
//  Created by Derek Higgs on 6/6/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

#include "SetupPhase.hpp"

#include <algorithm>
#include <cstring>

#include "UserInfo.hpp"
#include "Messaging.hpp"

#include "IPlayer.hpp"
#include "PlayerActionsSetup.h"
#include "IBoard.hpp"
#include "MatchContext.hpp"
#include "OnPlayerSurrender.hpp"
#include "Spawn.hpp"
#include "MessageKeys.h"

namespace {
    /**
     * Sets up the parameters for the player to make a move for the setup phase.
     *
     * @param context                               The match context.
     * @param spawn_positions_by_player_index       The spawn positions for
     *                                              each player.
     * @param spawn_position_count_by_player_index  The spawn limit for each
     *                                              player.
     * @param player_parameters                     The player parameters to
     *                                              fill.
     */
    void setPlayerParameters(const game::MatchContext * context,
                             const game::positionid_t * const * spawn_positions_by_player_index,
                             const unsigned int * spawn_position_count_by_player_index,
                             kettle::utils::UserInfo & player_parameters) {
        const game::positionid_t * spawn_positions = spawn_positions_by_player_index[ context->current_player_turn ];
        unsigned int spawn_position_count = spawn_position_count_by_player_index[ context->current_player_turn ];
        player_parameters.put(game::player_action::kSpawnLocations, spawn_positions, spawn_position_count);
    }
    
    /**
     * Checks to see if the player can place more pieces.
     *
     * @param context   The match context.
     * @return          True if the player can place more.
     */
    bool canCurrentPlayerPlaceMore(const game::MatchContext * context) {
        return context->countPiecesForCurrentPlayer() < context->getMaxPiecesForCurrentPlayer();
    }
    
    /**
     * Calls the current player to act for the setup phase.
     *
     * @param context               The match context.
     * @param player_parameters     The parameters for a setup phase action.
     * @param o_action_parameters   The parameters for the player's action.
     * @return                      The player's action.
     */
    game::player_action::action_t act(game::MatchContext * context,
                                      const kettle::utils::UserInfo & player_parameters,
                                      kettle::utils::UserInfo * o_action_parameters) {
        o_action_parameters->clear();
        game::IPlayer * player = context->getCurrentPlayer();
        return player->act(context,
                           game::player_action::kSetupPhase,
                           &player_parameters,
                           o_action_parameters);
    }
    
    /**
     * Finishes a player's setup phase.
     *
     * @param context                               The match context.
     * @param player_count                          The number of players.
     * @param first_player_to_setup_index           The index of the first
     *                                              player to perform the setup.
     * @param first_turn_after_setup_player_index   The player's turn when setup
     *                                              has finished.
     * @param message_sender                        The sender of the message
     *                                              for the setup finished
     *                                              message.
     * @return                                      The break reason as a quick-
     *                                              save point. If all players
     *                                              have set up, then this
     *                                              returns that the phase has
     *                                              also ended.
     */
    game::PhaseUpdateBreakReason onPlayerSetupFinished(game::MatchContext * context,
                                                       unsigned int player_count,
                                                       unsigned int first_player_to_setup_index,
                                                       unsigned int first_turn_after_setup_player_index,
                                                       const kettle::utils::ISender * message_sender) {
        kettle::utils::UserInfo setup_finished_info;
        unsigned int current_player_turn = context->current_player_turn;
        setup_finished_info.put(game::kMessageKeyPlayerIndex, current_player_turn);
        context->messaging->post(game::kPlayerFinishedSetup,
                                 message_sender,
                                 &setup_finished_info);
        
        current_player_turn = context->current_player_turn = (current_player_turn + 1) % player_count;
        if(current_player_turn == first_player_to_setup_index) {
            context->current_player_turn = first_turn_after_setup_player_index;
            return game::kPhaseUpdateBreakReasonPhaseEndQuicksavePoint;
        }
        return game::kPhaseUpdateBreakReasonQuicksavePoint;
    }
} // namespace

namespace game {
    SetupPhase * createSetupPhase(SpawnPositionList * spawn_position_lists,
                                  unsigned int player_count,
                                  unsigned int first_turn_after_setup_player_index) {
        positionid_t ** spawn_positions_by_player_index = new positionid_t*[player_count];
        spaces_t * spawn_position_count_by_player_index = new spaces_t[player_count];
        
        {
            positionid_t ** spawn_positions_iter = spawn_positions_by_player_index;
            spaces_t * spawn_position_count_iter = spawn_position_count_by_player_index;
            for(SpawnPositionList * spawn_position_list_iter = spawn_position_lists,
                * spawn_position_list_end = spawn_position_lists + player_count;
                spawn_position_list_iter != spawn_position_list_end;
                ++spawn_position_list_iter,
                ++spawn_positions_iter,
                ++spawn_position_count_iter) {
                
                unsigned int count = spawn_position_list_iter->spawn_position_count;
                positionid_t * spawn_positions_copy = *spawn_positions_iter = new positionid_t[ count ];
                memcpy(spawn_positions_copy, spawn_position_list_iter->spawn_positions, sizeof(*spawn_positions_copy) * count);
                
                *spawn_position_count_iter = count;
            }
        }
        
        return new SetupPhase(spawn_positions_by_player_index,
                              spawn_position_count_by_player_index,
                              player_count,
                              first_turn_after_setup_player_index);
    }
    
    SetupPhase::SetupPhase(const positionid_t * const * spawn_positions_by_player_index,
                           const spaces_t * spawn_position_count_by_player_index,
                           unsigned int player_count,
                           unsigned int first_turn_after_setup_player_index) :
            m_spawn_positions_by_player_index(spawn_positions_by_player_index),
            m_spawn_position_count_by_player_index(spawn_position_count_by_player_index),
            m_player_count(player_count),
            m_first_turn_after_setup_player_index(first_turn_after_setup_player_index) {}
    
    SetupPhase::~SetupPhase() {
        if(m_spawn_positions_by_player_index) {
            std::for_each(m_spawn_positions_by_player_index,
                          m_spawn_positions_by_player_index + m_player_count,
                          [](const positionid_t * positions){ delete [] positions; });
            delete [] m_spawn_positions_by_player_index;
            m_spawn_positions_by_player_index = nullptr;
        }
        if(m_spawn_position_count_by_player_index) {
            delete [] m_spawn_position_count_by_player_index;
            m_spawn_position_count_by_player_index = nullptr;
        }
    }
    
    void SetupPhase::initialize(const MatchContext * context) {
        m_first_player_to_setup_index = context->current_player_turn;
    }
    
    PhaseUpdateBreakReason SetupPhase::update(MatchContext * context) {
        kettle::utils::UserInfo player_parameters, action_parameters;
        
        setPlayerParameters(context,
                            m_spawn_positions_by_player_index,
                            m_spawn_position_count_by_player_index,
                            player_parameters);
        
        while(canCurrentPlayerPlaceMore(context)) {
            player_action::action_t action = act(context,
                                                 player_parameters,
                                                 &action_parameters);
            
            if(action == player_action::kThinking) {
                return kPhaseUpdateBreakReasonWaitingOnPlayer;
            }
            else if(action == player_action::kSpawn) {
                spawnPiece(context,
                           m_spawn_positions_by_player_index,
                           m_spawn_position_count_by_player_index,
                           this,
                           &action_parameters);
            }
            else if(action == player_action::kFinishedSpawning) {
                break;
            }
            else if(action == player_action::kSurrender) {
                onPlayerSurrender(context);
            }
        }
        
        return onPlayerSetupFinished(context,
                                     m_player_count,
                                     m_first_player_to_setup_index,
                                     m_first_turn_after_setup_player_index,
                                     this);
    }
    
    kettle::utils::hash_t SetupPhase::getType() const {
        return SetupPhase::getType();
    }
    
    kettle::utils::hash_t SetupPhase::getClassType() {
        return kettle::utils::hashCString("SetupPhase");
    }
} // namespace game
