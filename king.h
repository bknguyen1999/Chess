#ifndef KING_H
#define KING_H

#include "piece.h"

class King : public Piece {
public:
    King(Colour colour);
    Piece *clonePiece() override;
    PieceType getType() override;
    std::vector<std::pair<int,int>> getCaptureMoves(std::pair<int, int> pos) override;
    std::vector<std::pair<int, int>> getMoves(std::pair<int, int> pos) override;
    int getValue() override;
    ~King();
};

#endif
