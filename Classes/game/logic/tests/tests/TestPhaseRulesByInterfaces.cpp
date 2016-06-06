//
//  TestPhaseRulesByInterfaces.cpp
//  tests
//
//  Created by Derek Higgs on 6/5/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

#include "TestPhaseRulesByInterfaces.hpp"

#include <iostream>

#include "PhaseRulesByInterfaces.hpp"
#include "IPhaseRule.hpp"
#include "MatchConditionFunctionPointer.hpp"

using namespace std;
using namespace game;

namespace {
    int phase_changes_remaining = 5;
    
    PhaseUpdateBreakReason getReason() {
        static int nextReason = 3;
        PhaseUpdateBreakReason reason = (PhaseUpdateBreakReason)nextReason;
        nextReason = (nextReason + 1) % 4;
        return reason;
    }
    
    class TestPhaseRule : public IPhaseRule {
    public:
        TestPhaseRule(const char * name) : m_name(name) {}
        ~TestPhaseRule() {}
        
        IPhaseRule * initialize() {
            cout << "Initialize phase " << m_name << endl;
            --phase_changes_remaining;
            return this;
        }
        
        PhaseUpdateBreakReason update(MatchContext * context) {
            cout << "Update phase " << m_name << endl;
            return getReason();
        }
        
    protected:
        const char * const m_name;
        
    private:
        // disable copy and assign
        TestPhaseRule(const TestPhaseRule &);
        void operator=(const TestPhaseRule &);
    }; // class TestPhaseRule
    
    bool testWinConditionNever(const MatchContext * context) {
        return false;
    }
    
    bool testWinCondition(const MatchContext * context) {
        return phase_changes_remaining <= 0;
    }
    
    const char * boolToYN(bool boolean) {
        return boolean ? "Yes" : "No";
    }
}

int testPhaseRulesByInterfaces() {
    PhaseRuleWithNext phase_rules_with_next[] = {
        // phase 0
        { new TestPhaseRule("Setup"), 1 },
        // phase 1
        { new TestPhaseRule("Upkeep"), 2 },
        // phase 2
        { new TestPhaseRule("Turn"), 1 }
    };
    
    IMatchCondition * conditions[] = {
        new MatchConditionFunctionPointer(testWinConditionNever),
        new MatchConditionFunctionPointer(testWinCondition),
    };
    
    IPhaseRules * phase_rules = createPhaseRules(phase_rules_with_next, 3, conditions, 2);
    
    MatchContext * context = nullptr;
    phase_t current_phase = kPhaseInitial;
    
    while(!phase_rules->isFinished(context)) {
        switch (phase_rules->updatePhase(context, current_phase)) {
            case game::kPhaseUpdateBreakReasonPhaseEndQuicksavePoint:
            case game::kPhaseUpdateBreakReasonPhaseEnd:
                current_phase = phase_rules->getNextPhase(current_phase);
                phase_rules->initializePhase(current_phase);
                
            case game::kPhaseUpdateBreakReasonQuicksavePoint:
            case game::kPhaseUpdateBreakReasonWaitingOnPlayer:
                break;
        }
    }
    
    cout << "Test Phase Rules by Interfaces finished. Did player 1 win? " << boolToYN(phase_rules->didPlayerWin(context, 0)) << endl;
    cout << "Did player 2 win? " << boolToYN(phase_rules->didPlayerWin(context, 1)) << endl;
    
    delete phase_rules;
    
    return 0;
}
