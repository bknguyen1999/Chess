#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"

class Bishop : public Piece {
public:
    Bishop(Colour colour);
    Piece *clonePiece() override;
    PieceType getType() override;
    int getValue() override;
    std::vector<std::pair<int, int>> getMoves(std::pair<int, int> pos) override;
    std::vector<std::pair<int, int>> getCaptureMoves(std::pair<int, int> pos) override;
    ~Bishop();
};

#endif
