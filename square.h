#ifndef SQUARE_H
#define SQUARE_H

//#include "board.h"
#include "piece.h"
#include <utility>

class Square{
    std::pair<int,int> pos;
    Piece *piece = nullptr;
public:
    Square(int row, int col);
    Square(const Square &other);
    Square &operator=(const Square &other);
    std::pair<int,int> getPos() const;
    Piece *getPiece() const;
    void addPiece(Piece *p);
    void removePiece();
    bool operator==(const Square &other) const;
    ~Square();
};

#endif
