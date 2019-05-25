#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"

class Queen : public Piece {
public:
    Queen(Colour colour);
    PieceType getType() override;
    std::vector<std::pair<int, int>> getMoves(std::pair<int, int> pos) override;
    int getValue() override;
    std::vector<std::pair<int, int>> getCaptureMoves(std::pair<int, int> pos) override;
    Piece *clonePiece() override;
    ~Queen();
};

#endif
