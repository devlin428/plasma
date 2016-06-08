//
//  Spawn.cpp
//  tests
//
//  Created by Derek Higgs on 6/8/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

#include "Spawn.hpp"

#include "UserInfo.hpp"
#include "Messaging.hpp"

#include "MatchContext.hpp"
#include "IPlayer.hpp"
#include "IBoard.hpp"
#include "IPiece.hpp"
#include "PlayerActionsSetup.h"

namespace {
    
    /**
     * Sends a message that the spawn failed.
     *
     * @param context               The match context.
     * @param message_sender        The sender of the message for the spawn
     *                              message.
     * @param action_parameters     The parameters to perform the spawn.
     */
    void onSpawnFailed(game::MatchContext * context,
                       const kettle::utils::ISender * message_sender,
                       const kettle::utils::UserInfo * action_parameters) {
        context->messaging->post(game::kSpawnFailed,
                                 message_sender,
                                 action_parameters);
    }
    
    /**
     * Spawns a piece.
     *
     * @param context               The match context.
     * @param piece                 The piece to spawn onto the board.
     * @param spawn_position_id     The ID of the position to spawn.
     * @param message_sender        The sender of the message for the spawn
     *                              message.
     * @param action_parameters     The parameters to perform the spawn.
     */
    void spawn(game::MatchContext * context,
               game::IPiece * piece,
               unsigned int spawn_position_id,
               const kettle::utils::ISender * message_sender,
               const kettle::utils::UserInfo * action_parameters) {
        if(context->board->setPieceAt(piece, spawn_position_id)) {
            if(context->addPieceToCurrentPlayer(piece)) {
                context->messaging->post(game::player_action::kSpawn,
                                         message_sender,
                                         action_parameters);
            }
            else {
                context->board->removePiece(piece);
                delete piece;
                onSpawnFailed(context, message_sender, action_parameters);
            }
        }
        else {
            delete piece;
            onSpawnFailed(context, message_sender, action_parameters);
        }
    }
    
    /**
     * Spawns a piece.
     *
     * @param context               The match context.
     * @param type                  The type of piece to spawn onto the board.
     * @param spawn_position_id     The ID of the position to spawn.
     * @param message_sender        The sender of the message for the spawn
     *                              message.
     * @param action_parameters     The parameters to perform the spawn.
     */
    void spawn(game::MatchContext * context,
               unsigned int type,
               unsigned int spawn_position_id,
               const kettle::utils::ISender * message_sender,
               const kettle::utils::UserInfo * action_parameters) {
        game::IPlayer * player = context->getCurrentPlayer();
        game::IPiece * piece = player->spawn(type);
        if(piece) {
            spawn(context,
                  piece,
                  spawn_position_id,
                  message_sender,
                  action_parameters);
        }
        else {
            onSpawnFailed(context, message_sender, action_parameters);
        }
    }
    
    /**
     * Spawns a piece.
     *
     * @param context                               The match context.
     * @param spawn_positions_by_player_index       The spawn positions for
     *                                              each player.
     * @param spawn_position_count_by_player_index  The spawn limit for each
     *                                              player.
     * @param type                                  The type of piece to spawn
     *                                              onto the board.
     * @param spawn_position_index                  The index of the spawn
     *                                              position in the player's
     *                                              spawn positions.
     * @param message_sender                        The sender of the message
     *                                              for the spawn message.
     * @param action_parameters                     The parameters to perform
     *                                              the spawn.
     */
    void spawn(game::MatchContext * context,
               const game::positionid_t * const * spawn_positions_by_player_index,
               const unsigned int * spawn_position_count_by_player_index,
               unsigned int type,
               unsigned int spawn_position_index,
               const kettle::utils::ISender * message_sender,
               const kettle::utils::UserInfo * action_parameters) {
        unsigned int spawn_position_count = spawn_position_count_by_player_index[ context->current_player_turn ];
        if(spawn_position_index < spawn_position_count) {
            const game::positionid_t * spawn_positions = spawn_positions_by_player_index[ context->current_player_turn ];
            game::positionid_t spawn_position_id = spawn_positions[ spawn_position_index ];
            spawn(context, type, spawn_position_id, message_sender, action_parameters);
        }
        else {
            onSpawnFailed(context, message_sender, action_parameters);
        }
    }
}

namespace game {
    /**
     * Spawns a piece.
     *
     * @param context                               The match context.
     * @param spawn_positions_by_player_index       The spawn positions for
     *                                              each player.
     * @param spawn_position_count_by_player_index  The spawn limit for each
     *                                              player.
     * @param message_sender                        The sender of the message
     *                                              for the spawn message.
     * @param action_parameters                     The parameters to perform
     *                                              the spawn.
     */
    void spawnPiece(MatchContext * context,
                    const positionid_t * const * spawn_positions_by_player_index,
                    const unsigned int * spawn_position_count_by_player_index,
                    const kettle::utils::ISender * message_sender,
                    const kettle::utils::UserInfo * action_parameters) {
        if(action_parameters->isKeyOfType(player_action::kPieceType, kettle::utils::kUserInfoTypeInt) &&
           action_parameters->isKeyOfType(player_action::kPositionIndex, kettle::utils::kUserInfoTypeInt))
        {
            unsigned int type = action_parameters->getInt(game::player_action::kPieceType);
            unsigned int spawn_position_index = action_parameters->getInt(game::player_action::kPositionIndex);
            spawn(context,
                  spawn_positions_by_player_index,
                  spawn_position_count_by_player_index,
                  type,
                  spawn_position_index,
                  message_sender,
                  action_parameters);
        }
        else {
            onSpawnFailed(context, message_sender, action_parameters);
        }
    }
}
