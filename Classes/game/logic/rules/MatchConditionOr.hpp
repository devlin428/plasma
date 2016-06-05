//
//  MatchConditionOr.hpp
//  Plazma Lights Off
//
//  Created by Derek Higgs on 6/5/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

#ifndef MatchConditionOr_hpp
#define MatchConditionOr_hpp

#include "IMatchCondition.hpp"

namespace game {
    /**
     * A condition made by combining two conditions with an or statement.
     */
    class MatchConditionOr : public IMatchCondition {
    public:
        /**
         * Creates the and statement with the two conditions.
         *
         * @param left_hand_side    The left hand side of the statement. Takes
         *                          ownership.
         * @param right_hand_side   The right hand side of the statement. Takes
         *                          ownership.
         */
        MatchConditionOr(IMatchCondition * left_hand_side,
                         IMatchCondition * right_hand_side);
        
        /**
         * Deconstructor.
         */
        ~MatchConditionOr();
        
        /**
         * Checks to see if a condition is met.
         *
         * @param context   The match context to evaluate
         */
        bool isMet(const MatchContext * context) const;
        
    protected:
        /**
         * The two conditions of the or statment.
         */
        IMatchCondition * m_left_hand_side, * m_right_hand_side;
        
    private:
        // disable copy and assign
        MatchConditionOr(const MatchConditionOr &);
        void operator=(const MatchConditionOr &);
    };
} // namespace game

#endif /* MatchConditionOr_hpp */
