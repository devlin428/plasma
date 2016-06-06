//
//  TestMatchCondition.cpp
//  tests
//
//  Created by Derek Higgs on 6/5/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

#include "TestMatchCondition.hpp"

#include <iostream>

#include "MatchContext.hpp"
#include "IMatchCondition.hpp"
#include "MatchConditionBuilder.hpp"

using namespace std;
using namespace game;

bool isCurrentPlayerOdd(const MatchContext * context) {
    return context->current_player_turn % 2 == 1;
}

bool isCurrentPlayerMultipleOfThree(const MatchContext * context) {
    return context->current_player_turn % 3 == 0;
}

bool isCurrentPlayerMultipleOfFive(const MatchContext * context) {
    return context->current_player_turn % 5 == 0;
}

void check(const MatchContext * context, const IMatchCondition * condition) {
    cout << "Turn belongs to player " << context->current_player_turn;
    cout << ". Is condition met? ";
    cout << (condition->isMet(context) ? "Yes" : "No") << endl;
}

const IMatchCondition * createTestCondition() {
    const IMatchCondition * condition;
    
    condition = (MatchConditionBuilder(isCurrentPlayerMultipleOfThree) &&
                 isCurrentPlayerMultipleOfFive ||
                 !MatchConditionBuilder(isCurrentPlayerOdd)).createCondition();
    
    return condition;
}

int testMatchCondition() {
    MatchContext context = { nullptr, nullptr, nullptr, nullptr, nullptr, 0, 0 };
    
    cout << "Will check if the player index is a multiple of 15 or even..." << endl;
    
    const IMatchCondition * condition = createTestCondition();
    
    check(&context, condition);
    
    context.current_player_turn = 1;
    check(&context, condition);
    
    context.current_player_turn = 2;
    check(&context, condition);
    
    context.current_player_turn = 3;
    check(&context, condition);
    
    context.current_player_turn = 5;
    check(&context, condition);
    
    context.current_player_turn = 6;
    check(&context, condition);
    
    context.current_player_turn = 10;
    check(&context, condition);
    
    context.current_player_turn = 15;
    check(&context, condition);
    
    context.current_player_turn = 30;
    check(&context, condition);
    
    delete condition;
    
    return 0;
}
