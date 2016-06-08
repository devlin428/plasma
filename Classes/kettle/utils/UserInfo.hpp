//
//  UserInfo.hpp
//  Plazma Lights Off
//
//  Created by Derek Higgs on 6/2/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

#ifndef UserInfo_hpp
#define UserInfo_hpp

#include "StringHash.hpp"

namespace kettle {
namespace utils {
    /**
     * The supported types for UserInfo.
     */
    enum UserInfoType {
        /**
         * The key is missing, so there is no value.
         */
        kUserInfoTypeVoid,
        
        /**
         * An int or unsigned int.
         */
        kUserInfoTypeInt,
        
        /**
         * An array of int or unsigned int.
         */
        kUserInfoTypeIntArray,
        
        // TODO: Add more types as needed.
    };
    
    /**
     * Stored data by keys.
     */
    class UserInfo {
    public:
        /**
         * Constructor.
         */
        UserInfo();
        
        /**
         * Deconstructor.
         */
        ~UserInfo();
        
        /**
         * Creates a deep copy of this instance.
         *
         * @param   The deep copy. The caller takes ownership.
         */
        UserInfo * copy() const;
        
        /**
         * Removes all of the data.
         */
        UserInfo & clear();
        
        /**
         * Checks if the key has the given value type.
         */
        bool isKeyOfType(StringHash key, UserInfoType type) const;
        
        /**
         * Sets an integer.
         *
         * @param key       The key to retrieve a value.
         * @param value     The value to store.
         * @return          This instance.
         */
        UserInfo & put(StringHash key, int value);
        
        /**
         * Gets an integer.
         *
         * @param key   The key to retrieve a value.
         * @return      The value or 0 if the value was absent.
         */
        int getInt(StringHash key) const;
        
        /**
         * Sets an array.
         *
         * @param key       The key to retrieve a value.
         * @param array     The array to store.
         * @param length    The length of the array.
         * @return          This instance.
         */
        UserInfo & put(StringHash key, const int * array, unsigned int length);
        
        /**
         * Gets an array.
         *
         * @param key           The key to retrieve a value.
         * @param o_array       (Optional) The value as an array. If the array
         *                      is already allocated, then it will be filled up
         *                      to the shorter of the value's length or
         *                      array_length. If this is pointing null, then a
         *                      new array is allocated and the caller takes
         *                      ownership.
         * @param array_length  (Optional) The length of the output array if it
         *                      was already allocated.
         * @return              The length of the array or 0 if the value was
         *                      absent.
         */
        unsigned int getArray(StringHash key,
                              int ** o_array = nullptr,
                              unsigned int array_length = 0) const;
        
        /**
         * Sets an array.
         *
         * @param key       The key to retrieve a value.
         * @param array     The array to store.
         * @param length    The length of the array.
         * @return          This instance.
         */
        UserInfo & put(StringHash key,
                       const unsigned int * array,
                       unsigned int length);
        
        /**
         * Gets an array.
         *
         * @param key           The key to retrieve a value.
         * @param o_array       (Optional) The value as an array. If the array
         *                      is already allocated, then it will be filled up
         *                      to the shorter of the value's length or
         *                      array_length. If this is pointing null, then a
         *                      new array is allocated and the caller takes
         *                      ownership.
         * @param array_length  (Optional) The length of the output array if it
         *                      was already allocated.
         * @return              The length of the array or 0 if the value was
         *                      absent.
         */
        unsigned int getArray(StringHash key,
                              unsigned int ** o_array = nullptr,
                              unsigned int array_length = 0) const;
        
        // TODO: Add more types as needed.
        
    private:
        /**
         * The private implementation.
         */
        struct PrivateImplementation;
        PrivateImplementation * m_private_implementation;
        
        // Dissable copy and assignment.
        UserInfo(const UserInfo &);
        void operator=(const UserInfo &);
    }; // class UserInfo
} // namespace utils
} // namespace kettle

#endif /* UserInfo_hpp */
