//
//  MatchConditionAnd.hpp
//  Plazma Lights Off
//
//  Created by Derek Higgs on 6/5/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

#ifndef MatchConditionAnd_hpp
#define MatchConditionAnd_hpp

#include "IMatchCondition.hpp"

namespace game {
    /**
     * A condition made by combining two conditions with an and statement.
     */
    class MatchConditionAnd : public IMatchCondition {
    public:
        /**
         * Creates the and statement with the two conditions.
         *
         * @param left_hand_side    The left hand side of the statement. Takes
         *                          ownership.
         * @param right_hand_side   The right hand side of the statement. Takes
         *                          ownership.
         */
        MatchConditionAnd(IMatchCondition * left_hand_side,
                          IMatchCondition * right_hand_side);
        
        /**
         * Deconstructor.
         */
        ~MatchConditionAnd();
        
        /**
         * Checks to see if a condition is met.
         *
         * @param context   The match context to evaluate
         */
        bool isMet(const MatchContext * context) const;
        
    protected:
        /**
         * The two conditions of the and statment.
         */
        IMatchCondition * m_left_hand_side, * m_right_hand_side;
        
    private:
        // disable copy and assign
        MatchConditionAnd(const MatchConditionAnd &);
        void operator=(const MatchConditionAnd &);
    };
} // namespace game

#endif /* MatchConditionAnd_hpp */

