#include "castle.h"
#include <iostream>
#include "normalmove.h"
using namespace std;

Castle::Castle(Board board, pair<int,int> from, pair<int,int> dest, Colour colour): Move{board, from,dest,colour}{}

Board Castle::movePiece(char promoteTo){
    int rowFrom = from.first;
    int colFrom = from.second;
    int rowDest = dest.first;
    int colDest = dest.second;
    if(board.getSquare(rowDest,colDest).getPiece() != nullptr){
        throw InvalidMove{};
    }
    bool legalCastle = true;
    Board temp = board;
    if(colFrom < colDest){
        for(int i = colFrom; i < colDest; i++){
            pair<int,int> cur = make_pair(rowFrom, i);
            pair<int,int> next = make_pair(rowFrom, i+1);
            Move m{temp,cur, next, colour};
            if(m.checkMove() == false){ //castling will result in putting you in check
                legalCastle = false;
                break;
            }
            else{
                Move *makemove = new NormalMove{temp, cur, next, colour};
                temp = makemove->movePiece();
            }
        }
    }
    else{
        for(int i = colFrom; i > colDest; i--){
            pair<int,int> cur = make_pair(rowFrom, i);
            pair<int,int> next = make_pair(rowFrom, i-1);
            Move m{temp, cur, next, colour};
            if(m.checkMove() == false){ //castling will result in putting you in check
                legalCastle = false;
                break;
            }
            else{
                Move *makemove = new NormalMove{temp, cur, next, colour};
                temp = makemove->movePiece();
            }
        }
    }
    if(legalCastle == true){
        Board newBoard = board;
        Square &kingFrom = newBoard.getSquare(rowFrom, colFrom);
        Piece *king = kingFrom.getPiece()->clonePiece();
        if(king->getHasMoved() == true){
            throw InvalidMove{};
        }
        Square &kingDest = newBoard.getSquare(rowDest,colDest);
        Piece *rook;
        // now swap spot of the rook
        if(colDest == colFrom + 2){
            if(king->getColour() == Colour::Black){
                Square &rookDest = newBoard.getSquare(0,5);
                Square &rookFrom = newBoard.getSquare(0,7);
                rook = rookFrom.getPiece()->clonePiece();
                if(rook->getHasMoved()){
                    throw InvalidMove{};
                }
                rookDest.addPiece(rook);
                rookFrom.removePiece();
            }
            else{
                Square &rookDest = newBoard.getSquare(7,5);
                Square &rookFrom = newBoard.getSquare(7,7);
                rook = rookFrom.getPiece()->clonePiece();
                if(rook->getHasMoved()){
                    throw InvalidMove{};
                }
                rookDest.addPiece(rook);
                rookFrom.removePiece();
            }
        }
        else{
            if(king->getColour() == Colour::Black){
                Square &rookDest = newBoard.getSquare(0,3);
                Square &rookFrom = newBoard.getSquare(0,0);
                rook = rookFrom.getPiece()->clonePiece();
                if(rook->getHasMoved()){
                    throw InvalidMove{};
                }
                rookDest.addPiece(rook);
                rookFrom.removePiece();
            }
            else{
                Square &rookDest = newBoard.getSquare(7,3);
                Square &rookFrom = newBoard.getSquare(7,0);
                rook = rookFrom.getPiece()->clonePiece();
                if(rook->getHasMoved()){
                    throw InvalidMove{};
                }
                rookDest.addPiece(rook);
                rookFrom.removePiece();
            }
        }
        kingDest.addPiece(king);
        kingFrom.removePiece(); // swapped spot of king
        king->setMoved();
        rook->setMoved();
        newBoard.setEnPassant(make_pair(-1,-1));

        pair<int,int> oldLKPos = newBoard.getLatestKiller(colour);
        if(oldLKPos == make_pair(-1,-1)){
            return newBoard;
        }
        int rowOldLK = oldLKPos.first;
        int colOldLK = oldLKPos.second;
        Piece *oldLK = newBoard.getSquare(rowOldLK, colOldLK).getPiece();
        if(oldLK != nullptr){
            oldLK->resetConsecutiveKills();
        }
        newBoard.setLatestKiller(make_pair(-1,-1), colour); //sets theLatestKiller to nothing
        king->resetConsecutiveKills();
        rook->resetConsecutiveKills();
        return newBoard;
    }
    throw InvalidMove{};
}
