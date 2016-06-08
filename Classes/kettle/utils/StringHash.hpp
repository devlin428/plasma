//
//  StringHash.hpp
//  Plazma Lights Off
//
//  Created by Derek Higgs on 5/31/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

#ifndef StringHash_hpp
#define StringHash_hpp

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
    
    /**
     * Hashes a c-style string.
     *
     * @param cstring   The string.
     * @return          The hash.
     */
    unsigned long hashCString(const char * cstring);
    
    /**
     * Hashes a c-style string.
     *
     * @param cstring   The string.
     * @param length    The length of the string.
     * @return          The hash.
     */
    unsigned long hashCString(const char * cstring, string_size_t length);
    
    /**
     * Hashes arbitrary data.
     *
     * @param data          The data.
     * @param length_bytes  The size in bytes of the data.
     * @return              The hash.
     */
    unsigned long hashBytes(const void * data, byte_size_t length_bytes);
    
    /**
     * Turns strings into unique hashes. Define DEBUG_STRING_HASH to check that
     * the hashes are unique.
     */
    class StringHash {
    public:
        /**
         * Constructs the hash by hashing the c-style string.
         *
         * @param cstring   The c-style string.
         */
        explicit StringHash(const char * cstring);
        
        /**
         * Constructs the hash by hashing the c-style string.
         *
         * @param cstring   The c-style string.
         * @param length    The length of the string.
         */
        StringHash(const char * cstring, unsigned int length);
        
        /**
         * Copy constructor.
         */
        StringHash(const StringHash & string_hash);
        
        /**
         * Deconstructor.
         */
        ~StringHash();
        
        /**
         * Assignment.
         */
        StringHash & operator=(const StringHash & right_hand_side);
        
        /**
         * Changes the stored hash to the c-style string.
         */
        StringHash & operator=(const char * cstring);
        
        /**
         * Gets the hash value.
         */
        unsigned long getHash() const;
        
        /**
         * Checks that the hashes have the same value.
         *
         * @param right_hand_side   The right hand side of the operator.
         */
        bool operator==(const StringHash & right_hand_side) const;
        
        /**
         * Checks that the hashes have the same value.
         *
         * @param right_hand_side   The right hand side of the operator.
         */
        bool operator==(unsigned long right_hand_side) const;
        
    protected:
        /**
         * The hash.
         */
        unsigned long m_hash;
        
    private:
        // disable empty constructor
        StringHash();
    }; // class StringHash
    
    /**
     * Checks that the hashes have the same value.
     *
     * @param left_hand_side    The left hand side of the operator.
     * @param right_hand_side   The right hand side of the operator.
     */
    bool operator==(unsigned long left_hand_side,
                    const StringHash & right_hand_side);
    
    /**
     * Checks that the left hand side has a smaller hash value.
     *
     * @param left_hand_side    The left hand side of the operator.
     * @param right_hand_side   The right hand side of the operator.
     */
    bool operator<(const StringHash & left_hand_side,
                   const StringHash & right_hand_side);
    
    /**
     * Checks that the right hand side has a larger hash value.
     *
     * @param left_hand_side    The left hand side of the operator.
     * @param right_hand_side   The right hand side of the operator.
     */
    bool operator<=(const StringHash & left_hand_side,
                   const StringHash & right_hand_side);
    
    /**
     * Checks that the left hand side has a larger hash value.
     *
     * @param left_hand_side    The left hand side of the operator.
     * @param right_hand_side   The right hand side of the operator.
     */
    bool operator>(const StringHash & left_hand_side,
                   const StringHash & right_hand_side);
    
    /**
     * Checks that the right hand side has a smaller hash value.
     *
     * @param left_hand_side    The left hand side of the operator.
     * @param right_hand_side   The right hand side of the operator.
     */
    bool operator>(const StringHash & left_hand_side,
                   const StringHash & right_hand_side);
} // namespace utils
} // namespace kettle

#include "StringHash.inl"

#endif /* StringHash_hpp */
