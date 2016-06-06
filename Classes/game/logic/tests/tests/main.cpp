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

int main(int argc, const char * argv[]) {
    testMatch();
    testMatchCondition();
    testPhaseRulesByInterfaces();
    return 0;
}
