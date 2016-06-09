//
//  TestPhase.hpp
//  tests
//
//  Created by Derek Higgs on 6/9/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

#ifndef TestPhase_hpp
#define TestPhase_hpp

namespace game {
    struct MatchContext;
    class IPhaseRule;
} // namespace game

/**
 * Runs a phase until the phase has finished.
 *
 * @param context   The match context.
 * @param phase     The phase to test.
 */
void testPhase(game::MatchContext * context, game::IPhaseRule * phase);

#endif /* TestPhase_hpp */
