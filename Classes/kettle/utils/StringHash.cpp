//
//  StringHash.cpp
//  Plazma Lights Off
//
//  Created by Derek Higgs on 5/31/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

#include "StringHash.hpp"

#ifdef DEBUG
//#define DEBUG_STRING_HASH
#endif // DEBUG

#include <cstring>

#ifdef DEBUG_STRING_HASH

#include <map>

#include "Log.hpp"

#endif

namespace {
    /**
     * Checks if a string hash is unique.
     *
     * @param hash      The string hash.
     * @param cstring   (Optional) The cstring.
     */
    void registerStringHash(kettle::utils::hash_t hash,
                            const char * cstring = nullptr);
    
    /**
     * Make sure each string has a separate hash.
     */
#ifdef DEBUG_STRING_HASH
    
    std::map<kettle::utils::hash_t, const char *> all_hashed_strings;
    
    const char * copy(const char * cstring) {
        size_t length = strlen(cstring);
        return strcpy(new char[ length + 1 ], cstring);
    }
    
    void registerStringHash(kettle::utils::hash_t hash,
                            const char * cstring) {
        if(all_hashed_strings.count(hash) == 0) {
            all_hashed_strings[ hash ] = copy(cstring);
        }
        else {
            const char * stored_cstring = all_hashed_strings[ hash ];
            if(strcmp(cstring, stored_cstring) != 0) {
                kettle::utils::log("WARNING: Strings %s and %s have the same hash: %ld",
                                   stored_cstring,
                                   cstring,
                                   hash);
            }
        }
    }
    
#else // DEBUG_STRING_HASH
    
    void registerStringHash(kettle::utils::hash_t hash,
                            const char * cstring) {}
    
#endif // DEBUG_STRING_HASH
}

namespace kettle {
    namespace utils {
        hash_t hashCString(const char * cstring) {
            hash_t hash = hashCString(cstring, strlen(cstring));
            registerStringHash(hash, cstring);
            return hash;
        }
        
        hash_t hashCString(const char * cstring, string_size_t length) {
            return hashBytes(cstring, length * sizeof(char));
        }
        
        hash_t hashBytes(const void * data, byte_size_t length_bytes) {
            // Using sdbm to hash.
            // http://www.cse.yorku.ca/~oz/hash.html
            hash_t hash = 0;
            
            const char * byte_end = (const char *)(data) + length_bytes;
            for(const char * byte_iterator = (const char *)data; byte_iterator != byte_end; ++byte_iterator) {
                hash = *byte_iterator + (hash << 6) + (hash << 16) - hash;
            }
            
            return hash;
        }
} // namespace utils
} // namespace kettle
