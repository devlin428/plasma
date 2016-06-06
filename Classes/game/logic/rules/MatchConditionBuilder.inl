namespace game {
    inline MatchConditionBuilder & MatchConditionBuilder::operator&&(const MatchConditionBuilder & right_hand_side) {
        return andCondition(right_hand_side);
    }
    
    inline MatchConditionBuilder & MatchConditionBuilder::andCondition(match_condition_t right_hand_side) {
        return andCondition(MatchConditionBuilder(right_hand_side));
    }
    
    inline MatchConditionBuilder & MatchConditionBuilder::operator&&(match_condition_t right_hand_side) {
        return andCondition(right_hand_side);
    }
    
    inline MatchConditionBuilder & operator&&(match_condition_t left_hand_side,
                                              MatchConditionBuilder & right_hand_side) {
        return MatchConditionBuilder(left_hand_side).andCondition(right_hand_side);
    }
    
    inline MatchConditionBuilder & MatchConditionBuilder::operator||(const MatchConditionBuilder & right_hand_side) {
        return orCondition(right_hand_side);
    }
    
    inline MatchConditionBuilder & MatchConditionBuilder::orCondition(match_condition_t right_hand_side) {
        return orCondition(MatchConditionBuilder(right_hand_side));
    }
    
    inline MatchConditionBuilder & MatchConditionBuilder::operator||(match_condition_t right_hand_side) {
        return orCondition(right_hand_side);
    }
    
    inline MatchConditionBuilder & operator||(match_condition_t left_hand_side,
                                              MatchConditionBuilder & right_hand_side) {
        return MatchConditionBuilder(left_hand_side).orCondition(right_hand_side);
    }
    
    inline MatchConditionBuilder & MatchConditionBuilder::operator!() {
        return notCondition();
    }
}; // namespace game