//
//  SetupPhase.hpp
//  tests
//
//  Created by Derek Higgs on 6/6/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

#ifndef SetupPhase_hpp
#define SetupPhase_hpp

#include "IPhaseRule.hpp"

#include "Messaging.hpp"

#include "PlayerActions.h"
#include "BoardTypes.h"

namespace game {
    const kettle::utils::hash_t kPlayerFinishedSetup = kettle::utils::hashCString("Player finished setup");
    
    /**
     * Struct for creating the setup phase easier.
     */
    struct SpawnPositionList {
        /**
         * An array of spawn positions.
         */
        const positionid_t * spawn_positions;
        
        /**
         * The length of spawn_positions.
         */
        spaces_t spawn_position_count;
    }; // struct SpawnPositionList
    
    class SetupPhase;
    
    /**
     * Creates a new setup phase. This variation allows for fixed size arrays
     * as inputs.
     *
     * @param spawn_position_lists                  An array of spawn position
     *                                              lists indexed by the player.
     * @param player_count                          The number of players
     *                                              in the setup phase.
     * @param first_turn_after_setup_player_index   The index of the first
     *                                              player's turn when this
     *                                              phase has ended.
     */
    SetupPhase * createSetupPhase(SpawnPositionList * spawn_position_lists,
                                  unsigned int player_count,
                                  unsigned int first_turn_after_setup_player_index = 0);
    
    /**
     * The setup phase. Each player sets all of their pieces at once in acending
     * player index order starting from the current player at the start of the
     * phase.
     */
    class SetupPhase : public IPhaseRule, public kettle::utils::ISender {
    public:
        /**
         * Construct the setup phase.
         *
         * @param spawn_positions_by_player_index       An array of arrays
         *                                              listing the spawn
         *                                              positions for each
         *                                              player indexed by the
         *                                              player index. Takes
         *                                              ownership over all of
         *                                              these arrays.
         * @param spawn_position_count_by_player_index  How many spawn positions
         *                                              each player has indexed
         *                                              by the player index.
         *                                              Takes ownership.
         * @param player_count                          The number of players
         *                                              in the setup phase.
         * @param first_turn_after_setup_player_index   The index of the first
         *                                              player's turn when this
         *                                              phase has ended.
         */
        SetupPhase(const positionid_t * const * spawn_positions_by_player_index,
                   const spaces_t * spawn_position_count_by_player_index,
                   unsigned int player_count,
                   unsigned int first_turn_after_setup_player_index = 0);
        
        /**
         * Deconstructor.
         */
        ~SetupPhase();
        
        /**
         * Initializes the phase data.
         *
         * @param context           The match context.
         */
        void initialize(const MatchContext * context);
        
        /**
         * Updates the phase.
         *
         * The current player will continue to place pieces until the player
         * can place no more or the player idles.
         *
         * @param context           The match context.
         * @return                  The reason this function returned. On the
         *                          player idling,
         *                          kPhaseUpdateBreakReasonWaitingOnPlayer. On
         *                          the player has placed all of the pieces,
         *                          kPhaseUpdateBreakReasonQuicksavePoint. On
         *                          all players have laid their peices,
         *                          kPhaseUpdateBreakReasonPhaseEndQuicksavePoint.
         */
        PhaseUpdateBreakReason update(MatchContext * context);
        
        /**
         * Gets the type of this class.
         */
        kettle::utils::hash_t getType() const;
        
        /**
         * Gets the type of this class.
         */
        static kettle::utils::hash_t getClassType();
        
    protected:
        /**
         * An array of arrays listing the spawn positions for each player
         * indexed by the player index.
         */
        const positionid_t * const * m_spawn_positions_by_player_index;
        
        /**
         * How many spawn positions each player has indexed by the player index.
         */
        const spaces_t * m_spawn_position_count_by_player_index;
        
        /**
         * The number of players in the setup phase.
         */
        const unsigned int m_player_count;
        
        /**
         * The index of the first player's turn.
         */
        const unsigned int m_first_turn_after_setup_player_index;
        
        /**
         * Store's the player's turn on initializing the phase. Players will
         * setup their pieces until we get back to this player.
         */
        unsigned int m_first_player_to_setup_index;
        
    private:
        // disable copy and assign
        SetupPhase(const SetupPhase &);
        void operator=(const SetupPhase &);
    };
} // namespace game

#endif /* SetupPhase_hpp */
