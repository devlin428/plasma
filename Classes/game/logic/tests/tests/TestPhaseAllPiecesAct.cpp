//
//  TestPhaseAllPiecesAct.cpp
//  tests
//
//  Created by Derek Higgs on 6/9/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

#include "TestPhaseAllPiecesAct.hpp"

#include <iostream>

#include "PhaseAllPlayerPiecesAct.hpp"
#include "MatchContext.hpp"
#include "IPiece.hpp"

#include "TestPhase.hpp"

using namespace std;
using namespace game;

namespace {
    class TestPiece : public IPiece {
    public:
        TestPiece(unsigned int id) : m_id(id) {}
        ~TestPiece() {}
        
        positionid_t getPositionId() const {
            return 0;
        }
        
        void setPositionId(positionid_t position_id) {}
        
        flags32_t getBlockFlags() const{
            return 0;
        }
        
        flags32_t getPassFlags() const {
            return 0;
        }
        
        spaces_t getMaxMovementDistance() const {
            return 0;
        }
        
        action::action_t act(const MatchContext * context,
                             action::phase_t phase,
                             const kettle::utils::UserInfo * phase_info,
                             kettle::utils::UserInfo * o_action_info) {
            cout << "Piece " << m_id << " was told to do " << phase << endl;
            return 0;
        }
        
    protected:
        unsigned int m_id;
        
    private:
        // disable copy and assign
        TestPiece(const TestPiece &);
        void operator=(const TestPiece &);
    }; // class TestPiece
}

int TestPhaseAllPiecesAct() {
    PhaseAllPlayerPiecesAct phase3(3, false), phase12(12, true);
    
    TestPiece piece1(1), piece2(2), piece3(3);
    IPiece * player_pieces[] = {
        &piece1,
        &piece2,
        &piece3,
        &piece2
    };
    unsigned int max_pieces = sizeof(player_pieces) / sizeof(*player_pieces);
    IPiece ** pieces[] = { player_pieces };
    
    MatchContext context = {
        nullptr,
        pieces,
        &max_pieces,
        nullptr,
        nullptr,
        sizeof(pieces) / sizeof(*pieces),
        0
    };
    
    testPhase(&context, &phase3);
    testPhase(&context, &phase12);
    
    return 0;
}
