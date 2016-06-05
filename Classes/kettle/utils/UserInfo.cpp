//
//  UserInfo.cpp
//  Plazma Lights Off
//
//  Created by Derek Higgs on 6/2/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

#include "UserInfo.hpp"

#include <vector>
#include <map>
#include <cstdint>

#include "ReferenceCountedObject.hpp"

namespace kettle {
namespace utils {
    struct UserInfo::PrivateImplementation : public ReferenceCountedObject {
        std::map<StringHash, bool>      bool_table;
        std::map<StringHash, int>       int_table;
        std::map<StringHash, UserInfo>  userinfo_table;
    }; // struct UserInfo::PrivateImplementation
    
    UserInfo::~UserInfo() {
        if(m_private_implementation) {
            m_private_implementation->release();
            m_private_implementation = nullptr;
        }
    }
} // namespace utils
} // namespace kettle
