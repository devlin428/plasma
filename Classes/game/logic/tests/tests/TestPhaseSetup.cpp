//
//  TestPhaseSetup.cpp
//  tests
//
//  Created by Derek Higgs on 6/7/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

#include "TestPhaseSetup.hpp"

#include <algorithm>
#include <iostream>

#include "Messaging.hpp"
#include "UserInfo.hpp"

#include "SetupPhase.hpp"
#include "MatchContext.hpp"
#include "IPlayer.hpp"
#include "IBoard.hpp"
#include "IPiece.hpp"
#include "PlayerActionsSetup.h"

using namespace std;
using namespace kettle::utils;
using namespace game;
using namespace game::player_action;

namespace {
    class TestPiece : public IPiece {
    public:
        TestPiece(unsigned int type) : m_type(type) {}
        
        ~TestPiece() {}
        
        positionid_t getPositionId() const {
            return m_position_id;
        }
        
        void setPositionId(positionid_t position_id) {
            cout << "Set piece of type " << m_type << " at " << position_id << endl;
            m_position_id = position_id;
        }
        
        flags32_t getBlockFlags() const {
            return 0;
        }
        
        flags32_t getPassFlags() const {
            return 0;
        }
        
        spaces_t getMaxMovementDistance() const {
            return 0;
        }
    protected:
        unsigned int m_type;
        positionid_t m_position_id;
    }; // class TestPiece : public IPiece
    
    class TestPlayer : public IPlayer {
    public:
        TestPlayer() {}
        ~TestPlayer() {}
        
        player_action::action_t act(const MatchContext * context,
                                    player_action::phase_t phase,
                                    const kettle::utils::UserInfo * phase_info,
                                    kettle::utils::UserInfo * o_action_info) {
            static int action = -1;
            action = (action+1) % 4;
            switch (action) {
                case 0:
                    if(o_action_info) {
                        static int piece_type = 0;
                        o_action_info->put(kPieceType, ++piece_type);
                        
                        static int position_index = 0;
                        o_action_info->put(kPositionIndex, position_index);
                        position_index = (position_index+1)%4;
                    }
                    
                    return kSpawn;
                    
                case 1:
                    return kThinking;
                    
                case 2:
                    return kFinishedSpawning;
                    
                case 3:
                    return kSurrender;
                    
                default:
                    break;
            }
            return kSpawn;
        }
        
        IPiece * spawn(unsigned int type) {
            cout << "Created piece of type " << type << endl;
            return (IPiece *) new TestPiece(type);
        }
    }; // class TestPlayer : public IPlayer
    
    class TestBoard : public IBoard {
    public:
        TestBoard() {}
        ~TestBoard() {}
        
        IBoard * clone() const {
            return nullptr;
        }
        
        IPiece * getPieceAt(positionid_t position_id) const {
            return nullptr;
        }
        
        bool setPieceAt(IPiece * piece, positionid_t position_id) {
            piece->setPositionId(position_id);
            return true;
        }
        
        IPiece * removePieceAt(positionid_t position_id) const {
            return nullptr;
        }
        
        IPiece * removePiece(IPiece * piece) const {
            return nullptr;
        }
        
        spaces_t getMaxAdjacentIds() const {
            return 0;
        }
        
        spaces_t getAdjacentPositionIds(positionid_t position_id,
                                        int * o_adjacent_position_ids) const {
            return 0;
        }
    }; // class TestBoard : public IBoard
    
    void runPhase(MatchContext & context, IPhaseRule * phase) {
        phase->initialize(&context);
        
        PhaseUpdateBreakReason reason;
        while(true) {
            reason = phase->update(&context);
            switch (reason) {
                case game::kPhaseUpdateBreakReasonPhaseEndQuicksavePoint:
                    cout << "Phase ended with a quicksave point." << endl;
                    return;
                    
                case game::kPhaseUpdateBreakReasonQuicksavePoint:
                    cout << "Quicksave point" << endl;
                    break;
                    
                case game::kPhaseUpdateBreakReasonPhaseEnd:
                    cout << "Phase ended." << endl;
                    return;
                    
                case game::kPhaseUpdateBreakReasonWaitingOnPlayer:
                    cout << "Waiting on player " << context.current_player_turn << endl;
                    break;
            }
        }
    }
    
    void runPhase(IPhaseRule * phase) {
        TestPlayer player1, player2;
        IPlayer * players[] = {
            (IPlayer*)&player1,
            (IPlayer*)&player2
        };
        
        IPiece * player1pieces[] = { nullptr, nullptr};
        IPiece * player2pieces[] = { nullptr, nullptr, nullptr };
        IPiece ** pieces[] = {
            player1pieces,
            player2pieces
        };
        unsigned int max_pieces_by_player[] = {
            sizeof(player1pieces)/sizeof(*player1pieces),
            sizeof(player2pieces)/sizeof(*player2pieces)
        };
        
        TestBoard board;
        
        MatchContext context = {
            players,
            pieces,
            max_pieces_by_player,
            (IBoard *) &board,
            new Messaging(),
            sizeof(players)/sizeof(*players),
            1
        };
        
        runPhase(context, phase);
        
        delete context.messaging;
        
        unsigned int * max_iter = max_pieces_by_player;
        for(IPiece *** pieces_iter = pieces;
            pieces_iter != pieces + context.number_of_players;
            ++pieces_iter, ++max_iter) {
            for_each(*pieces_iter,
                     *pieces_iter + *max_iter,
                     [](const IPiece * piece){
                         if(piece) {
                             delete piece;
                         }
                     });
        }
    }
}

int testSetupPhase() {
    positionid_t player1_spawn_positions[] = { 0, 1, 2 };
    positionid_t player2_spawn_positions[] = { 3, 4 };
    SpawnPositionList spawn_positions[] = {
        {
            player1_spawn_positions,
            sizeof(player1_spawn_positions) / sizeof(*player1_spawn_positions)
        },
        {
            player2_spawn_positions,
            sizeof(player2_spawn_positions) / sizeof(*player2_spawn_positions)
        }
    };
    unsigned int player_count = sizeof(spawn_positions)/sizeof(*spawn_positions);
    
    IPhaseRule * phase = createSetupPhase(spawn_positions, player_count, 12);
    
    runPhase(phase);
    
    delete phase;
    
    return 0;
}
