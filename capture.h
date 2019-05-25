#ifndef CAPTURE_H
#define CAPTURE_H

#include "move.h"
#include "board.h"

class Capture: public Move{
public:
    Capture(Board board, std::pair<int,int> from, std::pair<int,int> dest, Colour colour);
    Board movePiece(char promoteTo = 0) override;
};

#endif
