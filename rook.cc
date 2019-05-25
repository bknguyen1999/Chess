#include "rook.h"

using namespace std;

Rook::Rook(Colour colour) :Piece{colour} {
	value = 5;
}

PieceType Rook::getType() {
    return PieceType::Rook;
}

int Rook::getValue() {
  return value;
}
Piece* Rook::clonePiece() {
	Piece *newRook = new Rook{getColour()};
	if(getHasMoved()){
		newRook->setMoved();
	}
	newRook->setConsecutiveKills(getConsecutiveKills());
	newRook->setKillCount(getKilledCount());
	return newRook;
}

vector<pair<int, int>> Rook::getMoves(pair<int, int> pos) {
	vector<pair<int,int>> moves;
	int row = pos.first;
	int col = pos.second;
	pair<int,int> possible;
	for (int i = row ; i <= 7; i++) {
		possible = make_pair(i, col);
		moves.emplace_back(possible);
	}
	for(int i = row; i >= 0; i--){
		possible = make_pair(i,col);
		moves.emplace_back(possible);
	}
	for(int i = col; i <= 7; i++){
		possible = make_pair(row,i);
		moves.emplace_back(possible);
	}
	for(int i = col; i >= 0; i--){
		possible = make_pair(row,i);
		moves.emplace_back(possible);
	}
	moves = remove(moves);
	return moves;
}

vector<pair<int, int>> Rook::getCaptureMoves(pair<int, int> pos) {
     return getMoves(pos);
}

Rook::~Rook() {}
