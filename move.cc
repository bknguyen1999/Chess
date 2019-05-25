#include "move.h"
#include <iostream>
using namespace std;

Move::Move(Board board, pair<int,int> from, pair<int,int> dest, Colour colour): board{board}, from{from}, dest{dest}, colour{colour}{}

pair<int,int> Move::getFrom(){
    return from;
}


pair<int,int> Move::getDest(){
    return dest;
}


bool Move::isInBoard(pair<int,int> pos){
    if(pos.first >= 0 && pos.first <= 7 && pos.second >= 0 && pos.second <= 7){
        return true;
    }
    return false;
}

bool Move::isValid(){
    int rowFrom = from.first;
    int colFrom = from.second;
    int rowDest = dest.first;
    int colDest = dest.second;
    if(!isInBoard(dest) || !isInBoard(from)){
        return false;
    }
    if(board.getSquare(rowFrom,colFrom).getPiece() == nullptr){
        return false;
    }
    if(dest == from){
        return false;
    }
    Piece *piece = board.getSquare(rowFrom, colFrom).getPiece();
    if(piece->getColour() != colour){
        return false;
    }
    Square &destSqr = board.getSquare(rowDest, colDest);
    if(piece->getType() == PieceType::King && (colDest == colFrom + 2 || colDest == colFrom - 2)){ //checks for invalid castle
        Piece *rook;
        if(colour == Colour::Black){
            if(colDest == colFrom + 2){
                rook = board.getSquare(0,7).getPiece();
            }
            else{
                rook = board.getSquare(0, 0).getPiece();
            }
        }
        else{
            if(colDest == colFrom + 2){
                rook = board.getSquare(7,7).getPiece();
            }
            else{
                rook = board.getSquare(7, 0).getPiece();
            }
        }
        if(rook == nullptr) return false;
        if(rook->getHasMoved()){
            return false;
        }
    }
    if(isPathClear()){
        if(destSqr.getPiece() && (destSqr.getPiece()->getColour() != colour)){
            vector<pair<int,int>> possibleCaptureMoves = piece->getCaptureMoves(from);
            for(auto i: possibleCaptureMoves){
                if (i == dest){
                    return true;
                }
            }
            return false;
        }
        else if(destSqr.getPiece()){
            return false;
        }
        else{
            if(piece->getType() == PieceType::Pawn && destSqr.getPos() == board.getenPassant()){ // enpassant move
                vector<pair<int,int>> possibleMoves = piece->getCaptureMoves(from);
                for(auto i: possibleMoves){
                    if (i == dest){
                        return true;
                    }
                }
                return false;
            }
            else{
                if(piece->getType() == PieceType::Pawn){
                    vector<pair<int,int>> captureMoves = piece->getCaptureMoves(from);
                    vector<pair<int,int>> possibleMoves = piece->getMoves(from);
                    for(auto i:captureMoves){
                        if (i == dest){
                            return true;
                        }
                    }
                    for(auto i : possibleMoves){
                        if (i == dest){
                            return true;
                        }
                    }
                    return false;
                }
                else{
                    vector<pair<int,int>> possibleMoves = piece->getMoves(from);
                    for(auto i: possibleMoves){
                        if (i == dest){
                            return true;
                        }
                    }
                    return false;
                }
            }
        }
    }
    else{
        return false;
    }
}


bool Move::checkMove(){ //returns true if the move doesn't put you in check, false otherwise
    if(isValid()){
        int rowFrom = from.first;
        int colFrom = from.second;
        int rowDest = dest.first;
        int colDest = dest.second;
        Board newBoard = board;
        Square &fromSquare = newBoard.getSquare(rowFrom, colFrom);
        Square &destSquare = newBoard.getSquare(rowDest, colDest);
        Piece *piece = fromSquare.getPiece()->clonePiece();
        if(destSquare.getPiece()){
            destSquare.removePiece();
        }
        destSquare.addPiece(piece);
        fromSquare.removePiece();
        if(colour == Colour::Black){
            if(newBoard.isCheck(colour) == State::BlackCheck){
                return false;
            }
            else{
                return true;
            }
        }
        else{
            if(newBoard.isCheck(colour) == State::WhiteCheck){
                return false;
            }
            else{
                return true;
            }
        }
    }
    else{
        return false;
    }
}


bool Move::isPathClear(){
    int rowFrom = from.first;
    int colFrom = from.second;
    if(board.getSquare(rowFrom,colFrom).getPiece() == nullptr){
        return false;
    }
    Square &s = board.getSquare(rowFrom, colFrom);
    Piece *p = s.getPiece();
    int rowDest = dest.first;
    int colDest = dest.second;
    if (p->getType() == PieceType::Knight){
        return true;
    }
    if(rowFrom > rowDest && colFrom == colDest){ //moving up
        for(int i = rowFrom - 1; i > rowDest; i--){
            Square &check = board.getSquare(i, colFrom);
            if(check.getPiece()){
                return false;
            }
        }
        return true;
    }
    else if (rowFrom < rowDest && colFrom == colDest){ //moving down
        for(int i = rowFrom + 1; i < rowDest; i++){
            Square &check = board.getSquare(i, colFrom);
            if(check.getPiece()){
                return false;
            }
        }
        return true;
    }
    else if (colFrom > colDest && rowFrom == rowDest){ // moving left
        for(int i = colFrom - 1; i > colDest; i--){
            Square &check = board.getSquare(rowFrom, i);
            if(check.getPiece()){
                return false;
            }
        }
        return true;
    }
    else if (colFrom < colDest && rowFrom == rowDest){ // moving right
        for(int i = colFrom + 1; i < colDest; i++){
            Square &check = board.getSquare(rowFrom, i);
            if(check.getPiece()){
                return false;
            }
        }
        return true;
    }
    else if (rowFrom > rowDest && colFrom < colDest){ // moving up-right
        for(int i = rowFrom - 1, j = colFrom + 1; i > rowDest && j < colDest; i--, j++){
            Square &check = board.getSquare(i, j);
            if(check.getPiece()){
                return false;
            }
        }
        return true;
    }
    else if (rowFrom > rowDest && colFrom > colDest){ // moving up-left
        for(int i = rowFrom - 1, j = colFrom - 1; i > rowDest && j > colDest; i--, j--){
            Square &check = board.getSquare(i, j);
            if(check.getPiece()){
                return false;
            }
        }
        return true;
    }
    else if (rowFrom < rowDest && colFrom < colDest){ // moving down-right
        for(int i = rowFrom + 1, j = colFrom + 1; i < rowDest && j < colDest; i++, j++){
            Square &check = board.getSquare(i, j);
            if(check.getPiece()){
                return false;
            }
        }
        return true;
    }
    else if (rowFrom < rowDest && colFrom > colDest){ // moving down-left
        for(int i = rowFrom + 1, j = colFrom - 1; i < rowDest && j > colDest; i++, j--){
            Square &check = board.getSquare(i, j);
            if(check.getPiece()){
                return false;
            }
        }
        return true;
    }
    else {
      return true;
    }
}


bool Move::isCastle(){ //identifies if the move is a castle
  if(!isInBoard(dest) || !isInBoard(from)){
      return false;
  }
    int rowFrom = from.first;
    int colFrom = from.second;
    int rowDest = dest.first;
    int colDest = dest.second;
    Square &fromSqr = board.getSquare(rowFrom, colFrom); // square the king is on
    Piece *piece = fromSqr.getPiece(); // should be king
    if(piece == nullptr){
        return false;
    }
    if(piece->getType() == PieceType::King && rowFrom == rowDest &&
    (colDest == colFrom + 2 || colDest == colFrom - 2) && isPathClear()){
        Piece *rook;
        if(piece->getHasMoved() == false){
            if(colDest == colFrom + 2){
                if(piece->getColour() == Colour::Black){
                    rook = board.getSquare(0,7).getPiece();
                }
                else{
                    rook = board.getSquare(7,7).getPiece();
                }
            }
            else{
                if(piece->getColour() == Colour::Black){
                    rook = board.getSquare(0,0).getPiece();
                }
                else{
                    rook = board.getSquare(7,0).getPiece();
                }
            }
            if(rook && rook->getType() == PieceType::Rook && rook->getHasMoved() == false){
                return true;
            }
        }
    }
    return false;
}

bool Move::isEnPassant(){
  if(!isInBoard(dest) || !isInBoard(from)){
      return false;
  }
    if(board.getenPassant() == make_pair(-1,-1)){
        return false;
    }

    int rowFrom = from.first;
    int colFrom = from.second;
    int rowDest = dest.first;
    int colDest = dest.second;
    Square &fromSqr = board.getSquare(rowFrom, colFrom);
    Square &destSqr = board.getSquare(rowDest, colDest);
    if(fromSqr.getPiece() == nullptr){
        return false;
    }
    if(destSqr.getPiece() != nullptr){
        return false;
    }
    pair<int,int> EPCoord = board.getenPassant();
    if(EPCoord == make_pair(-1,-1)){
        return false;
    }
    int rowEP = EPCoord.first;
    int colEP = EPCoord.second;
    Square EPSqr = board.getSquare(rowEP, colEP);
    Piece *killer = fromSqr.getPiece();
    if(killer == nullptr){
        return false;
    }
    Piece *check = destSqr.getPiece();
    if(check != nullptr){
        return false;
    }
    Piece *killed;
    if (killer->getType() != PieceType::Pawn) return false;
    if(colour == Colour::Black){
        int rowKilled = rowDest - 1;
        int colKilled = colDest;
        Square &killedSqr = board.getSquare(rowKilled, colKilled);
        killed = killedSqr.getPiece();
    }
    else{
        int rowKilled = rowDest + 1;
        int colKilled = colDest;
        Square &killedSqr = board.getSquare(rowKilled, colKilled);
        killed = killedSqr.getPiece();
    }
    if(killed == nullptr){
        return false;
    }
    if(destSqr == EPSqr && killer->getType() == PieceType::Pawn
    && killed->getType() == PieceType::Pawn){
        return true;
    }
    else{
        return false;
    }
}

bool Move::isCapture(){
  if(!isInBoard(dest) || !isInBoard(from)){
      return false;
  }
    int rowDest = dest.first;
    int colDest = dest.second;
    Square &destSqr = board.getSquare(rowDest,colDest);
    Piece *killed = destSqr.getPiece();
    if(killed && killed->getColour() != colour){
        return true;
    }
    return false;
}

bool Move::isPromotePawn(){ //if pawn kills another piece to get to the end, it will be a promotepawn
  if(!isInBoard(dest) || !isInBoard(from)){
      return false;
  }
    int rowFrom = from.first;
    int colFrom = from.second;
    int rowDest = dest.first;
  //  int colDest = dest.second;
    Piece *moving = board.getSquare(rowFrom, colFrom).getPiece();
    if(moving == nullptr){
        return false;
    }
    if(moving->getType() == PieceType::Pawn){
        if(colour == Colour::Black && rowDest == 7){
            return true;
        }
        else if (colour == Colour::White && rowDest == 0){
            return true;
        }
        else{
            return false;
        }
    }
    return false;
}


bool Move::isNormalMove(){
  if(!isInBoard(dest) || !isInBoard(from)){
      return false;
  }
    return (!isCastle() && !isEnPassant() && !isCapture() && !isPromotePawn());
}

Board Move::movePiece(char promoteTo) {
   return board;
}

Move::~Move(){}
