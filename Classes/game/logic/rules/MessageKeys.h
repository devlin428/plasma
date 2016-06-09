//
//  MessageKeys.h
//  tests
//
//  Created by Derek Higgs on 6/8/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

#ifndef MessageKeys_h
#define MessageKeys_h

#include "StringHash.hpp"

namespace game {
    /**
     * Message user info key for the player index.
     */
    const kettle::utils::hash_t kMessageKeyPlayerIndex = kettle::utils::hashCString("Player index");
}

#endif /* MessageKeys_h */
