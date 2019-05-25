#include "knight.h"

using namespace std;

Knight::Knight(Colour colour) : Piece{colour} {
    value = 3;
}

Piece* Knight::clonePiece(){
    Piece *k = new Knight{getColour()};
    if(getHasMoved()){
		k->setMoved();
	}
    k->setConsecutiveKills(getConsecutiveKills());
	k->setKillCount(getKilledCount());
    return k;
}

PieceType Knight::getType() {
    return PieceType::Knight;
}

int Knight::getValue() {
  return value;
}

vector<pair<int, int>> Knight::getMoves(pair<int, int> pos) {
    // sum fuckd shit lol
    int row = pos.first;
    int col = pos.second;
    vector<pair<int, int>> moves;
    pair<int, int> h1 = make_pair(row-2, col+1);
    moves.emplace_back(h1);
    pair<int, int> h2 = make_pair(row-1, col+2);
    moves.emplace_back(h2);
    pair<int, int> h3 = make_pair(row+1, col+2);
    moves.emplace_back(h3);
    pair<int, int> h4 = make_pair(row+2, col+1);
    moves.emplace_back(h4);
    pair<int, int> h5 = make_pair(row+2, col-1);
    moves.emplace_back(h5);
    pair<int, int> h6 = make_pair(row+1, col-2);
    moves.emplace_back(h6);
    pair<int, int> h7 = make_pair(row-1, col-2);
    moves.emplace_back(h7);
    pair<int, int> h8 = make_pair(row-2, col-1);
    moves.emplace_back(h8);
    moves = remove(moves);
    return moves;
}

vector<pair<int, int>> Knight::getCaptureMoves(pair<int, int> pos) {
    return getMoves(pos);
}
Knight::~Knight() {}
