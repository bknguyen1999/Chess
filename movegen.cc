#include "movegen.h"
#include <algorithm>
#include <iostream>
using namespace std;
MoveGen::MoveGen(Board board, Colour colour): board{board}, colour{colour} {}


bool MoveGen::legalMoveLeft() {
	// get player's pieces
	vector<pair<int,int>> team = board.getPieces(colour);
	vector<movepair> legalMoves;
	// for each piece get pseudolegal moves then check if legal
	for (auto mem: team) {
		Piece *currPiece = board.getSquare(mem.first, mem.second).getPiece();
		vector<pair<int,int>> moves = currPiece->getMoves(mem);
		vector<pair<int, int>> capturemoves = currPiece->getCaptureMoves(mem);
		moves.insert(moves.end(), capturemoves.begin(), capturemoves.end());
		unique(moves.begin(),moves.end());

		random_shuffle(moves.begin(), moves.end());
		for(auto move: moves) {
			Board copy = board;
			Move currMove{copy, mem, move, colour};
			if (currMove.checkMove()) {
					return true;
		 }
		}
	}
	return false;
}


vector<movepair> MoveGen::getLegalMoves() {
		// get player's pieces
	vector<pair<int,int>> team = board.getPieces(colour);
	vector<movepair> legalMoves;
	// randomize piece lineup
	random_shuffle(team.begin(), team.end());
	// for each piece get pseudolegal moves then check if legal
	for (auto mem: team) {
		Piece *currPiece = board.getSquare(mem.first, mem.second).getPiece();
		vector<pair<int,int>> moves = currPiece->getMoves(mem);
		vector<pair<int, int>> capturemoves = currPiece->getCaptureMoves(mem);
		moves.insert(moves.end(), capturemoves.begin(), capturemoves.end());
		unique(moves.begin(),moves.end());
		// randomize player's moves
		random_shuffle(moves.begin(), moves.end());
		for(auto move: moves) {
			Board copy = board;
			Move currMove{copy, mem, move, colour};
			if (currMove.checkMove()) {
			 legalMoves.push_back(make_pair(mem, move));
		 }
		}
	}
	random_shuffle(legalMoves.begin(), legalMoves.end());
	return legalMoves;
}
