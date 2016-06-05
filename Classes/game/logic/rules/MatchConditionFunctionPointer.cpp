//
//  MatchConditionFunctionPointer.cpp
//  Plazma Lights Off
//
//  Created by Derek Higgs on 6/5/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

#include "MatchConditionFunctionPointer.hpp"

namespace game {
    MatchConditionFunctionPointer::MatchConditionFunctionPointer(match_condition_t condition) :
            m_condition(condition) {}
    
    MatchConditionFunctionPointer::~MatchConditionFunctionPointer() {}
    
    bool MatchConditionFunctionPointer::isMet(const game::MatchContext *context) const {
        return m_condition(context);
    }
} // game