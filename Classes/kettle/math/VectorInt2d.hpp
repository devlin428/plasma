//
//  VectorInt2d.hpp
//  Plazma Lights Off
//
//  Created by Derek Higgs on 5/29/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

#ifndef VectorInt2d_hpp
#define VectorInt2d_hpp

#include "Vector2dTemplate.hpp"

namespace kettle {
namespace math {
    
    typedef vector2d_template::Vector2dTemplate<int> VectorInt2d;
    
    VectorInt2d & dividei(VectorInt2d & vector, int denominator);
    VectorInt2d & operator /=(VectorInt2d & vector, int denominator);
    VectorInt2d divide(const VectorInt2d & vector, int denominator);
    VectorInt2d operator /(const VectorInt2d & vector, int denominator);
    
} // namespace math
} // namespace kettle

#endif /* VectorInt2d_hpp */
