//
//  MatchConditionFunctionPointer.hpp
//  Plazma Lights Off
//
//  Created by Derek Higgs on 6/5/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

#ifndef MatchConditionFunctionPointer_hpp
#define MatchConditionFunctionPointer_hpp

#include "IMatchCondition.hpp"
#include "RuleTypes.h"

namespace game {
    /**
     * Creates a match condition out of a function pointer.
     */
    class MatchConditionFunctionPointer : public IMatchCondition {
    public:
        /**
         * Default constructor. Initializes the function pointer with null.
         */
        MatchConditionFunctionPointer();
        
        /**
         * Creates the match condition with the function pointer as the
         * condition.
         *
         * @param condition     The condition.
         */
        explicit MatchConditionFunctionPointer(match_condition_t condition);
        
        /**
         * Copies the match condition.
         *
         * @param condition     The condition to copy.
         */
        MatchConditionFunctionPointer(const MatchConditionFunctionPointer & condition);
        
        /**
         * Deconstructor.
         */
        ~MatchConditionFunctionPointer();
        
        /**
         * Sets this condition to match another condition.
         *
         * @param condition     The condition to match.
         */
        MatchConditionFunctionPointer & operator=(const MatchConditionFunctionPointer & right_hand_side);
        
        /**
         * Sets the condition function pointer to a function.
         *
         * @param condition     The condition to match.
         */
        MatchConditionFunctionPointer & operator=(match_condition_t right_hand_side);
        
        /**
         * Checks to see if a condition is met.
         *
         * @param context   The match context to evaluate
         */
        bool isMet(const MatchContext * context) const;
        
    protected:
        /**
         * The function pointer to check the condition.
         */
        match_condition_t m_condition;
    }; // class MatchConditionFunctionPointer
} // namespace game

#endif /* MatchConditionFunctionPointer_hpp */
