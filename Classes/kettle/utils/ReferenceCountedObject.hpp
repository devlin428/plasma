//
//  ReferenceCountedObject.hpp
//  Plazma Lights Off
//
//  Created by Derek Higgs on 6/5/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

#ifndef ReferenceCountedObject_hpp
#define ReferenceCountedObject_hpp

namespace kettle {
namespace utils {
    /**
     * Adds reference counting to an object.
     *
     * Call retain to keep this instance. Call release when finished with this
     * instance.
     *
     * An object implementing this should never be deleted explicitly, but
     * released instead.
     */
    class ReferenceCountedObject {
    public:
        /**
         * Constructor. Initializes the reference count to one.
         */
        ReferenceCountedObject();
        
        /**
         * Increments the reference count.
         */
        void retain();
        
        /**
         * Decreaments the reference count. This will be deleted when the
         * reference count hits zero.
         */
        void release();
        
    protected:
        unsigned int m_reference_count;
    };
} // namespace utils
} // namespace kettle

#endif /* ReferenceCountedObject_hpp */
