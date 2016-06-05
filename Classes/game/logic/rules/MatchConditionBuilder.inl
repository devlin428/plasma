namespace game {
    inline MatchConditionBuilder & operator&&(MatchConditionBuilder & left_hand_side,
                                              match_condition_t right_hand_side) {
        return left_hand_side.andCondition(MatchConditionBuilder(right_hand_side));
    }
    
    inline MatchConditionBuilder & operator&&(match_condition_t left_hand_side,
                                              MatchConditionBuilder & right_hand_side) {
        return MatchConditionBuilder(left_hand_side).andCondition(right_hand_side);
    }
    
    inline MatchConditionBuilder & operator&&(MatchConditionBuilder & left_hand_side,
                                              const MatchConditionBuilder & right_hand_side) {
        return left_hand_side.andCondition(right_hand_side);
    }
    
    inline MatchConditionBuilder & operator||(MatchConditionBuilder & left_hand_side,
                                              match_condition_t right_hand_side) {
        return left_hand_side.orCondition(MatchConditionBuilder(right_hand_side));
    }
    
    inline MatchConditionBuilder & operator||(match_condition_t left_hand_side,
                                              MatchConditionBuilder & right_hand_side) {
        return MatchConditionBuilder(left_hand_side).orCondition(right_hand_side);
    }
    
    inline MatchConditionBuilder & operator||(MatchConditionBuilder & left_hand_side,
                                              const MatchConditionBuilder & right_hand_side) {
        return left_hand_side.orCondition(right_hand_side);
    }
    
    inline MatchConditionBuilder & operator!(MatchConditionBuilder & condtion_builder) {
        return condtion_builder.notCondition();
    }
}; // namespace game