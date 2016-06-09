//
//  OnPlayerSurrender.cpp
//  tests
//
//  Created by Derek Higgs on 6/6/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

#include "OnPlayerSurrender.hpp"

#include "Messaging.hpp"
#include "UserInfo.hpp"

#include "MatchContext.hpp"
#include "PlayerActions.h"
#include "MessageKeys.h"

namespace game {
    void onPlayerSurrender(MatchContext * context) {
        kettle::utils::UserInfo info;
        info.put(kMessageKeyPlayerIndex, context->current_player_turn);
        context->messaging->post(player_action::kSurrender, nullptr, &info);
    }
} // namespace game