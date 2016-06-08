//
//  IBoard.hpp
//  Plazma Lights Off
//
//  Created by Derek Higgs on 5/28/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

#ifndef IBoard_hpp
#define IBoard_hpp

#include "IPiece.hpp"
#include "RouteSet.hpp"

namespace game {
    class IBoard {
    public:
        virtual ~IBoard() {}
        
        virtual IBoard * clone() const = 0;
        
        virtual IPiece * getPieceAt(positionid_t position_id) const = 0;
        
        /**
         * Locates the piece at the position.
         * The caller keeps ownership of the piece.
         * @param piece         The piece to place.
         * @param position_id   The postion to place the piece.
         */
        virtual bool setPieceAt(IPiece * piece, positionid_t position_id) = 0;
        virtual IPiece * removePieceAt(positionid_t position_id) const = 0;
        virtual IPiece * removePiece(IPiece * piece) const = 0;
        
        virtual spaces_t getMaxAdjacentIds() const = 0;
        
        /**
         * Gets the position IDs adjacent to the given position.
         * @param position_id               The ID of the postion to search.
         * @param o_adjacent_position_ids   (optional) An array to be filled
         *                                  with the position IDs of the
         *                                  adjacent spaces.
         * @return                          The number of adjacent spaces.
         */
        virtual spaces_t getAdjacentPositionIds(positionid_t position_id,
                                                int * o_adjacent_position_ids) const = 0;
        
    protected:
        IBoard() {}
        
    private:
        // disable copy and assign
        IBoard(const IBoard &);
        void operator=(const IBoard &);
    }; // class IBoard
    
    flags32_t getBlockFlagsAt(const IBoard * board, positionid_t position_id);
    flags32_t getPassFlagsAt(const IBoard * board, positionid_t position_id);
    
    bool canStopOn(const IPiece * IPiece,
                   const IBoard * board,
                   positionid_t position_id);
    bool canPass(const IPiece * IPiece,
                 const IBoard * board,
                 positionid_t position_id);
    
    /**
     * Gets the routes that a piece may go.
     *
     * If there isn't enough data to store the route information, then an error
     * message will be logged and this method will return what information it
     * can record.
     *
     * @param board
     * @param piece
     * @return
     */
    unsigned int getRoutes(const IBoard * board,
                           const IPiece * piece,
                           unsigned int max_result_length,
                           RouteSet & o_routes);
    
} // namespace game

#endif /* IBoard_hpp */
