//
//  RuleTypes.h
//  Plazma Lights Off
//
//  Created by Derek Higgs on 6/3/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

#ifndef RuleTypes_h
#define RuleTypes_h

namespace game {
    struct MatchContext;
    
    /**
     * The type of a phase.
     */
    typedef int phase_t;
    
    /**
     * Reasons for an update function to break.
     */
    enum PhaseUpdateBreakReason {
        /**
         * The current phase ended and a quicksave can be performed.
         */
        kPhaseUpdateBreakReasonPhaseEndQuicksavePoint,
        
        /**
         * The match just reached a point where a quicksave can be performed.
         */
        kPhaseUpdateBreakReasonQuicksavePoint,
        
        /**
         * The current phase ended.
         */
        kPhaseUpdateBreakReasonPhaseEnd,
        
        /**
         * Waiting on player input.
         */
        kPhaseUpdateBreakReasonWaitingOnPlayer
    }; // enum PhaseUpdateBreakReason
    
    /**
     * Returns if a condition has been met in the match.
     */
    typedef bool (*match_condition_t)(const MatchContext * context);
} // namespace game

#endif /* RuleTypes_h */
