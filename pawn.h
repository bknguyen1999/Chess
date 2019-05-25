#ifndef PAWN_H
#define PAWN_H

#include "piece.h"
#include <vector>
#include <utility>

class Pawn : public Piece {
public:
    Pawn(Colour colour);
    PieceType getType() override;
    Piece *clonePiece() override;
    int getValue() override;
    std::vector<std::pair<int,int>> getCaptureMoves(std::pair<int, int> pos) override;
    std::vector<std::pair<int, int>> getMoves(std::pair<int, int> pos) override;
    ~Pawn(); 
};

#endif
