//
//  Vector2d.hpp
//  Plazma Lights Off
//
//  Created by Derek Higgs on 5/29/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

#ifndef Vector2d_hpp
#define Vector2d_hpp

#include "Vector2dTemplate.hpp"

namespace kettle {
namespace math {
    
    typedef vector2d_template::Vector2dTemplate<float> Vector2d;
    
    Vector2d vector2dUnitWithAngle(float angle);
    
    Vector2d & normalize(Vector2d & vector);
    Vector2d getNormalized(const Vector2d & vector);
    
    Vector2d & rotatei(Vector2d & vector, float radians);
    Vector2d & rotatei(Vector2d & vector, const Vector2d & pivot, float radians);
    Vector2d rotate(const Vector2d & vector, float radians);
    Vector2d rotate(const Vector2d & vector, const Vector2d & pivot, float radians);
    
    Vector2d rotate(const Vector2d & other);
    Vector2d unrotate(const Vector2d & other);
    
    Vector2d & dividei(Vector2d & vector, float denominator);
    Vector2d & operator /=(Vector2d & vector, float denominator);
    Vector2d divide(const Vector2d & vector, float denominator);
    Vector2d operator /(const Vector2d & vector, float denominator);
    
    bool isCloseTo(const Vector2d & left_hand_side,
                   const Vector2d & right_hand_side,
                   float epsilon);
    
    Vector2d linearInterpolation(const Vector2d from,
                                 const Vector2d to,
                                 float alpha);
    
    bool intersects(const Vector2d & line1a,
                    const Vector2d & line1b,
                    const Vector2d & line2a,
                    const Vector2d & line2b,
                    float * hitpoint_range_line1,
                    float * hitpoint_range_line2 = nullptr);
    
    bool segmentOverlaps(const Vector2d & line1a,
                         const Vector2d & line1b,
                         const Vector2d & line2a,
                         const Vector2d & line2b,
                         float * hitpoint_range_line1,
                         float * hitpoint_range_line2 = nullptr);
} // namespace math
} // namespace kettle

#endif /* Vector2d_hpp */
