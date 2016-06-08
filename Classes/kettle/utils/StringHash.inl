namespace kettle {
namespace utils {
    inline unsigned long StringHash::getHash() const {
        return m_hash;
    }
    
    inline bool operator<(const StringHash & left_hand_side,
                          const StringHash & right_hand_side) {
        return left_hand_side.getHash() < right_hand_side.getHash();
    }
    
    inline bool operator<=(const StringHash & left_hand_side,
                          const StringHash & right_hand_side) {
        return left_hand_side.getHash() <= right_hand_side.getHash();
    }
    
    inline bool operator>(const StringHash & left_hand_side,
                          const StringHash & right_hand_side) {
        return left_hand_side.getHash() > right_hand_side.getHash();
    }
    
    inline bool operator>=(const StringHash & left_hand_side,
                          const StringHash & right_hand_side) {
        return left_hand_side.getHash() >= right_hand_side.getHash();
    }
} // namespace utils
} // namespace kettle
