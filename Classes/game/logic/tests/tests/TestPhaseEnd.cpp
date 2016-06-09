//
//  TestPhaseEnd.cpp
//  tests
//
//  Created by Derek Higgs on 6/9/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

#include "TestPhaseEnd.hpp"

#include <iostream>

#include "PhaseEndTurn.hpp"
#include "MatchContext.hpp"

#include "TestPhase.hpp"

using namespace std;
using namespace game;

namespace {
    void runPhase(MatchContext * context, IPhaseRule * phase) {
        testPhase(context, phase);
        cout << "Current player's turn " << context->current_player_turn << endl;
    }
}

int testPhaseEnd() {
    PhaseEndTurn phase;
    MatchContext context = {
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        4,
        2
    };
    
    for(int i = 0; i != 10; ++i) {
        runPhase(&context, &phase);
    }
    
    return 0;
}
