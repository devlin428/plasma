//
//  StringHash.cpp
//  Plazma Lights Off
//
//  Created by Derek Higgs on 5/31/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

#include "StringHash.hpp"

#include <cstring>
#include <map>

#include "ReferenceCountedObject.hpp"
#include "Log.hpp"

#ifdef DEBUG
//#define DEBUG_STRING_HASH
#endif // DEBUG

namespace {
    /**
     * Registers a hash and checks if unique.
     *
     * @param hash      The string hash.
     * @param cstring   (Optional) The cstring.
     */
    void registerStringHash(kettle::utils::StringHash & hash,
                            const char * cstring = nullptr);
    
    /**
     * Unregisters a hash.
     *
     * @param hash      The string hash.
     */
    void unregisterStringHash(kettle::utils::StringHash & hash);
    
    /**
     * Make sure each string has a separate hash.
     */
#ifdef DEBUG_STRING_HASH
    class UniqueCheck;
    
    /**
     * A singleton of the string hash unique checker. Automatically deleted on
     * all string hashes being destroyed.
     */
    UniqueCheck * unique_check;
    
    /**
     * Class for checking unique string hashes.
     */
    class UniqueCheck : public kettle::utils::ReferenceCountedObject {
    public:
        /**
         * Constructor.
         */
        UniqueCheck() {}
        
        /**
         * Deconstructor.
         */
        ~UniqueCheck() {}
        
        /**
         * Checks that a string hash is unique for a string.
         *
         * @param hash      The string hash.
         * @param cstring   The cstring.
         */
        void checkUnique(unsigned long hash, const char * cstring);
        
    protected:
        /**
         * The stored string hashes.
         */
        std::map<unsigned long, const char *> m_hash_to_string;
        
    private:
        // disable copy and assign
        UniqueCheck(const UniqueCheck &);
        void operator=(const UniqueCheck &);
    };
    
    void registerStringHash(kettle::utils::StringHash & hash,
                            const char * cstring) {
        if(unique_check) {
            unique_check->retain();
        }
        else {
            unique_check = new UniqueCheck();
        }
        
        if(cstring) {
            unique_check->checkUnique(hash.getHash(), cstring);
        }
    }
    
    void unregisterStringHash(kettle::utils::StringHash & hash) {
        if(unique_check) {
            if(unique_check->release()) {
                unique_check = nullptr;
            }
        }
    }
    
    const char * copy(const char * cstring) {
        size_t length = strlen(cstring);
        return strcpy(new char[ length + 1 ], cstring);
    }
    
    void UniqueCheck::checkUnique(unsigned long hash, const char * cstring) {
        if(m_hash_to_string.count(hash) == 0) {
            m_hash_to_string[ hash ] = copy(cstring);
        }
        else {
            const char * stored_cstring = m_hash_to_string[ hash ];
            if(strcmp(cstring, stored_cstring) != 0) {
                kettle::utils::log("WARNING: Strings %s and %s have the same hash: %ld",
                                   stored_cstring,
                                   cstring,
                                   hash);
            }
        }
    }
    
#else // DEBUG_STRING_HASH
    void registerStringHash(kettle::utils::StringHash & hash,
                            const char * cstring) {}
    void unregisterStringHash(kettle::utils::StringHash & hash) {}
#endif // DEBUG_STRING_HASH
}

namespace kettle {
    namespace utils {
        unsigned long hashCString(const char * cstring) {
            return hashCString(cstring, strlen(cstring));
        }
        
        unsigned long hashCString(const char * cstring, string_size_t length) {
            return hashBytes(cstring, length * sizeof(char));
        }
        
        unsigned long hashBytes(const void * data, byte_size_t length_bytes) {
            // Using sdbm to hash.
            // http://www.cse.yorku.ca/~oz/hash.html
            unsigned long hash = 0;
            
            const char * byte_end = (const char *)(data) + length_bytes;
            for(const char * byte_iterator = (const char *)data; byte_iterator != byte_end; ++byte_iterator) {
                hash = *byte_iterator + (hash << 6) + (hash << 16) - hash;
            }
            
            return hash;
        }
        
        StringHash::StringHash(char const * cstring) :
                m_hash(hashCString(cstring)) {
            registerStringHash(*this, cstring);
        }
        
        StringHash::StringHash(const char * cstring, unsigned int length) :
                m_hash(hashCString(cstring, length)) {
            registerStringHash(*this, cstring);
        }
        
        StringHash::StringHash(const StringHash & string_hash) :
                m_hash(string_hash.getHash()) {
            registerStringHash(*this);
        }
        
        StringHash::~StringHash() {
            unregisterStringHash(*this);
        }
        
        StringHash & StringHash::operator=(const StringHash & right_hand_side) {
            unregisterStringHash(*this);
            m_hash = right_hand_side.getHash();
            registerStringHash(*this);
            return *this;
        }
        
        StringHash & StringHash::operator=(const char * cstring) {
            unregisterStringHash(*this);
            m_hash = hashCString(cstring);
            registerStringHash(*this);
            return *this;
        }
        
        bool StringHash::operator==(const StringHash & right_hand_side) const {
            return *this == right_hand_side.getHash();
        }
        
        bool StringHash::operator==(unsigned long right_hand_side) const {
            return m_hash == right_hand_side;
        }
        
        bool operator==(unsigned long left_hand_side,
                        const StringHash & right_hand_side) {
            return right_hand_side == left_hand_side;
        }
} // namespace utils
} // namespace kettle
