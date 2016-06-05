//
//  Vector2dTemplate.hpp
//  Plazma Lights Off
//
//  Created by Derek Higgs on 5/29/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

#ifndef Vector2dTemplate_hpp
#define Vector2dTemplate_hpp

namespace kettle {
namespace math {
namespace vector2d_template {
    
    template <typename NUMBER>
    class Vector2dTemplate {
    public:
        static const Vector2dTemplate ZERO;
        static const Vector2dTemplate ONE;
        static const Vector2dTemplate UNIT_X;
        static const Vector2dTemplate UNIT_Y;
        
        /**
         * The coordinate values.
         */
        NUMBER x, y;
        
        /**
         * Constructs a vector with undefined data.
         */
        Vector2dTemplate();
        
        Vector2dTemplate(NUMBER x, NUMBER y);
        Vector2dTemplate(const NUMBER * values);
        Vector2dTemplate(const Vector2dTemplate & from, const Vector2dTemplate & to);
        Vector2dTemplate(const Vector2dTemplate & right_hand_side);
        
        /**
         * Destructor.
         */
        ~Vector2dTemplate();
        
        bool isZero() const;
        bool isOne() const;
        
        NUMBER getAngleTo(const Vector2dTemplate & vector_b) const;
        
        Vector2dTemplate & addi(const Vector2dTemplate & right_hand_side);
        Vector2dTemplate & operator +=(const Vector2dTemplate & right_hand_side);
        Vector2dTemplate add(const Vector2dTemplate & right_hand_side) const;
        Vector2dTemplate operator +(const Vector2dTemplate & right_hand_side) const;
        
        Vector2dTemplate & clampi(const Vector2dTemplate & min, const Vector2dTemplate & max);
        Vector2dTemplate clamp(const Vector2dTemplate & min, const Vector2dTemplate & max) const;
        
        float getDistance(const Vector2dTemplate & vector) const;
        NUMBER getDistanceSquared(const Vector2dTemplate & vector) const;
        
        NUMBER getDotProduct(const Vector2dTemplate & right_hand_side) const;
        
        float getMagnitude() const;
        NUMBER getMagnitudeSquared() const;
        
        Vector2dTemplate & negate();
        Vector2dTemplate getNegation() const;
        Vector2dTemplate operator -() const;
        
        Vector2dTemplate & scalei(NUMBER scalar);
        Vector2dTemplate & operator *=(NUMBER scalar);
        Vector2dTemplate scale(NUMBER scalar) const;
        Vector2dTemplate operator *(NUMBER scalar) const;
        
        Vector2dTemplate & scalei(const Vector2dTemplate & right_hand_side);
        Vector2dTemplate & operator *=(const Vector2dTemplate & right_hand_side);
        Vector2dTemplate scale(const Vector2dTemplate & right_hand_side) const;
        Vector2dTemplate operator *(const Vector2dTemplate & right_hand_side) const;
        
        Vector2dTemplate & set(NUMBER x, NUMBER y);
        Vector2dTemplate & set(const NUMBER * values);
        Vector2dTemplate & operator =(const NUMBER * values);
        Vector2dTemplate & set(const Vector2dTemplate & right_hand_side);
        Vector2dTemplate & operator =(const Vector2dTemplate & right_hand_side);
        Vector2dTemplate & set(const Vector2dTemplate & from, const Vector2dTemplate & to);
        
        NUMBER operator [] (int index) const;
        NUMBER & operator [] (int index);
        
        Vector2dTemplate & setZero();
        
        Vector2dTemplate & subtracti(const Vector2dTemplate & right_hand_side);
        Vector2dTemplate & operator -=(const Vector2dTemplate & right_hand_side);
        Vector2dTemplate subtract(const Vector2dTemplate & right_hand_side) const;
        Vector2dTemplate operator -(const Vector2dTemplate & right_hand_side) const;
        
        Vector2dTemplate & smoothi(const Vector2dTemplate & target, float elapsed_time, float response_time);
        
        int compare(const Vector2dTemplate & right_hand_side) const;
        bool operator <(const Vector2dTemplate & right_hand_side) const;
        bool operator >(const Vector2dTemplate & right_hand_side) const;
        
        bool equals(const Vector2dTemplate & right_hand_side) const;
        bool operator ==(const Vector2dTemplate & right_hand_side) const;
        bool operator !=(const Vector2dTemplate & right_hand_side) const;
        
        float getAngle() const;
        
        NUMBER getCrossProduct(const Vector2dTemplate & right_hand_side) const;
        
        Vector2dTemplate getPerpendicular() const;
        Vector2dTemplate getClockwisePerpendicular() const;
        
        Vector2dTemplate getMidpoint(const Vector2dTemplate & right_hand_side) const;
        Vector2dTemplate getProjection(const Vector2dTemplate & projector);
    }; // class Vector2dTemplate

    template <typename NUMBER>
    Vector2dTemplate<NUMBER> & add(const Vector2dTemplate<NUMBER> & left_hand_side,
                                   const Vector2dTemplate<NUMBER> & right_hand_side,
                                   Vector2dTemplate<NUMBER> & o_result);

    template <typename NUMBER>
    Vector2dTemplate<NUMBER> & clamp(const Vector2dTemplate<NUMBER> & vector,
                                     const Vector2dTemplate<NUMBER> & min,
                                     const Vector2dTemplate<NUMBER> & max,
                                     Vector2dTemplate<NUMBER> & o_result);
    
    template <typename NUMBER>
    Vector2dTemplate<NUMBER> & subtract(const Vector2dTemplate<NUMBER> & left_hand_side,
                                        const Vector2dTemplate<NUMBER> & right_hand_side,
                                        const Vector2dTemplate<NUMBER> & o_result);
    
    template <typename NUMBER>
    bool intersects(const Vector2dTemplate<NUMBER> & line1a,
                    const Vector2dTemplate<NUMBER> & line1b,
                    const Vector2dTemplate<NUMBER> & line2a,
                    const Vector2dTemplate<NUMBER> & line2b);
    
    template <typename NUMBER>
    bool isParallel(const Vector2dTemplate<NUMBER> & line1a,
                    const Vector2dTemplate<NUMBER> & line1b,
                    const Vector2dTemplate<NUMBER> & line2a,
                    const Vector2dTemplate<NUMBER> & line2b);
    
    template <typename NUMBER>
    bool segmentOverlaps(const Vector2dTemplate<NUMBER> & line1a,
                         const Vector2dTemplate<NUMBER> & line1b,
                         const Vector2dTemplate<NUMBER> & line2a,
                         const Vector2dTemplate<NUMBER> & line2b);
    
    template <typename NUMBER>
    Vector2dTemplate<NUMBER> getIntersection(const Vector2dTemplate<NUMBER> & line1a,
                                             const Vector2dTemplate<NUMBER> & line1b,
                                             const Vector2dTemplate<NUMBER> & line2a,
                                             const Vector2dTemplate<NUMBER> & line2b);
    
    template <typename NUMBER>
    Vector2dTemplate<NUMBER> operator * (NUMBER scalar,
                                         const Vector2dTemplate<NUMBER> & right_hand_side);
    
    template <typename NUMBER>
    Vector2dTemplate<NUMBER> & dividei(Vector2dTemplate<NUMBER> & vector, float denominator);
    template <typename NUMBER>
    Vector2dTemplate<NUMBER> & operator /=(Vector2dTemplate<NUMBER> & vector, float denominator);
    template <typename NUMBER>
    Vector2dTemplate<NUMBER> divide(const Vector2dTemplate<NUMBER> & vector, float denominator);
    template <typename NUMBER>
    Vector2dTemplate<NUMBER> operator /(const Vector2dTemplate<NUMBER> & vector, float denominator);
    
} // namespace vector2d_template
} // namespace math
} // namespace kettle

#include "Vector2dTemplate.inl"

#endif /* Vector2dTemplate_hpp */
