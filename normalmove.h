#ifndef NORMAL_MOVE_H
#define NORMAL_MOVE_H

#include "move.h"
#include "board.h"

class NormalMove: public Move{
public:
    NormalMove(Board board, std::pair<int,int> from, std::pair<int,int> dest, Colour colour);
    Board movePiece(char promoteTo = 0) override;
};

#endif
