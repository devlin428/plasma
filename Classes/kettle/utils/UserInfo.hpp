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
    enum UserInfoType {
        kUserInfoTypeNull,
        kUserInfoTypeBoolean,
        kUserInfoTypeInt,
        kUserInfoTypeUserInfo
        
        // TODO: Add more types as needed.
    };
    
    class UserInfo {
    public:
        UserInfo();
        UserInfo(const UserInfo &);
        ~UserInfo();
        
        void operator=(const UserInfo &);
        
        UserInfo & put(StringHash key, bool value);
        bool get(StringHash key, bool * o_value) const;
        bool get(StringHash key, bool default_value) const;
        bool getBoolean(StringHash key) const;
        
        UserInfo & put(StringHash key, int value);
        bool get(StringHash key, int * o_value) const;
        int get(StringHash key, int default_value) const;
        int getInt(StringHash key) const;
        
        UserInfo & put(StringHash key, UserInfo & value);
        bool get(StringHash key, UserInfo * o_value) const;
        UserInfo * getUserInfo(StringHash key) const;
        
        // TODO: Add more types as needed.
        
        UserInfoType getType(StringHash key);
        bool contains(StringHash key, UserInfoType type);
        bool contains(StringHash key);
        
    private:
        struct PrivateImplementation;
        PrivateImplementation * m_private_implementation;
    }; // class UserInfo
} // namespace utils
} // namespace kettle

#endif /* UserInfo_hpp */
