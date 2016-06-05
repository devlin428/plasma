//
//  MatchConditionNot.hpp
//  Plazma Lights Off
//
//  Created by Derek Higgs on 6/5/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

#ifndef MatchConditionNot_hpp
#define MatchConditionNot_hpp

#include "IMatchCondition.hpp"

namespace game {
    /**
     * A condition that negates another condition.
     */
    class MatchConditionNot : public IMatchCondition {
    public:
        /**
         * Constructs a condition that negates another condition.
         *
         * @param condition     The condition to negate. Takes ownership.
         */
        explicit MatchConditionNot(IMatchCondition * condition);
        
        /**
         * Deconstructor
         */
        ~MatchConditionNot();
        
        /**
         * Checks to see if a condition is met.
         *
         * @param context   The match context to evaluate
         */
        bool isMet(const MatchContext * context) const;
        
    protected:
        /**
         * The condition this negates.
         */
        IMatchCondition * m_condition;
        
    private:
        // disable copy and assign
        MatchConditionNot(const MatchConditionNot &);
        void operator=(const MatchConditionNot &);
    }; // class MatchConditionNot
} // namespace game

#endif /* MatchConditionNot_hpp */
