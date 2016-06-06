//
//  StringHash.cpp
//  Plazma Lights Off
//
//  Created by Derek Higgs on 5/31/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

#include "StringHash.hpp"

#include <cstring>

#ifdef DEBUG_RETAIN_STRING
namespace {
    const char * copy(const char * cstring) {
        size_t length = strlen(cstring);
        return strcpy(new char[ length + 1 ], cstring);
    }
} // namespace
#endif // DEBUG_RETAIN_STRING

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
        
        StringHash::StringHash(char const * cstring) : m_hash(hashCString(cstring))
#ifdef DEBUG_RETAIN_STRING
                , m_cstring(copy(cstring))
#endif // DEBUG_RETAIN_STRING
                {}
        
        StringHash::~StringHash() {
#ifdef DEBUG_RETAIN_STRING
            if(m_cstring) {
                delete [] m_cstring;
                m_cstring = nullptr;
            }
#endif // DEBUG_RETAIN_STRING
        }
} // namespace utils
} // namespace kettle
