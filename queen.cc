#include "queen.h"

using namespace std;

Queen::Queen(Colour colour) : Piece{colour} {
    value = 9;
}

PieceType Queen::getType() {
    return PieceType::Queen;
}

vector<pair<int, int>> Queen::getMoves(pair<int, int> pos) {
    // all diagonals and rows and cols from pos
    vector<pair<int, int>> moves;
    int row = pos.first;
    int col = pos.second;
    pair<int, int> d1; // diagonals
    pair<int, int> d2; // ...
    pair<int, int> d3; // ...
    pair<int, int> d4; // diagonals
    pair<int, int> l1; // lines
    pair<int, int> l2; // lines
    pair<int, int> l3; // lines
    pair<int, int> l4; // lines
    for (int i = 0; i < 8; i++) {
        l1 = make_pair(row + i, col);
        l2 = make_pair(row, col + i);
        l3 = make_pair(row, col - i);
        l4 = make_pair(row - i, col);
        d1 = make_pair(row+i, col+i);
        d2 = make_pair(row+i, col-i);
        d3 = make_pair(row-i, col+i);
        d4 = make_pair(row-i, col-i);
        moves.emplace_back(l1);
        moves.emplace_back(l2);
        moves.emplace_back(l3);
        moves.emplace_back(l4);
        moves.emplace_back(d1);
        moves.emplace_back(d2);
        moves.emplace_back(d3);
        moves.emplace_back(d4);
    }
    moves = remove(moves);
    return moves;
}

int Queen::getValue() {
  return value;
}
vector<pair<int, int>> Queen::getCaptureMoves(pair<int, int> pos) {
    return getMoves(pos);
}

Piece* Queen::clonePiece(){
    Piece *q = new Queen{getColour()};
    if(getHasMoved()){
		q->setMoved();
	}
    q->setConsecutiveKills(getConsecutiveKills());
	q->setKillCount(getKilledCount());
    return q;
}

Queen::~Queen() {}
