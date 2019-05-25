#include "king.h"
using namespace std;

King::King(Colour c): Piece{c}{
    value = 0;
}

Piece* King::clonePiece(){
    Piece *k = new King{getColour()};
    if(getHasMoved()){
		k->setMoved();
	}
    k->setConsecutiveKills(getConsecutiveKills());
	k->setKillCount(getKilledCount());
    return k;
}

PieceType King::getType(){
    return PieceType::King;
}

vector<pair<int,int>> King::getCaptureMoves(pair<int, int> pos){
    return getMoves(pos);
}
int King::getValue() {
  return value;
}

// gets all possible moves the piece can make, even if there's a piece in that square
vector<pair<int,int>> King::getMoves(pair<int,int> curpos){
    vector<pair<int,int>> moves;
    int row = curpos.first;
    int col = curpos.second;
    pair<int,int> possible;
    if (!getHasMoved()){
        pair<int,int> castle = make_pair(row, col + 2);
        pair<int,int> castle2 = make_pair(row, col - 2);
        moves.emplace_back(castle);
        moves.emplace_back(castle2);
    }
    if(row - 1 >= 0){
        possible = make_pair(row-1, col);
        moves.emplace_back(possible);
    }
    if(col - 1 >= 0){
        possible = make_pair(row, col-1);
        moves.emplace_back(possible);
    }
    if(col + 1 <= 7){
        possible = make_pair(row, col + 1);
        moves.emplace_back(possible);
    }
    if (row + 1 <= 7){
        possible = make_pair(row+1, col);
        moves.emplace_back(possible);
    }
    if(row + 1 <= 7 && col + 1 <= 7){
        possible = make_pair(row + 1, col + 1);
        moves.emplace_back(possible);
    }
    if(row + 1 <= 7 && col - 1 >= 0){
        possible = make_pair(row + 1, col - 1);
        moves.emplace_back(possible);
    }
    if(row - 1 >= 0 && col - 1 >= 0){
        possible = make_pair(row - 1, col - 1);
        moves.emplace_back(possible);
    }
    if(row - 1 >= 0 && col + 1 <= 7){
        possible = make_pair(row - 1, col + 1);
        moves.emplace_back(possible);
    }
    moves = remove(moves);
    return moves;

}

King::~King() {}
