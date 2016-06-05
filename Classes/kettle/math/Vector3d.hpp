//
//  Vector3d.hpp
//  Plazma Lights Off
//
//  Created by Derek Higgs on 5/30/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

#ifndef Vector3d_hpp
#define Vector3d_hpp

#include "Vector3dTemplate.hpp"

namespace kettle {
namespace math {
    
    typedef vector3d_template::Vector3dTemplate<float> Vector3d;
    
    Vector3d unitWithAngle(float angle);
    
    Vector3d & normalize(Vector3d & vector);
    Vector3d getNormalized(const Vector3d & vector);
    
    Vector3d linearInterpolation(const Vector3d from,
                                 const Vector3d to,
                                 float alpha);
    
    Vector3d & rotatei(Vector3d & vector, float radians);
    Vector3d & rotatei(Vector3d & vector, const Vector3d & pivot, float radians);
    Vector3d rotate(const Vector3d & vector, float radians);
    Vector3d rotate(const Vector3d & vector, const Vector3d & pivot, float radians);
    
    Vector3d rotate(const Vector3d & other);
    Vector3d unrotate(const Vector3d & other);
    
    Vector3d & dividei(Vector3d & vector, float denominator);
    Vector3d & operator /=(Vector3d & vector, float denominator);
    Vector3d divide(const Vector3d & vector, float denominator);
    Vector3d operator /(const Vector3d & vector, float denominator);
    
    bool isCloseTo(const Vector3d & left_hand_side,
                   const Vector3d & right_hand_side,
                   float epsilon);
    
    bool intersects(const Vector3d & line1a,
                    const Vector3d & line1b,
                    const Vector3d & line2a,
                    const Vector3d & line2b,
                    float * hitpoint_range_line1,
                    float * hitpoint_range_line2 = nullptr);
    
    bool segmentOverlaps(const Vector3d & line1a,
                         const Vector3d & line1b,
                         const Vector3d & line2a,
                         const Vector3d & line2b,
                         float * hitpoint_range_line1,
                         float * hitpoint_range_line2 = nullptr);
} // namespace math
} // namespace kettle

#endif /* Vector3d_hpp */
