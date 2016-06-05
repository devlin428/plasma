//
//  MatchConditionNot.cpp
//  Plazma Lights Off
//
//  Created by Derek Higgs on 6/5/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

#include "MatchConditionNot.hpp"

namespace game {
    MatchConditionNot::MatchConditionNot(IMatchCondition * condition) :
            m_condition(condition) {}
    
    MatchConditionNot::~MatchConditionNot() {
        if(m_condition) {
            delete m_condition;
            m_condition = nullptr;
        }
    }
    
    bool MatchConditionNot::isMet(const game::MatchContext *context) const {
        return !m_condition->isMet(context);
    }
} // namespace game
