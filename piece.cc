#include "piece.h"
using namespace std;

Piece::Piece(Colour c): colour{c}{}


Colour Piece::getColour(){
    return colour;
}

bool Piece::getHasMoved() {
	return hasMoved;
}

void Piece::setMoved() {
	hasMoved = true;
}

int Piece::getKilledCount(){
    return killCount;
}

int Piece::getConsecutiveKills(){
    return consecutiveKills;
}

void Piece::incKillCount(){
    killCount++;
}

void Piece::incConsecutiveKills(){
    consecutiveKills++;
}

void Piece::resetConsecutiveKills(){
    consecutiveKills = 0;
}

void Piece::setKillCount(int n){
    killCount = n;
}
void Piece::setConsecutiveKills(int n){
    consecutiveKills = n;
}

vector<pair<int,int>> Piece::remove(vector<pair<int,int>> v){
    vector<pair<int,int>> newmoves;
    for(auto move: v){
        int row = move.first;
        int col = move.second;
        if (row > 7 || row < 0 || col > 7 || col < 0){
            continue;
        }
        newmoves.emplace_back(move);
    }
    return newmoves;
}

Piece::~Piece() {}
