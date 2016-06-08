//
//  TestMatch.cpp
//  Plazma Lights Off
//
//  Created by Derek Higgs on 6/3/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

#include "TestMatch.hpp"

#include <iostream>

#include "Match.hpp"
#include "IPhaseRules.hpp"
#include "IBoard.hpp"

using namespace std;
using namespace game;

PhaseUpdateBreakReason getReason() {
    static int nextReason = 3;
    PhaseUpdateBreakReason reason = (PhaseUpdateBreakReason)nextReason;
    nextReason = (nextReason + 1) % 4;
    return reason;
}

const phase_t kPhaseSetup = kPhaseInitial;
PhaseUpdateBreakReason updateSetup(MatchContext * context) {
    cout << "Setup update" << endl;
    return getReason();
}

const phase_t kPhaseUpkeep = 1;
PhaseUpdateBreakReason updateUpkeep(MatchContext * context) {
    cout << "Upkeep update" << endl;
    return getReason();
}

const phase_t kPhaseTurn = 2;
PhaseUpdateBreakReason updateTurn(MatchContext * context) {
    cout << "Turn update" << endl;
    return getReason();
}

const phase_t kNextPhase[] = { kPhaseUpkeep, kPhaseTurn, kPhaseUpkeep };

bool isMatchFinished(const MatchContext * context) {
    static int checks = 0;
    return ++checks > 7;
}

class TestPhaseRules : public IPhaseRules {
public:
    TestPhaseRules() {}
    ~TestPhaseRules() {}
    
    void initializePhase(const MatchContext * context,
                         phase_t current_phase) {
        cout << "Initialize phase " << current_phase << endl;
    }
    
    PhaseUpdateBreakReason updatePhase(MatchContext * context,
                                       phase_t current_phase) {
        if(current_phase >= 0) {
            switch (current_phase) {
                case kPhaseSetup:
                    return updateSetup(context);
                    
                case kPhaseUpkeep:
                    return updateUpkeep(context);
                    
                case kPhaseTurn:
                    return updateTurn(context);
            }
        }
        return kPhaseUpdateBreakReasonPhaseEnd;
    }
    
    phase_t getNextPhase(phase_t current_phase) const {
        if(current_phase >= 0) {
            return kNextPhase[ current_phase ];
        }
        return current_phase;
    }
    
    bool didPlayerWin(const MatchContext * context,
                      unsigned int player_index) const {
        return isMatchFinished(context);
    }
    
    bool isFinished(const MatchContext * context) const {
        return isMatchFinished(context);
    }
}; // class TestPhaseRules

class DummyBoard : public IBoard {
public:
    ~DummyBoard() {}
    
    IBoard * clone() const {
        return new DummyBoard();
    }
    
    IPiece * getPieceAt(positionid_t position_id) const {
        return nullptr;
    }
    
    bool setPieceAt(IPiece * piece, positionid_t position_id) {
        return false;
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
    
}; // class DummyBoard

int testMatch() {
    IPlayer * players[] = {};
    unsigned int max_pieces_by_player[] = {};
    
    IBoard * board = new DummyBoard();
    
    IPhaseRules * rules = new TestPhaseRules();
    
    Match * match = Match::create(players, 0, max_pieces_by_player, board, rules);
    
    while (!match->isFinished()) {
        MatchUpdateBreakReason reason = match->update();
        
        const char * status;
        switch (reason) {
            case game::kMatchUpdateBreakReasonQuicksavePoint:
                status = "Quicksave";
                break;
                
            case game::kMatchUpdateBreakReasonWaitingOnPlayer:
                status = "Waiting";
                break;
                
            case game::kMatchUpdateBreakReasonMatchEnd:
                status = "End";
                break;
        }
        
        cout << status << endl;
    }
    
    cout << "Match has ended." << endl;
    
    delete match;
    
    return 0;
}