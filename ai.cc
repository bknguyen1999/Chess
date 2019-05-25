#include "ai.h"
#include <algorithm>
#include <utility>
#include "move.h"
#include <iostream>
#include "enpassant.h"
#include "castle.h"
#include "capture.h"
#include "promotepawn.h"
#include "normalmove.h"
#include "movegen.h"
using namespace std;



AI::AI(Colour colour, int level): colour{colour}, level{level} {
	if (colour == Colour::Black) {
	 enemyColour = Colour::White;
	} else {
	enemyColour = Colour::Black;
	}
}
bool AI::getIsAI() { return true; }

movepair AI::getL1move(Board b) {
	MoveGen gen{b, colour};
	vector<movepair> allLegalMoves = gen.getLegalMoves();
	random_shuffle(allLegalMoves.begin(), allLegalMoves.end());
	for(auto move: allLegalMoves){
		pair<int,int> from = move.first;
		pair<int,int> dest = move.second;
		Board copy = b;
		Move check{copy, from, dest, colour};
		if(check.checkMove()){
			return move;
		}
	}
		return make_pair(make_pair(-1,-1),make_pair(-1,-1));
}

movepair AI::getL2move(Board b) { //prioritizes capture moves
	MoveGen gen{b, colour};
	vector<movepair> allLegalMoves = gen.getLegalMoves();
	random_shuffle(allLegalMoves.begin(), allLegalMoves.end());
	vector<movepair> check;
	vector<movepair> capture;
	vector<movepair> normal;
	for(auto move: allLegalMoves){
		pair<int,int> from = move.first;
		pair<int,int> dest = move.second;
		Board copy = b;
		Move checkmove{copy, from, dest, colour};
		if(checkmove.checkMove()){
			copy = makeMove(checkmove, copy, colour);
			Piece *destPiece = b.getSquare(dest.first, dest.second).getPiece();
			if(copy.isCheck(colour) != State::Normal){
				check.emplace_back(move);
				continue;
			}
			else if (checkmove.isCapture() || checkmove.isEnPassant() ||
			(checkmove.isPromotePawn() && destPiece && (destPiece->getColour() == enemyColour))){
				capture.emplace_back(move);
				continue;
			}
			else{
				normal.emplace_back(move);
				continue;
			}
		}
		else{
			continue;
		}
	}
	random_shuffle(check.begin(), check.end());
	random_shuffle(capture.begin(), capture.end());
	random_shuffle(normal.begin(), normal.end());
	for(auto move: check){
		return move;
	}
	for(auto move: capture){
		return move;
	}
	for(auto move: normal){
		return move;
	}
	// will never reach this case but need to silence error
  return getL1move(b);
}

movepair AI::getL3move(Board b) {
	vector<pair<int,int>> team = b.getPieces(colour);
	vector<pair<int,int>> enemies = b.getPieces(enemyColour);
	vector<pair<int,int>> unsafe; // SPOTS WHERE ENEMY CAN ATTACK
	vector<pair<int,int>> endangered; // PIECES OF MY TEAM IN DANGER
	vector<pair<int,int>> killers; //pieces of other team that can kill my pieces
	random_shuffle(team.begin(), team.end());
	random_shuffle(enemies.begin(), enemies.end());

	for(auto enemy: enemies){
		Piece *currPiece = b.getSquare(enemy.first, enemy.second).getPiece();
		if(currPiece == nullptr){
			continue;
		}
// get capture moves of enemy piece
		vector<pair<int,int>> captureMoves = currPiece->getCaptureMoves(enemy);
		for(auto dest: captureMoves){
			Board copy = b;
			Move check{copy, enemy, dest, enemyColour};
			Piece *destPiece = copy.getSquare(dest.first, dest.second).getPiece();

			if(check.isValid()){
				unsafe.emplace_back(dest);
				if (check.isPromotePawn()) {
					if (destPiece == nullptr) {
						continue;
					}
					else{
						if (destPiece->getColour()==colour) {
							endangered.emplace_back(dest);
					        killers.emplace_back(enemy);
						}
					}
				}
				else if(check.isCapture() || check.isEnPassant()){
					endangered.emplace_back(dest);
					killers.emplace_back(enemy);
				}
			}
		}
	}
	random_shuffle(unsafe.begin(), unsafe.end());
	random_shuffle(killers.begin(), killers.end());
	random_shuffle(endangered.begin(), endangered.end());
	if(endangered.size() == 0){ // no teamates are endangered
		random_shuffle(team.begin(), team.end());
		for(auto piece: team){ // checks if any teamates can make a safe capture, if not, can they make a capture
			Piece *curPiece = b.getSquare(piece.first, piece.second).getPiece();
			vector<pair<int,int>> captureMoves = curPiece->getCaptureMoves(piece);
			random_shuffle(captureMoves.begin(), captureMoves.end());
			for(auto move: captureMoves){
				Board copy = b;
				Move check{copy, piece, move, colour};
				Piece *target = copy.getSquare(move.first, move.second).getPiece();
				if(target == nullptr){
					continue;
				}
				if(find(captureMoves.begin(), captureMoves.end(), move) != captureMoves.end() &&
				find(unsafe.begin(), unsafe.end(), move) == unsafe.end()){ // checks if it can make a safe capture
					if(check.checkMove()){
						return make_pair(piece,move);
					}
				}
			}
		}
		for(auto piece: team){ // no teamates can make a capture, so make a safe move
			Piece *curPiece = b.getSquare(piece.first, piece.second).getPiece();
			vector<pair<int,int>> legalMove = curPiece->getMoves(piece);
			random_shuffle(legalMove.begin(), legalMove.end());
			for(auto move: legalMove){
				if(find(unsafe.begin(), unsafe.end(), move) == unsafe.begin()){
					continue;
				}
				Board copy = b;
				Move check{copy, piece, move, colour};
				if(check.checkMove()){
					return make_pair(piece,move);
				}
			}
		}
		return getL2move(b);
	}
	else{ // there are endangered teamates
		for(auto piece: team){ // checks if any teamates can kill the piece making a teamate endangered and its not gonna land on an unsafe square
			Piece *curPiece = b.getSquare(piece.first, piece.second).getPiece();
			if(curPiece == nullptr){
				continue;
			}
			vector<pair<int,int>> captureMoves = curPiece->getCaptureMoves(piece);
			for(auto move: captureMoves){ // search if endangered piece can kill the piece making it endangered
				if (find(killers.begin(), killers.end(), move) == killers.begin()){
					Board copy = b;
					Move check{copy, piece, move, colour};
					if(find(unsafe.begin(), unsafe.end(), move) == unsafe.end()){ // kill on safe square
						if(check.checkMove()){
							return make_pair(piece, move);
						}
					}
				}
			}
		}
		for (auto piece: endangered) { // checks for avoiding capture moves
			Piece *currPiece = b.getSquare(piece.first, piece.second).getPiece();
			if(currPiece == nullptr){
				continue;
			}
			vector<pair<int,int>> moves = currPiece->getMoves(piece);
			random_shuffle(moves.begin(), moves.end());
			for(auto move: moves) {
				if (find(unsafe.begin(), unsafe.end(), move) != unsafe.end()){ // if dest an unsafe square
					continue;
				}
				Board copy = b;
				Move currMove{copy, piece, move, colour};
				if (currMove.checkMove()) {
					return make_pair(piece, move);
				}
			}
		}
	}
	for(auto piece: team){ // kill a killer on unsafe square
		Piece *curPiece = b.getSquare(piece.first, piece.second).getPiece();
		if(curPiece == nullptr){
			continue;
		}
		vector<pair<int,int>> captureMoves = curPiece->getCaptureMoves(piece);
		for(auto move: captureMoves){ // search if endangered piece can kill the piece making it endangered
			if (find(killers.begin(), killers.end(), move) == killers.begin()){
				Board copy = b;
				Move check{copy, piece, move, colour};
				if(check.checkMove()){
					return make_pair(piece, move);
				}
			}
		}
	}
	return getL2move(b);
}


movepair AI::getL4move(Board b) {
 movepair res;
 res =  minimaxroot(b, 2, true);
 return res;
}


int AI::evaluate(Board b, Colour currcolour) {
 int boardVal = 0;
	for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				Piece *currPiece = b.getSquare(i, j).getPiece();
				if (currPiece == nullptr) continue;
				if (currPiece->getColour() == currcolour) {
					boardVal += currPiece->getValue();
				} else {
					boardVal -= currPiece->getValue();
				}
			}
		}
	State currState = b.getState();
 	if (currcolour == Colour::Black && currState == State::WhiteCheck)
 		boardVal += 20;
 	else if (currcolour == Colour::White && currState == State::BlackCheck)
 		boardVal += 20;
 	if (currcolour == Colour::Black && currState == State::WhiteCheckmate)
 		boardVal += 200;
 	else if (currcolour == Colour::White && currState == State::BlackCheckmate)
 		boardVal += 200;
 	return boardVal;
}


Board AI::makeMove(Move movehero, Board curBoard, Colour currColour) {
	if(movehero.checkMove()){
		pair<int, int> from = movehero.getFrom();
		pair<int, int> dest = movehero.getDest();
		if (movehero.isEnPassant()) {
				Move *moveE = new EnPassant{curBoard, from, dest, currColour};
				curBoard = moveE->movePiece();
				delete moveE;
		} else if (movehero.isCastle()) {
				Move *moveC = new Castle{curBoard, from, dest, currColour};
				curBoard = moveC->movePiece();
				delete moveC;
		} else if (movehero.isPromotePawn()) {
				char promote;
				if (currColour == Colour::White){
					promote = 'Q';
				}
				else {
					promote = 'q';
				}
				Move *movePP = new PromotePawn{curBoard, from, dest, currColour};
				curBoard = movePP->movePiece(promote);
				delete movePP;
		} else if (movehero.isCapture()) {
				Move *moveEat = new Capture{curBoard, from, dest, currColour};
				curBoard = moveEat->movePiece();
				delete moveEat;
		} else if (movehero.isNormalMove()) {
				Move *moveNormal = new NormalMove{curBoard, from, dest, currColour};
				curBoard = moveNormal->movePiece();
				delete moveNormal;
		}
		return curBoard;
	}
	else{
		return curBoard;
	}
}


movepair AI::minimaxroot(Board b, int depth, bool maximizingPlayer) {
			MoveGen gen{b, colour};
			vector<movepair> legalMoves = gen.getLegalMoves();
		  int bestScore= -9999;
			movepair bestMove = legalMoves[1];
				for (auto move: legalMoves) {
					Board copy = b;
					pair<int, movepair> localMax;
					Move currMove{copy,move.first, move.second, colour};
					Board newBoard= makeMove(currMove, copy, colour); // change to new board
					int currScore = evaluate(newBoard, colour);
					if (currScore > bestScore) {
						bestMove = move;
						bestScore = currScore;
					}
					localMax = minimax(newBoard, depth-1, false,-10000, 10000, bestMove);
					  if (localMax.first > bestScore) {
							bestMove = localMax.second;
							bestScore = localMax.first;
						}
				}
		return bestMove;
}

pair<int, movepair> AI::minimax(Board b, int depth, bool maximizingPlayer, int alpha, int beta, movepair curr) {
		Colour currColour;
		if (maximizingPlayer) {
			currColour = colour;
		} else {
			currColour = enemyColour;
		}

			if (depth == 0) {
				int result = evaluate(b, currColour);
				return make_pair(-result, curr);
			}
					MoveGen gen{b, currColour};
					vector<movepair> legalMoves = gen.getLegalMoves();
			if (maximizingPlayer) { // MAXIMIZING
		    int bestScore= -9999;
				movepair bestMove = curr;

				for (auto move: legalMoves) {
				  Board copy = b;
					pair<int, movepair> localMax;
					Move currMove{copy,move.first, move.second, currColour};
					Board newBoard= makeMove(currMove, copy, currColour); // change to new board
					int currScore = evaluate(newBoard, currColour);
					if (currScore > bestScore) {
						bestMove = move;
						bestScore = currScore;
					}
					localMax = minimax(newBoard, depth-1, false, alpha, beta,bestMove);
					  if (localMax.first > bestScore) {
							bestMove = localMax.second;
							bestScore = localMax.first;
						}
	 				  alpha = max(alpha, bestScore);
						if (beta <= alpha)  return make_pair(bestScore, bestMove);
					}
		     return make_pair(bestScore, bestMove);
			 } else  { // MINIMIZING
	 		  int bestScore= 9999;
				movepair bestMove = curr;
					for (auto move: legalMoves) {
						Board copy = b;
						pair<int, movepair> localMin;
						Move currMove{copy,move.first, move.second, currColour};
						Board newBoard= makeMove(currMove, copy, currColour); // change to new board
						int currScore = evaluate(newBoard, currColour);
						if (currScore > bestScore) {
							bestMove = move;
							bestScore = currScore;
					}
						localMin = minimax(newBoard, depth-1, true, alpha, beta, bestMove);
						if (localMin.first < bestScore) {
								bestMove = curr;
								bestScore = localMin.first;
							}
							beta = min(beta, bestScore);
	  					if (beta <= alpha)  return make_pair(bestScore, bestMove);
						}
					 return make_pair(bestScore, bestMove);
				  }
}


movepair AI::getMove(Board b) {
		if (level == 1) return getL1move(b);
		if (level == 2) return getL2move(b);
	  if (level == 3) return getL3move(b);
    else return getL4move(b);
}
