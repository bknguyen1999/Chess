#ifndef CASTLE_H
#define CASTLE_H

#include "move.h"
//#include "board.h"

class Castle: public Move{
public:
    Castle(Board board, std::pair<int,int> from, std::pair<int,int> dest, Colour colour);
    Board movePiece(char promoteTo = 0) override;
};

#endif
