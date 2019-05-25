#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"

class Knight : public Piece {
public:
    Knight(Colour colour);
    PieceType getType() override;
    Piece *clonePiece() override;
    std::vector<std::pair<int, int>> getMoves(std::pair<int, int> pos) override;
    std::vector<std::pair<int, int>> getCaptureMoves(std::pair<int, int> pos) override;
    int getValue() override;
    ~Knight();    
};

#endif
