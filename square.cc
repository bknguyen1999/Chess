#include "square.h"
using namespace std;

Square::Square(int row, int col): pos{pair<int,int>(row, col)}{}

Square::Square(const Square &other): pos{other.pos}{
    if(other.piece){
        piece = other.piece->clonePiece();
    }
    else{
        piece = nullptr;
    }
}

Square& Square::operator=(const Square &other){
    if(piece){
        delete piece;
        piece = nullptr;
    }
    Square copy = other;
    swap(pos, copy.pos);
    swap(piece, copy.piece);
    return *this;
}

pair<int,int> Square::getPos() const{
    return pos;
}

Piece* Square::getPiece() const{
    return piece;
}

void Square::addPiece(Piece *p){
    piece = p;
}

void Square::removePiece(){
	delete piece;
    piece = nullptr; 
}

bool Square::operator==(const Square &other) const{
    return pos == other.pos;
}

Square::~Square(){
        delete piece;
	piece = nullptr;
}
