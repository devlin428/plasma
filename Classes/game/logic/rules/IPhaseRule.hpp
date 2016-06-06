//
//  IPhaseRule.hpp
//  tests
//
//  Created by Derek Higgs on 6/5/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

#ifndef IPhaseRule_hpp
#define IPhaseRule_hpp

#include "RuleTypes.h"

namespace game {
    class IPhaseRule {
    public:
        virtual ~IPhaseRule() {}
        
        virtual IPhaseRule * initialize() = 0;
        
        virtual PhaseUpdateBreakReason update(MatchContext * context) = 0;
        
    protected:
        IPhaseRule() {}
        
    private:
        // disable copy and assign
        IPhaseRule(const IPhaseRule &);
        void operator=(const IPhaseRule &);
    }; // class IPhaseRule
} // namespace game

#endif /* IPhaseRule_hpp */
