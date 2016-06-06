//
//  EndCondition.cpp
//  tests
//
//  Created by Derek Higgs on 6/5/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

#include "EndCondition.hpp"

#include <algorithm>

namespace game {
    EndCondition::EndCondition(const IMatchCondition * const * player_win_conditions,
                               unsigned int player_count) :
            m_player_win_conditions(player_win_conditions),
            m_player_count(player_count) {}
    
    EndCondition::~EndCondition() {
        if(m_player_win_conditions) {
            std::for_each(m_player_win_conditions,
                          m_player_win_conditions + m_player_count,
                          [](const IMatchCondition * condition){ delete condition; });
            delete [] m_player_win_conditions;
            m_player_win_conditions = nullptr;
        }
    }
    
    bool EndCondition::didPlayerWin(const game::MatchContext *context,
                                    unsigned int player_index) const {
        return m_player_win_conditions[ player_index ]->isMet(context);
    }
    
    bool EndCondition::isMet(const game::MatchContext *context) const {
        for(const IMatchCondition * const * condition_iter = m_player_win_conditions,
            * const * end_condition_iter = m_player_win_conditions + m_player_count;
            condition_iter != end_condition_iter;
            ++condition_iter) {
            
            if((**condition_iter).isMet(context)) {
                return true;
            }
        }
        return false;
    }
} // namespace game
