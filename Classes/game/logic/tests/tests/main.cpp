//
//  main.cpp
//  Plazma Lights Off
//
//  Created by Derek Higgs on 5/28/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

#include "TestMatch.hpp"
#include "TestMatchCondition.hpp"
#include "TestPhaseRulesByInterfaces.hpp"
#include "TestPhaseSetup.hpp"
#include "TestPhaseAllPiecesAct.hpp"
#include "TestPhaseEnd.hpp"

int main(int argc, const char * argv[]) {
    testMatch();
    testMatchCondition();
    testPhaseRulesByInterfaces();
    testSetupPhase();
    TestPhaseAllPiecesAct();
    testPhaseEnd();
    return 0;
}
