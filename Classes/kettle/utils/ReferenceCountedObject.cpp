//
//  ReferenceCountedObject.cpp
//  Plazma Lights Off
//
//  Created by Derek Higgs on 6/5/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

#include "ReferenceCountedObject.hpp"

namespace kettle {
namespace utils {
    ReferenceCountedObject::ReferenceCountedObject() :
            m_reference_count(1) {}
    
    void ReferenceCountedObject::retain() {
        ++m_reference_count;
    }
    
    bool ReferenceCountedObject::release() {
        if(--m_reference_count == 0) {
            delete this;
            return true;
        }
        return false;
    }
} // namespace utils
} // namespace kettle
