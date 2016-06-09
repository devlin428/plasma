//
//  IPlayer.hpp
//  Plazma Lights Off
//
//  Created by Derek Higgs on 5/31/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

#ifndef IPlayer_hpp
#define IPlayer_hpp

#include "PlayerActions.h"

namespace kettle {
namespace utils {
    class UserInfo;
} // namespace utils
} // namespace kettle

namespace game {
    struct MatchContext;
    
    class IPiece;
    
    class IPlayer {
    public:
        virtual ~IPlayer() {}
        
        virtual action::action_t act(const MatchContext * context,
                                     action::phase_t phase,
                                     const kettle::utils::UserInfo * phase_info,
                                     kettle::utils::UserInfo * o_action_info) = 0;
        
        virtual IPiece * spawn(unsigned int type) = 0;
        
    protected:
        IPlayer() {}
        
    private:
        // dissable copy and assign
        IPlayer(const IPlayer &);
        void operator=(const IPlayer &);
    }; // class IPlayer
} // namespace game

#endif /* IPlayer_hpp */
