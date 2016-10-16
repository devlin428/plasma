//
//  Flags32.cpp
//  tests
//
//  Created by Derek Higgs on 6/10/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

#include "Flags32.hpp"


namespace kettle {
namespace utils {
    Flags32 & Flags32::clear() {
        m_flags = 0;
        return *this;
    }
} // namespace utils
} // namespace kettle
