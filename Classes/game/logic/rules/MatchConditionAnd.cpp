//
//  MatchConditionAnd.cpp
//  Plazma Lights Off
//
//  Created by Derek Higgs on 6/5/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

#include "MatchConditionAnd.hpp"

namespace game {
    MatchConditionAnd::MatchConditionAnd(IMatchCondition * left_hand_side,
                                         IMatchCondition * right_hand_side) :
            m_left_hand_side(left_hand_side),
            m_right_hand_side(right_hand_side) {}
    
    MatchConditionAnd::~MatchConditionAnd() {
        if(m_left_hand_side) {
            delete m_left_hand_side;
            m_left_hand_side = nullptr;
        }
        if(m_right_hand_side) {
            delete m_right_hand_side;
            m_right_hand_side = nullptr;
        }
    }
    
    bool MatchConditionAnd::isMet(const game::MatchContext *context) const {
        return m_left_hand_side->isMet(context) &&
               m_right_hand_side->isMet(context);
    }
}
