#ifndef ROOK_H
#define ROOK_H

#include "piece.h"

class Rook : public Piece {
public:
    Rook(Colour colour);
    PieceType getType() override;
    Piece* clonePiece() override;
    int getValue() override;
    std::vector<std::pair<int, int>> getMoves(std::pair<int, int> pos) override;
   std::vector<std::pair<int, int>> getCaptureMoves(std::pair<int, int> pos) override;
    ~Rook();
};

#endif
