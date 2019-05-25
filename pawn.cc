#include "pawn.h"
using namespace std;

Pawn::Pawn(Colour colour) : Piece{colour} {
    value = 1;
}

PieceType Pawn::getType() {
    return PieceType::Pawn;
}

Piece* Pawn::clonePiece(){
    Piece *p = new Pawn{getColour()};
    if(getHasMoved()){
		p->setMoved();
	}
    p->setConsecutiveKills(getConsecutiveKills());
	p->setKillCount(getKilledCount());
    return p;
}
int Pawn::getValue() {
  return value;
}


vector<std::pair<int,int>> Pawn::getCaptureMoves(pair<int, int> pos){
    int row = pos.first;
    int col = pos.second;
    vector<pair<int,int>> moves;
    if(getColour() == Colour::Black){
        if(row != 7){
            pair<int,int> m = make_pair(row+1, col+1);
            pair<int,int> m2 = make_pair(row+1, col-1);
            if(col == 0){
                moves.emplace_back(m);
            }
            else if(col == 7){
                moves.emplace_back(m2);
            }
            else{
                moves.emplace_back(m);
                moves.emplace_back(m2);
            }
        }
    }
    else{
        if(row != 0){
            pair<int,int> m = make_pair(row-1, col + 1);
            pair<int,int> m2 = make_pair(row-1, col - 1);
            if(col == 0){
                moves.emplace_back(m);
            }
            if(col == 7){
                moves.emplace_back(m2);
            }
            else{
                moves.emplace_back(m);
                moves.emplace_back(m2);
            }
        }
    }
    moves = remove(moves);
    return moves;
}

vector<pair<int, int>> Pawn::getMoves(pair<int, int> pos) {
    // only in front if it has moved before, else in front and in front front
    int row = pos.first;
    int col = pos.second;
    vector<pair<int,int>> moves;

    if (getColour() == Colour::Black){
        pair<int,int> m = make_pair(row + 1, col);
        pair<int,int> m2 = make_pair(row +  2, col);
        if(!getHasMoved()){
            moves.emplace_back(m);
            moves.emplace_back(m2);
        }
        else{
            moves.emplace_back(m);
        }
    }
    else if(getColour() == Colour::White){
        pair<int,int> m = make_pair(row - 1, col);
        pair<int,int> m2 = make_pair(row -  2, col);
        if(!getHasMoved()){
            moves.emplace_back(m);
            moves.emplace_back(m2);
        }
        else{
            moves.emplace_back(m);
        }
    }
    moves = remove(moves);
    return moves;
}

Pawn::~Pawn() {}
