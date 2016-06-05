//
//  RouteSet.hpp
//  Plazma Lights Off
//
//  Created by Derek Higgs on 5/31/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

#ifndef RouteSet_hpp
#define RouteSet_hpp

#include "BoardTypes.h"

namespace game {
    /**
     * Retains a set of routes to various positions. Only records one route per
     * destination.
     */
    class RouteSet {
    public:
        const unsigned int kNodeIndexFailure;
        
        RouteSet();
        ~RouteSet();
        
        void clear();
        
        /**
         * Adds a node to a route.
         *
         * @param position_id               The position ID of this step of the
         *                                  route.
         * @param previous_position_index   The index of the position that leads
         *                                  to the position.
         * @return                          The index of the newly added node or
         *                                  kNodeIndexFailure if adding the node
         *                                  failed.
         */
        unsigned int addRouteNode(positionid_t position_id,
                                  unsigned int previous_position_index);
        
        unsigned int getSize() const;
        
        positionid_t getPositionId(unsigned int position_index) const;
        
        unsigned int getPreviousPositionIndex(unsigned int position_index) const;
        
    protected:
        positionid_t * position_ids;
        unsigned int * previous_position_indexes;
        unsigned int size, capacity;
        
    private:
        // disable copy and assign
        RouteSet(const RouteSet &);
        void operator=(const RouteSet &);
    }; // class RouteSet
    
    /**
     * Gets a route.
     *
     * @param routes
     * @param destination_index     The index of the destination.
     * @param o_route               An array of position IDs to take to get to
     *                              the destination.
     * @param route_length          The size of the o_route array.
     * @return                      The size of the route.
     */
    unsigned int getRoute(const RouteSet * routes,
                          unsigned int destination_index,
                          positionid_t * o_route = nullptr,
                          unsigned int route_length = 0);
} // namespace game

#endif /* RouteSet_hpp */
