//
//  IPlayer.hpp
//  Plazma Lights Off
//
//  Created by Derek Higgs on 5/31/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

#ifndef IPlayer_hpp
#define IPlayer_hpp

namespace game {
    class IPlayer {
    public:
        virtual ~IPlayer() {}
        
    protected:
        IPlayer() {}
        
    private:
        // dissable copy and assign
        IPlayer(const IPlayer &);
        void operator=(const IPlayer &);
    }; // class IPlayer
} // namespace game

#endif /* IPlayer_hpp */
