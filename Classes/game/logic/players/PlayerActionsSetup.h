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
namespace player_action {
    const phase_t kSetupPhase = kettle::utils::hashCString("Setup");
    
    const player_parameter_key_t kSpawnLocations = kettle::utils::hashCString("Locations");
    
    const action_t kSpawn = kettle::utils::hashCString("Spawn");
    const action_parameter_key_t kPieceType = kettle::utils::hashCString("Type");
    const action_parameter_key_t kPositionIndex = kettle::utils::hashCString("Position Index");
    
    const action_t kFinishedSpawning = kettle::utils::hashCString("Finished spawning.");
} // namespace player_action
} // namespace game

#endif /* PlayerActionsSetup__h */
