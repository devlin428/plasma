//
//  StringHash.hpp
//  Plazma Lights Off
//
//  Created by Derek Higgs on 5/31/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

#ifndef StringHash_hpp
#define StringHash_hpp

#ifdef DEBUG
#define DEBUG_RETAIN_STRING
#endif // DEBUG

namespace kettle {
namespace utils {
    /**
     * Type for string sizes. Should match string.h's size_t.
     */
    typedef unsigned long string_size_t;
    
    /**
     * Type for byte sizes. Should match string.h's size_t.
     */
    typedef unsigned long byte_size_t;
    
    unsigned long hashCString(const char * cstring);
    unsigned long hashCString(const char * cstring, string_size_t length);
    unsigned long hashBytes(const void * data, byte_size_t length_bytes);
    
    class StringHash {
    public:
        explicit StringHash(const char * cstring);
        StringHash(const char * cstring, int length);
        StringHash(const StringHash & string_hash);
        
        ~StringHash();
        
        StringHash & operator =(const StringHash right_hand_side);
        StringHash & operator =(const char * cstring);
        
        unsigned long getHash();
        
#ifdef DEBUG_RETAIN_STRING
        const char * getCstring() const;
#endif // DEBUG_RETAIN_STRING
        
    protected:
        unsigned long m_hash;
#ifdef DEBUG_RETAIN_STRING
        const char * m_cstring;
        
        void safeSetCstring(const char * cstring);
        void setCstring(const char * cstring);
        void releaseCstring();
#endif // DEBUG_RETAIN_STRING
        
    private:
        // disable empty constructor
        StringHash();
    }; // class StringHash
    
    bool operator ==(const StringHash & left_hand_side,
                     const StringHash & right_hand_side);
    
    bool operator<(const StringHash & left_hand_side,
                   const StringHash & right_hand_side);
    bool operator>(const StringHash & left_hand_side,
                   const StringHash & right_hand_side);
    bool operator<=(const StringHash & left_hand_side,
                    const StringHash & right_hand_side);
    bool operator>=(const StringHash & left_hand_side,
                    const StringHash & right_hand_side);
    
} // namespace utils
} // namespace kettle

#endif /* StringHash_hpp */
