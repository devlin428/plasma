//
//  BoardTypes.h
//  Plazma Lights Off
//
//  Created by Derek Higgs on 5/31/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

#ifndef BoardTypes_h
#define BoardTypes_h

#include <cstdint>

namespace game {
    typedef uint32_t positionid_t;
    typedef unsigned int spaces_t;
    
    typedef uint32_t flags32_t;
    
    typedef uint8_t collisionlayer_t;
} // namespace game

#endif /* BoardTypes_h */
