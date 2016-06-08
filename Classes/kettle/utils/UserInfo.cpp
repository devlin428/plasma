//
//  UserInfo.cpp
//  Plazma Lights Off
//
//  Created by Derek Higgs on 6/2/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

#include "UserInfo.hpp"

#include <cstring>

#include <algorithm>
#include <map>

namespace {
    /**
     * Creates a new copy of an array.
     *
     * @param array     The array to copy.
     * @param length    The length of the array.
     * @return          The copy.
     */
    const int * copyArray(const int * array, unsigned int length) {
        int * copy = new int[ length ];
        memcpy(copy, array, sizeof(*copy) * length);
        return copy;
    }
    
    /**
     * Pairs together an array with its length.
     */
    struct Array {
        const int * array;
        unsigned int length;
    }; // struct array
}

namespace kettle {
namespace utils {
    struct UserInfo::PrivateImplementation {
        std::map<StringHash, int> int_map;
        std::map<StringHash, Array> int_array_map;
    }; // struct UserInfo::PrivateImplementation
    
    UserInfo::UserInfo() : m_private_implementation(new PrivateImplementation()) {}
    
    UserInfo::~UserInfo() {
        if(m_private_implementation) {
            clear();
            delete m_private_implementation;
            m_private_implementation = nullptr;
        }
    }
    
    UserInfo * UserInfo::copy() const {
        UserInfo * copy = new UserInfo();
        
        copy->m_private_implementation->int_map = m_private_implementation->int_map;
        
        for(std::map<StringHash, Array>::iterator iter =
                    m_private_implementation->int_array_map.begin();
            iter != m_private_implementation->int_array_map.end();
            ++iter) {
            const int * array_copy = copyArray(iter->second.array, iter->second.length);
            copy->m_private_implementation->int_array_map[ iter-> first ] = {
                array_copy, iter->second.length
            };
        }
        
        return copy;
    }
    
    UserInfo & UserInfo::clear() {
        m_private_implementation->int_map.clear();
        
        std::for_each(m_private_implementation->int_array_map.begin(),
                      m_private_implementation->int_array_map.end(),
                      [](std::pair<StringHash, Array> pair){
                          delete [] pair.second.array;
                      });
        
        return *this;
    }
    
    bool UserInfo::isKeyOfType(StringHash key, UserInfoType type) const {
        switch (type) {
            case kUserInfoTypeVoid:
                return m_private_implementation->int_map.count(key) +
                       m_private_implementation->int_array_map.count(key) == 0;
                
            case kUserInfoTypeInt:
                return m_private_implementation->int_map.count(key) == 1;
                
            case kUserInfoTypeIntArray:
                return m_private_implementation->int_array_map.count(key) == 1;
        }
    }
    
    UserInfo & UserInfo::put(StringHash key, int value) {
        m_private_implementation->int_map[ key ] = value;
        return *this;
    }
    
    int UserInfo::getInt(StringHash key) const {
        return m_private_implementation->int_map[ key ];
    }
    
    UserInfo & UserInfo::put(StringHash key, const int * array, unsigned int length) {
        const int * copy = copyArray(array, length);
        m_private_implementation->int_array_map[ key ] = { copy, length };
        return *this;
    }
    
    unsigned int UserInfo::getArray(StringHash key,
                                    int ** o_array,
                                    unsigned int array_length) const {
        Array array = m_private_implementation->int_array_map[ key ];
        
        if(o_array) {
            if(!*o_array) {
                *o_array = new int[ array.length ];
            }
            memcpy(*o_array,
                   array.array,
                   sizeof(**o_array) * array.length);
        }
        
        return array.length;
    }
    
    UserInfo & UserInfo::put(StringHash key,
                             const unsigned int * array,
                             unsigned int length) {
        int * copy = new int[ length ];
        memcpy(copy, array, sizeof(*copy) * length);
        m_private_implementation->int_array_map[ key ] = { copy, length };
        return *this;
    }
    
    unsigned int UserInfo::getArray(StringHash key,
                                    unsigned int ** o_array,
                                    unsigned int array_length) const {
        Array array = m_private_implementation->int_array_map[ key ];
        
        if(o_array) {
            if(!*o_array) {
                *o_array = new unsigned int[ array.length ];
            }
            memcpy(*o_array,
                   array.array,
                   sizeof(**o_array) * array.length);
        }
        
        return array.length;
    }
} // namespace utils
} // namespace kettle
