//
//  PlayerActionsSetup..h
//  tests
//
//  Created by Derek Higgs on 6/6/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

#ifndef PlayerActionsSetup__h
#define PlayerActionsSetup__h

#include "PlayerActions.h"

namespace game {
namespace action {
    /**
     * The setup phase. The actions that can be performed are kSpawn and
     * kFinishedSpawning.
     *
     * parameter UserInfo:
     * @key kSpawnLocations     An array of position IDs of the valid spawn
     *                          locations.
     */
    const phase_t kSetupPhase = action::hash("Setup");
    
    /**
     * A UserInfo key to an array of position IDs of valid spawn positions.
     */
    const player_parameter_key_t kSpawnLocations = action::hash("Locations");
    
    /**
     * An action to spawn a piece.
     *
     * returned UserInfo:
     * @key kPieceType      The type of the piece to spawn.
     * @key kPositionIndex  The index of the spawn position in the array 
     *                      kSpawnLocations.
     */
    const action_t kSpawn = action::hash("Spawn");
    const action_parameter_key_t kPieceType = action::hash("Type");
    const action_parameter_key_t kPositionIndex = action::hash("Position Index");
    
    const action_t kFinishedSpawning = action::hash("Finished spawning.");
} // namespace action
} // namespace game

#endif /* PlayerActionsSetup__h */
