//
//  PhaseRulesByInterfaces.cpp
//  tests
//
//  Created by Derek Higgs on 6/5/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

#include "PhaseRulesByInterfaces.hpp"

#include <algorithm>
#include <cstring>

#include "IPhaseRule.hpp"

namespace game {
    IPhaseRules * createPhaseRules(const PhaseRuleWithNext * phase_rules_with_next,
                                   unsigned int phase_count,
                                   const IMatchCondition * const * player_win_conditions,
                                   unsigned int number_of_players) {
        IPhaseRule ** phase_rules = new IPhaseRule*[ phase_count ];
        phase_t * next_phase = new phase_t[ phase_count ];
        
        IPhaseRule ** phase_rules_iter = phase_rules;
        phase_t * next_phase_iter = next_phase;
        for(const PhaseRuleWithNext * phase_rule_with_next_iter = phase_rules_with_next,
            * phase_rule_with_next_end = phase_rules_with_next + phase_count;
            phase_rule_with_next_iter != phase_rule_with_next_end;
            ++phase_rule_with_next_iter,
            ++phase_rules_iter,
            ++next_phase_iter) {
            
            *phase_rules_iter = phase_rule_with_next_iter->phase_rule;
            *next_phase_iter = phase_rule_with_next_iter->next_phase;
        }
        
        IMatchCondition ** player_win_conditions_copy = new IMatchCondition*[ number_of_players ];
        std::memcpy(player_win_conditions_copy, player_win_conditions, sizeof(*player_win_conditions_copy) * number_of_players);
        
        return new PhaseRulesByInterfaces(phase_rules,
                                          next_phase,
                                          phase_count,
                                          player_win_conditions_copy,
                                          number_of_players);
    }
    
    PhaseRulesByInterfaces::PhaseRulesByInterfaces(IPhaseRule * const * phase_rules,
                                                   const phase_t * next_phase,
                                                   unsigned int phase_count,
                                                   const IMatchCondition * const * player_win_conditions,
                                                   unsigned int number_of_players) :
            m_phase_rules(phase_rules),
            m_next_phase(next_phase),
            m_end_condition(player_win_conditions, number_of_players),
            m_phase_count(phase_count) {}
    
    PhaseRulesByInterfaces::~PhaseRulesByInterfaces() {
        if(m_phase_rules) {
            std::for_each(m_phase_rules,
                          m_phase_rules+m_phase_count,
                          [](IPhaseRule * phase_rule) { delete phase_rule; });
            delete [] m_phase_rules;
            m_phase_rules = nullptr;
        }
        if(m_next_phase) {
            delete [] m_next_phase;
            m_next_phase = nullptr;
        }
    }
    
    IPhaseRules * PhaseRulesByInterfaces::initializePhase(phase_t current_phase) {
        if(current_phase >= 0) {
            m_phase_rules[ current_phase ]->initialize();
        }
        return this;
    }
    
    PhaseUpdateBreakReason PhaseRulesByInterfaces::updatePhase(MatchContext * context,
                                                               phase_t current_phase) {
        if(current_phase < 0) {
            return kPhaseUpdateBreakReasonPhaseEnd;
        }
        return m_phase_rules[current_phase]->update(context);
    }
    
    phase_t PhaseRulesByInterfaces::getNextPhase(phase_t current_phase) const {
        if(current_phase < 0) {
            return current_phase;
        }
        return m_next_phase[ current_phase ];
    }
    
    bool PhaseRulesByInterfaces::didPlayerWin(const MatchContext * context,
                                              unsigned int player_index) const {
        return m_end_condition.didPlayerWin(context, player_index);
    }
    
    bool PhaseRulesByInterfaces::isFinished(const MatchContext * context) const {
        return m_end_condition.isMet(context);
    }
} // namespace game