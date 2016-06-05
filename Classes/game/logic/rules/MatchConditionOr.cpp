//
//  MatchConditionOr.cpp
//  Plazma Lights Off
//
//  Created by Derek Higgs on 6/5/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

#include "MatchConditionOr.hpp"

namespace game {
    MatchConditionOr::MatchConditionOr(IMatchCondition * left_hand_side,
                                       IMatchCondition * right_hand_side) :
            m_left_hand_side(left_hand_side),
            m_right_hand_side(right_hand_side) {}
    
    MatchConditionOr::~MatchConditionOr() {
        if(m_left_hand_side) {
            delete m_left_hand_side;
            m_left_hand_side = nullptr;
        }
        if(m_right_hand_side) {
            delete m_right_hand_side;
            m_right_hand_side = nullptr;
        }
    }
    
    bool MatchConditionOr::isMet(const game::MatchContext *context) const {
        return m_left_hand_side->isMet(context) ||
               m_right_hand_side->isMet(context);
    }
} // namespace game