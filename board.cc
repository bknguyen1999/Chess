#include "board.h"
#include "move.h"
#include <iostream>
#include "movegen.h"
using namespace std;

Board::Board(int boardSize): boardSize{boardSize}, boardState{State::Normal} {
  for (int i = 0; i < boardSize; i++) {
      vector <Square> tiles;
        for (int j = 0; j < boardSize; j++) {
          Square tile{i,j};
          tiles.push_back(tile);
        }
        chessBoard.push_back(tiles);
  }
}

vector<pair<int,int>> Board::getPieces(const Colour colour) {
    vector<pair<int,int>> myPieces;
    for (int i =0; i < boardSize; i++) {
        for (int j=0; j < boardSize; j++) {
            Piece *curr = chessBoard[i][j].getPiece();
						if(curr == nullptr){
							continue;
						}
            if (curr) {
                if(curr->getColour() == colour)
                    myPieces.emplace_back(make_pair(i,j));
            }
        }
    }
    return myPieces;
}

pair<int,int> Board::getenPassant() {
	return enPassantCoord;
}

void Board::setEnPassant(pair<int,int> enPassant){
	this->enPassantCoord = enPassant;
}

pair<int,int> Board::getLatestKiller(Colour c){
	if(c == Colour::White){
		return latestKillerWhite;
	}
	else{
		return latestKillerBlack;
	}
}

void Board::setLatestKiller(pair<int,int> killer, Colour c){
	if(c == Colour::White){
		latestKillerWhite = killer;
	}
	else{
		latestKillerBlack = killer;
	}
}


Board::Board(const Board &other) {
  boardSize = other.boardSize;
  boardState = other.boardState;
	enPassantCoord = other.enPassantCoord;
	latestKillerWhite = other.latestKillerWhite;
	latestKillerBlack = other.latestKillerBlack;
	vector<vector<Square>> newBoard;
	for (int i = 0; i < boardSize; i++) {
		vector<Square> tiles;
		for (int j = 0; j < boardSize; j++) {
			Square tile = other.chessBoard[i][j];
			tiles.push_back(tile);
		}
		newBoard.push_back(tiles);
	}
  chessBoard = newBoard;
}

Board &Board::operator=(const Board &other) {
  if (this == &other) return *this;
  if (this != &other) {
    boardSize = other.boardSize;
    boardState = other.boardState;
      enPassantCoord = other.enPassantCoord;
      latestKillerWhite = other.latestKillerWhite;
      latestKillerBlack = other.latestKillerBlack;
      vector<vector<Square>> newBoard;
    for (int i = 0; i < boardSize; i++) {
			vector<Square> tiles;
		for (int j = 0; j < boardSize; j++) {
			Square tile = other.chessBoard[i][j];
			tiles.push_back(tile);
		}
		newBoard.push_back(tiles);
		}
  	chessBoard = newBoard;
  }
  return *this;
}

Board &Board::operator=(Board &&other){
	swap(boardSize, other.boardSize);
	swap(boardState, other.boardState);
	swap(chessBoard,other.chessBoard);
	swap(enPassantCoord, other.enPassantCoord);
	swap(latestKillerWhite, other.latestKillerWhite);
	swap(latestKillerBlack, other.latestKillerBlack);
	return *this;
}

bool Board::operator==(const Board &other) {
  if (boardSize == other.boardSize &&
  boardState == other.boardState &&
  enPassantCoord == other.enPassantCoord &&
	latestKillerWhite == other.latestKillerWhite &&
	latestKillerBlack == other.latestKillerBlack) {
		for(int i = 0; i < boardSize; i ++){
			for (int j = 0; j <boardSize; j++){
				Piece *p1 = chessBoard[i][j].getPiece();
				Piece *p2 = other.chessBoard[i][j].getPiece();
				if (p1 == nullptr && p2 == nullptr) continue;
				if (p1 == nullptr) return false;
				if (p2 == nullptr) return false;
				if (p1->getType()==p2->getType() && p1->getColour()==p2->getColour() && p1->getKilledCount() == p2->getKilledCount() &&
				p2->getConsecutiveKills() == p1->getConsecutiveKills()) continue;
				return false;
				}
			}
			return true;
	}
   else {
    	return false;
  }
}

State Board::isCheckmate(const Colour colour) {
  MoveGen currBoard{*this, colour};
  bool foundLegal = currBoard.legalMoveLeft();
  if(foundLegal == false) {
     if (colour == Colour::Black) {
         if (isCheck(colour) == State::BlackCheck) {
   	       return State::BlackCheckmate;
         }
         else {
   	       if (isCheck(Colour::White) != State::WhiteCheck) return State::Stalemate;
   	       else return State::WhiteCheck;
         }
       } else {
      if (isCheck(colour) == State::WhiteCheck) {
	       return State::WhiteCheckmate;
      } else {
      	if(isCheck(Colour::Black) != State::BlackCheck) return State::Stalemate;
      	else return State::BlackCheck;
      }
    }
  }
  return isCheck(colour);
}


State Board::getState(){
//  return boardState;
// if either stalemate or checkmate
  State checkMate = isCheckmate(Colour::Black);
  if(checkMate == State::BlackCheckmate || checkMate == State::Stalemate) {
    return checkMate;
  }
  checkMate = isCheckmate(Colour::White);
  if(checkMate == State::WhiteCheckmate || checkMate == State::Stalemate) {
    return checkMate;
}

// either check
  State checkState = isCheck(Colour::White);
  if(checkState == State::WhiteCheck) {
        return checkState;
  }

  checkState = isCheck(Colour::Black);
  if(checkState == State::BlackCheck) {
    return checkState;
  }
  return State::Normal;
}


Square &Board::getSquare (int row, int col) {
  return chessBoard[row][col];
}

bool Board::isValid() {
//	one white one black king
// no pawns on first or last row of the board
// no kings in check
	bool whiteKing = false;
	bool blackKing = false;
	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
	    Piece *curr = chessBoard[i][j].getPiece();
		    if (curr == nullptr) continue;
			  if (curr->getType() == PieceType::King) {
				      if (curr->getColour() == Colour::Black && blackKing == false) {
					           blackKing = true;
			     } else	if (curr->getColour() == Colour::White && whiteKing == false) {
					        whiteKing = true;
			     }	else {
             return false;
      }
		}
	}
}
if (whiteKing == false  || blackKing == false) return false;

	for (int i = 0; i < boardSize; i++) {
    Piece *white = chessBoard[0][i].getPiece();
    Piece *black = chessBoard[7][i].getPiece();
     if (white == nullptr) continue;
     if (black == nullptr) continue;
      if (white->getType() == PieceType::Pawn) return false;
      if (black->getType() == PieceType::Pawn) return false;

	}

 	if (this->getState() != State::WhiteCheck && this->getState() != State::BlackCheck) return true;
	else return false;

}

State Board::isCheck(const Colour colour) {
	pair <int, int> kingpos(-1,-1);
	vector<pair<int, int>> team = getPieces(colour);
	for (auto v: team) {
		Piece *curr = chessBoard[v.first][v.second].getPiece();
		if (curr->getType() == PieceType::King) {
			kingpos = make_pair(v.first, v.second);
		}
	}

	for (int i = 0; i < boardSize; i++) {
		for (int j=0; j < boardSize; j++) {
		 Piece *curr = chessBoard[i][j].getPiece();
			if (curr == nullptr) continue;
			// check if other colour then call move is legal
			if (curr->getColour() != colour) {
			Board copy = *this;
			Move currmove{copy, make_pair(i,j), kingpos, curr->getColour()};
				if (currmove.isValid()) {
	    //  in check
					if (colour == Colour::White) return State::WhiteCheck;
					else return State::BlackCheck;
				} else { //	 correct color but no check
					continue;
				}
			} else{ //		 wrong colour
				continue;
			}
		}
	}
	return State::Normal;
}


void Board::addPiece(Piece *p, int row, int col) {
	chessBoard[row][col].addPiece(p);
}

void Board::removePiece(int row, int col) {
	chessBoard[row][col].removePiece();
}

int Board::getSize() {
	return boardSize;
}

Board::~Board() {}
