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
    /**
     * Handles one phase of the match.
     */
    class IPhaseRule {
    public:
        /**
         * Deconstructor.
         */
        virtual ~IPhaseRule() {}
        
        /**
         * Initializes the phase data.
         *
         * @param context           The match context.
         */
        virtual void initialize(const MatchContext * context) = 0;
        
        /**
         * Updates the phase.
         *
         * @param context           The match context.
         * @return                  The reason this function returned.
         */
        virtual PhaseUpdateBreakReason update(MatchContext * context) = 0;
        
    protected:
        /**
         * Constructor.
         */
        IPhaseRule() {}
        
    private:
        // disable copy and assign
        IPhaseRule(const IPhaseRule &);
        void operator=(const IPhaseRule &);
    }; // class IPhaseRule
} // namespace game

#endif /* IPhaseRule_hpp */
