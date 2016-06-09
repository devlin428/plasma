//
//  TestPhase.cpp
//  tests
//
//  Created by Derek Higgs on 6/9/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

#include "TestPhase.hpp"

#include <iostream>

#include "MatchContext.hpp"
#include "IPhaseRule.hpp"

using namespace std;
using namespace game;

void testPhase(MatchContext * context, IPhaseRule * phase) {
    phase->initialize(context);
    
    PhaseUpdateBreakReason reason;
    while(true) {
        reason = phase->update(context);
        switch (reason) {
            case game::kPhaseUpdateBreakReasonPhaseEndQuicksavePoint:
                cout << "Phase ended with a quicksave point." << endl;
                return;
                
            case game::kPhaseUpdateBreakReasonQuicksavePoint:
                cout << "Quicksave point" << endl;
                break;
                
            case game::kPhaseUpdateBreakReasonPhaseEnd:
                cout << "Phase ended." << endl;
                return;
                
            case game::kPhaseUpdateBreakReasonWaitingOnPlayer:
                cout << "Waiting on player " << context->current_player_turn << endl;
                break;
        }
    }
}
