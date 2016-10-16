//
//  PlayerActionTurn.h
//  tests
//
//  Created by Derek Higgs on 6/13/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

#ifndef PlayerActionTurn_h
#define PlayerActionTurn_h

#include "PlayerActions.h"

namespace game {
namespace action {
    /**
     * The main phase. The actions that the player can performed are kMove and
     * kAct.
     */
    const phase_t kTurnPhase = hash("Turn");
    
    /**
     * An action to move a piece.
     *
     * returned UserInfo:
     * @key kPieceIndex     The index of the piece.
     * @key kRoute          The route to take as an array of position IDs.
     */
    const action_t kMove = hash("Move");
    
    /**
     * An action to make a piece perform an action.
     *
     * returned UserInfo:
     * @key kPieceIndex     The index of the piece.
     * @key kAction         The action to send to the piece.
     * @key kDirection      The compase direction for the action.
     */
    const action_t kAct = hash("Act");
    
    /**
     *
     */
} // namespace action
} // namespace game

#endif /* PlayerActionTurn_h */
