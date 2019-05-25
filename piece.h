#ifndef PIECE_H
#define PIECE_H

//#include "square.h"
#include "player.h"
#include <utility>
#include <vector>

enum class PieceType{King, Queen, Rook, Bishop, Knight, Pawn, Null};

class Piece{
    const Colour colour;
    bool hasMoved = false;
    int killCount = 0;
    int consecutiveKills = 0;
protected:
    int value;
    std::vector<std::pair<int,int>> remove(std::vector<std::pair<int,int>> v);
public:
    Piece(Colour c);
    virtual Piece *clonePiece() = 0;
    Colour getColour();
    virtual int getValue() = 0;
    virtual PieceType getType() = 0;
    virtual std::vector<std::pair<int, int>> getMoves(std::pair<int,int> curpos) = 0;
    virtual std::vector<std::pair<int, int>> getCaptureMoves(std::pair<int, int> pos) = 0;
    virtual ~Piece();
    void setMoved();
    bool getHasMoved();
    int getKilledCount();
    int getConsecutiveKills();
    void incKillCount();
    void incConsecutiveKills();
    void resetConsecutiveKills();
    void setKillCount(int n);
    void setConsecutiveKills(int n);
};
//inline Piece::~Piece() {}
#endif
