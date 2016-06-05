//
//  Vector3dTemplate.hpp
//  Plazma Lights Off
//
//  Created by Derek Higgs on 5/30/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

#ifndef Vector3dTemplate_hpp
#define Vector3dTemplate_hpp

namespace kettle {
namespace math {
namespace vector3d_template {
    
    template <typename NUMBER>
    class Vector3dTemplate {
    public:
        static const Vector3dTemplate ZERO;
        static const Vector3dTemplate ONE;
        static const Vector3dTemplate UNIT_X;
        static const Vector3dTemplate UNIT_Y;
        static const Vector3dTemplate UNIT_Z;
        
        /**
         * The coordinate values.
         */
        NUMBER x, y, z;
        
        /**
         * Constructs a vector with undefined data.
         */
        Vector3dTemplate();
        
        Vector3dTemplate(NUMBER x, NUMBER y, NUMBER z);
        Vector3dTemplate(const NUMBER * values);
        Vector3dTemplate(const Vector3dTemplate & from, const Vector3dTemplate & to);
        Vector3dTemplate(const Vector3dTemplate & right_hand_side);
        Vector3dTemplate(unsigned int color);
        
        /**
         * Destructor.
         */
        ~Vector3dTemplate();
        
        bool isZero() const;
        bool isOne() const;
        
        NUMBER getAngleTo(const Vector3dTemplate & vector_b) const;
        
        Vector3dTemplate & addi(const Vector3dTemplate & right_hand_side);
        Vector3dTemplate & operator +=(const Vector3dTemplate & right_hand_side);
        Vector3dTemplate add(const Vector3dTemplate & right_hand_side) const;
        Vector3dTemplate operator +(const Vector3dTemplate & right_hand_side) const;
        
        Vector3dTemplate & clampi(const Vector3dTemplate & min, const Vector3dTemplate & max);
        Vector3dTemplate clamp(const Vector3dTemplate & min, const Vector3dTemplate & max) const;
        
        Vector3dTemplate & crossi(const Vector3dTemplate & right_hand_side);
        Vector3dTemplate cross(const Vector3dTemplate & right_hand_side) const;
        
        float getDistance(const Vector3dTemplate & vector) const;
        NUMBER getDistanceSquared(const Vector3dTemplate & vector) const;
        
        NUMBER getDotProduct(const Vector3dTemplate & right_hand_side) const;
        
        float getMagnitude() const;
        NUMBER getMagnitudeSquared() const;
        
        Vector3dTemplate & negate();
        Vector3dTemplate getNegation() const;
        Vector3dTemplate operator -() const;
        
        Vector3dTemplate & scalei(NUMBER scalar);
        Vector3dTemplate & operator *=(NUMBER scalar);
        Vector3dTemplate scale(NUMBER scalar) const;
        Vector3dTemplate operator *(NUMBER scalar) const;
        
        Vector3dTemplate & scalei(const Vector3dTemplate & right_hand_side);
        Vector3dTemplate & operator *=(const Vector3dTemplate & right_hand_side);
        Vector3dTemplate scale(const Vector3dTemplate & right_hand_side) const;
        Vector3dTemplate operator *(const Vector3dTemplate & right_hand_side) const;
        
        Vector3dTemplate & set(NUMBER x, NUMBER y, NUMBER z);
        Vector3dTemplate & set(const NUMBER * values);
        Vector3dTemplate & operator =(const NUMBER * values);
        Vector3dTemplate & set(const Vector3dTemplate & right_hand_side);
        Vector3dTemplate & operator =(const Vector3dTemplate & right_hand_side);
        Vector3dTemplate & set(const Vector3dTemplate & from, const Vector3dTemplate & to);
        
        NUMBER operator [] (int index) const;
        NUMBER & operator [] (int index);
        
        Vector3dTemplate & setZero();
        
        Vector3dTemplate & subtracti(const Vector3dTemplate & right_hand_side);
        Vector3dTemplate & operator -=(const Vector3dTemplate & right_hand_side);
        Vector3dTemplate subtract(const Vector3dTemplate & right_hand_side) const;
        Vector3dTemplate operator -(const Vector3dTemplate & right_hand_side) const;
        
        Vector3dTemplate & smoothi(const Vector3dTemplate & target, float elapsed_time, float response_time);
        
        int compare(const Vector3dTemplate & right_hand_side) const;
        bool operator <(const Vector3dTemplate & right_hand_side) const;
        bool operator >(const Vector3dTemplate & right_hand_side) const;
        
        bool equals(const Vector3dTemplate & right_hand_side) const;
        bool operator ==(const Vector3dTemplate & right_hand_side) const;
        bool operator !=(const Vector3dTemplate & right_hand_side) const;
        
        float getAngle() const;
        
        NUMBER getCrossProduct(const Vector3dTemplate & right_hand_side) const;
        
        Vector3dTemplate getPerpendicular() const;
        Vector3dTemplate getClockwisePerpendicular() const;
        
        Vector3dTemplate getMidpoint(const Vector3dTemplate & right_hand_side) const;
        Vector3dTemplate getProjection(const Vector3dTemplate & projector);
    }; // class Vector3dTemplate
    
    template <typename NUMBER>
    Vector3dTemplate<NUMBER> & add(const Vector3dTemplate<NUMBER> & left_hand_side,
                                   const Vector3dTemplate<NUMBER> & right_hand_side,
                                   Vector3dTemplate<NUMBER> & o_result);
    
    template <typename NUMBER>
    Vector3dTemplate<NUMBER> & clamp(const Vector3dTemplate<NUMBER> & vector,
                                     const Vector3dTemplate<NUMBER> & min,
                                     const Vector3dTemplate<NUMBER> & max,
                                     Vector3dTemplate<NUMBER> & o_result);
    
    template <typename NUMBER>
    Vector3dTemplate<NUMBER> & cross(const Vector3dTemplate<NUMBER> & left_hand_side,
                                     const Vector3dTemplate<NUMBER> & right_hand_side,
                                     Vector3dTemplate<NUMBER> & o_result);
    
    template <typename NUMBER>
    Vector3dTemplate<NUMBER> & subtract(const Vector3dTemplate<NUMBER> & left_hand_side,
                                        const Vector3dTemplate<NUMBER> & right_hand_side,
                                        const Vector3dTemplate<NUMBER> & o_result);
    
    template <typename NUMBER>
    bool intersects(const Vector3dTemplate<NUMBER> & line1a,
                    const Vector3dTemplate<NUMBER> & line1b,
                    const Vector3dTemplate<NUMBER> & line2a,
                    const Vector3dTemplate<NUMBER> & line2b);
    
    template <typename NUMBER>
    bool isParallel(const Vector3dTemplate<NUMBER> & line1a,
                    const Vector3dTemplate<NUMBER> & line1b,
                    const Vector3dTemplate<NUMBER> & line2a,
                    const Vector3dTemplate<NUMBER> & line2b);
    
    template <typename NUMBER>
    bool segmentOverlaps(const Vector3dTemplate<NUMBER> & line1a,
                         const Vector3dTemplate<NUMBER> & line1b,
                         const Vector3dTemplate<NUMBER> & line2a,
                         const Vector3dTemplate<NUMBER> & line2b);
    
    template <typename NUMBER>
    Vector3dTemplate<NUMBER> getIntersection(const Vector3dTemplate<NUMBER> & line1a,
                                             const Vector3dTemplate<NUMBER> & line1b,
                                             const Vector3dTemplate<NUMBER> & line2a,
                                             const Vector3dTemplate<NUMBER> & line2b);
    
    template <typename NUMBER>
    Vector3dTemplate<NUMBER> operator * (NUMBER scalar,
                                         const Vector3dTemplate<NUMBER> & right_hand_side);
    
    template <typename NUMBER>
    Vector3dTemplate<NUMBER> & dividei(Vector3dTemplate<NUMBER> & vector, float denominator);
    template <typename NUMBER>
    Vector3dTemplate<NUMBER> & operator /=(Vector3dTemplate<NUMBER> & vector, float denominator);
    template <typename NUMBER>
    Vector3dTemplate<NUMBER> divide(const Vector3dTemplate<NUMBER> & vector, float denominator);
    template <typename NUMBER>
    Vector3dTemplate<NUMBER> operator /(const Vector3dTemplate<NUMBER> & vector, float denominator);
    
} // namespace vector3d_template
} // namespace math
} // namespace kettle

#include "Vector3dTemplate.inl"

#endif /* Vector3dTemplate_hpp */
