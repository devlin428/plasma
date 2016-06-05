//
//  MatchConditionBuilder.hpp
//  Plazma Lights Off
//
//  Created by Derek Higgs on 6/5/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

#ifndef MatchConditionBuilder_hpp
#define MatchConditionBuilder_hpp

#include "RuleTypes.h"

namespace game {
    class IMatchCondition;
    
    /**
     * Class for building complex conditions.
     */
    class MatchConditionBuilder {
    public:
        /**
         * Creates a condition builder that starts with a condition.
         *
         * @param   condition   The condition to start this builder.
         */
        explicit MatchConditionBuilder(match_condition_t condition);
        
        /**
         * Deconstructor
         */
        ~MatchConditionBuilder();
        
        /**
         * Creates a new condition. The caller takes ownership of this
         * condition.
         *
         * @return  The new condition based on the builder.
         */
        const IMatchCondition * createCondition() const;
        
        /**
         * Ands this condition with the condition from another condition
         * builder.
         *
         * @param right_hand_side   The condition builder with the other
         *                          condition.
         * @return                  This builder after the operation.
         */
        MatchConditionBuilder & andCondition(const MatchConditionBuilder & right_hand_side);
        
        /**
         * Ors this condition with the condition from another condition builder.
         *
         * @param right_hand_side   The condition builder with the other
         *                          condition.
         * @return                  This builder after the operation.
         */
        MatchConditionBuilder & orCondition(const MatchConditionBuilder & right_hand_side);
        
        /**
         * Negates this condition.
         *
         * @return                  This builder after the operation.
         */
        MatchConditionBuilder & notCondition();
        
    private:
        /**
         * The private implementation.
         */
        struct PrivateImplementation;
        PrivateImplementation * m_private_implementation;
        
        // disable the empty constructor
        MatchConditionBuilder();
        
        // disable copy and assign
        MatchConditionBuilder(const MatchConditionBuilder &);
        void operator=(const MatchConditionBuilder &);
    }; // class MatchConditionBuilder
    
    /**
     * Ands the conditions from a condition builder and a simple condition.
     *
     * @param left_hand_side    The condition builder with the condition.
     * @param right_hand_side   The simple condition.
     * @return                  This builder after the operation.
     */
    MatchConditionBuilder & operator&&(MatchConditionBuilder & left_hand_side,
                                       match_condition_t right_hand_side);
    
    /**
     * Ands the conditions from a condition builder and a simple condition.
     *
     * @param left_hand_side    The simple condition.
     * @param right_hand_side   The condition builder with the condition.
     * @return                  This builder after the operation.
     */
    MatchConditionBuilder & operator&&(match_condition_t left_hand_side,
                                       MatchConditionBuilder & right_hand_side);
    
    /**
     * Ands the conditions from two condition builders.
     *
     * @param left_hand_side    The condition builder with the condition on the
     *                          left.
     * @param right_hand_side   The condition builder with the condition on the
     *                          right.
     * @return                  This builder on the left after the operation.
     */
    MatchConditionBuilder & operator&&(MatchConditionBuilder & left_hand_side,
                                       const MatchConditionBuilder & right_hand_side);
    
    /**
     * Ors the conditions from a condition builder and a simple condition.
     *
     * @param left_hand_side    The condition builder with the condition.
     * @param right_hand_side   The simple condition.
     * @return                  This builder after the operation.
     */
    MatchConditionBuilder & operator||(MatchConditionBuilder & left_hand_side,
                                       match_condition_t right_hand_side);
    
    /**
     * Ors the conditions from a condition builder and a simple condition.
     *
     * @param left_hand_side    The simple condition.
     * @param right_hand_side   The condition builder with the condition.
     * @return                  This builder after the operation.
     */
    MatchConditionBuilder & operator||(match_condition_t left_hand_side,
                                       MatchConditionBuilder & right_hand_side);
    
    /**
     * Ors the conditions from two condition builders.
     *
     * @param left_hand_side    The condition builder with the condition on the
     *                          left.
     * @param right_hand_side   The condition builder with the condition on the
     *                          right.
     * @return                  This builder on the left after the operation.
     */
    MatchConditionBuilder & operator||(MatchConditionBuilder & left_hand_side,
                                       const MatchConditionBuilder & right_hand_side);
    
    /**
     * Negates the condition of the buidler.
     *
     * @param condtion_builder  The buider.
     * @return                  The builder after the operation.
     */
    MatchConditionBuilder & operator!(MatchConditionBuilder & condtion_builder);
} // namespace game

#include "MatchConditionBuilder.inl"

#endif /* MatchConditionBuilder_hpp */
