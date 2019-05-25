#ifndef ENPASSANT_H
#define ENPASSANT_H

#include "move.h"
#include "board.h"

class EnPassant: public Move{
public:
    EnPassant(Board board, std::pair<int,int> from, std::pair<int,int> dest, Colour colour);
    Board movePiece(char promoteTo = 0) override;
};

#endif
