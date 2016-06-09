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
     * Type for hash values.
     */
    typedef unsigned long hash_t;
    
    /**
     * Hashes a c-style string.
     *
     * @param cstring   The string.
     * @return          The hash.
     */
    hash_t hashCString(const char * cstring);
    
    /**
     * Hashes a c-style string.
     *
     * @param cstring   The string.
     * @param length    The length of the string.
     * @return          The hash.
     */
    hash_t hashCString(const char * cstring, string_size_t length);
    
    /**
     * Hashes arbitrary data.
     *
     * @param data          The data.
     * @param length_bytes  The size in bytes of the data.
     * @return              The hash.
     */
    hash_t hashBytes(const void * data, byte_size_t length_bytes);
} // namespace utils
} // namespace kettle

#endif /* StringHash_hpp */
