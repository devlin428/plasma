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
    const phase_t kSetupPhase("Setup");
    
    const player_parameter_key_t kSpawnLocations("Locations");
    
    const action_t kSpawn("Spawn");
    const action_parameter_key_t kPieceType("Type");
    const action_parameter_key_t kPositionIndex("Position Index");
    
    const action_t kFinishedSpawning("Finished spawning.");
} // namespace player_action
} // namespace game

#endif /* PlayerActionsSetup__h */
