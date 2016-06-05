//
//  Operations.hpp
//  Plazma Lights Off
//
//  Created by Derek Higgs on 6/3/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

#ifndef Operations_hpp
#define Operations_hpp

namespace kettle {
namespace math {
    /**
     * Gets the total of values from the array.
     *
     * @param array     The array of values.
     * @param length    The length of the array.
     * @return          The sumation of values in the array.
     */
    unsigned int sum(const unsigned int * array, unsigned int length);
} // namespace math
} // namespace kettle

#endif /* Operations_hpp */
