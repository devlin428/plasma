//
//  Operations.cpp
//  Plazma Lights Off
//
//  Created by Derek Higgs on 6/3/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

#include "Operations.hpp"

#include <algorithm>

namespace kettle {
namespace math {
    class RunningTotal {
    public:
        unsigned int total;
        RunningTotal() : total(0) {}
        void operator() (unsigned int max_pieces_for_player) {
            total += max_pieces_for_player;
        }
    }; // class RunningTotal
    
    unsigned int sum(const unsigned int * array, unsigned int length) {
        RunningTotal running_total;
        std::for_each(array, array+length, running_total);
        return running_total.total;
    }
} // namespace math
} // namespace kettle