#ifndef PROMOTE_PAWN_H
#define PROMOTE_PAWN_H

#include "move.h"
#include "board.h"

class PromotePawn: public Move{
public:
    PromotePawn(Board board, std::pair<int,int> from, std::pair<int,int> dest, Colour colour);
    Board movePiece(char promoteTo) override;
};

#endif
