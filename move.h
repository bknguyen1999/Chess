#ifndef MOVE_H
#define MOVE_H

#include <utility>
#include <vector>
#include "piece.h"
#include "square.h"
#include "board.h"

class InvalidMove{};


class Move{
protected:
    Board board;
    std::pair<int,int> from;
    std::pair<int,int> dest;
    Colour colour;
    bool isPathClear();
    bool isInBoard(std::pair<int,int> pos);
public:
    Move(Board board, std::pair<int,int> from, std::pair<int,int> dest, Colour colour);
    std::pair<int,int> getFrom();
    std::pair<int,int> getDest(); 
    bool isValid();
    bool checkMove(); // checks to see if the move will put you in check
    bool isCastle(); // checks if its a castle move
    bool isEnPassant(); // checks if its an en passant move
    bool isCapture();
    bool isPromotePawn();
    bool isNormalMove();
    virtual Board movePiece(char promoteTo = 0); // will be overriden by each move type
    virtual ~Move();
};

#endif
