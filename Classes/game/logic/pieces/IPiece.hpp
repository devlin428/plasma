//
//  IPiece.hpp
//  Plazma Lights Off
//
//  Created by Derek Higgs on 5/28/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

#ifndef IPiece_hpp
#define IPiece_hpp

#include "CollisionLayer.hpp"
#include "BoardTypes.h"
#include "PlayerActions.h"

namespace kettle {
namespace utils {
    class UserInfo;
} // namespace util
} // namespace kettle

namespace game {
    struct MatchContext;
    
    class IPiece {
    public:
        virtual ~IPiece() {}
        
        virtual positionid_t getPositionId() const = 0;
        virtual void setPositionId(positionid_t position_id) = 0;
        
        virtual flags32_t getBlockFlags() const = 0;
        virtual flags32_t getPassFlags() const = 0;
        
        virtual spaces_t getMaxMovementDistance() const = 0;
        
        virtual action::action_t act(const MatchContext * context,
                                     action::phase_t phase,
                                     const kettle::utils::UserInfo * phase_info,
                                     kettle::utils::UserInfo * o_action_info) = 0;
        
    protected:
        IPiece() {}
        
    private:
        // disable copy and assign
        IPiece(const IPiece &);
        void operator=(const IPiece &);
    }; // IPiece
} // namespace plazma

#endif /* IPiece_hpp */
