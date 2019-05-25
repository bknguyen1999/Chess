#include "bishop.h"

using namespace std;

Bishop::Bishop(Colour colour) : Piece{colour} {
	value = 3;
}

PieceType Bishop::getType() {
    return PieceType::Bishop;
}

Piece* Bishop::clonePiece() {
	Piece *newBishop = new Bishop{getColour()};
	if(getHasMoved()){
		newBishop->setMoved();
	}
	newBishop->setConsecutiveKills(getConsecutiveKills());
	newBishop->setKillCount(getKilledCount());
	return newBishop;
}
int Bishop::getValue() {
  return value;
}

vector<pair<int, int>> Bishop::getMoves(pair<int, int> pos) {
	vector<pair<int, int>> moves;
	int row = pos.first;
	int col = pos.second;
	pair<int,int> d1, d2, d3, d4;
	for (int i = 0; i < 8; i++) {
		d1 = make_pair(row+i, col+i);
		d2 = make_pair(row-i, col-i);
		d3 = make_pair(row+i, col-i);
		d4 = make_pair(row-i, col+i);
		moves.emplace_back(d1);
		moves.emplace_back(d2);
		moves.emplace_back(d3);
        moves.emplace_back(d4);
	}
    moves = remove(moves);
	return moves;
}


vector<pair<int, int>> Bishop::getCaptureMoves(pair<int, int> pos) {
	return	getMoves(pos);
}
Bishop::~Bishop() {}
