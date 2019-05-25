#include "normalmove.h"
#include <iostream>
using namespace std;

NormalMove::NormalMove(Board board, pair<int,int> from, pair<int,int> dest, Colour colour): Move{board, from, dest, colour}{}

Board NormalMove::movePiece(char promoteTo){
    if(checkMove()){
        int rowFrom = from.first;
        int colFrom = from.second;
        int rowDest = dest.first;
        int colDest = dest.second;
        if(board.getSquare(rowDest,colDest).getPiece() != nullptr){
            throw InvalidMove{};
        }
        Board newBoard = board;
        Square &movingFrom = newBoard.getSquare(rowFrom, colFrom); //tell casey to make getSquare return a reference
        Square &movingTo = newBoard.getSquare(rowDest, colDest);
        Piece *moving = movingFrom.getPiece()->clonePiece();
        if(moving->getType() == PieceType::Pawn){
            if(rowDest == rowFrom + 2){ // black pawn moves 2
                int rowEnPassant = rowDest - 1;
                int colEnPassant = colDest;
                pair<int,int> EPCoord = make_pair(rowEnPassant, colEnPassant);
                newBoard.setEnPassant(EPCoord);
            }
            else if(rowDest == rowFrom - 2){ // white pawn moves 2
                int rowEnPassant = rowDest + 1;
                int colEnPassant = colDest;
                pair<int,int> EPCoord = make_pair(rowEnPassant, colEnPassant);
                newBoard.setEnPassant(EPCoord);
            }
            else{
                newBoard.setEnPassant(make_pair(-1,-1));
            }
        }
        else{
            newBoard.setEnPassant(make_pair(-1,-1));
        }
        // changing the position/consecutive kills of the latestkiller
        pair<int,int> oldLKPos = newBoard.getLatestKiller(colour);
        if(oldLKPos == make_pair(-1,-1)){
            newBoard.setLatestKiller(make_pair(-1,-1), colour); //sets theLatestKiller to nothing
        }
        else{
            int rowOldLK = oldLKPos.first;
            int colOldLK = oldLKPos.second;
            Piece *oldLK = newBoard.getSquare(rowOldLK, colOldLK).getPiece();
            if(oldLK != nullptr){
                oldLK->resetConsecutiveKills();
            }
            newBoard.setLatestKiller(make_pair(-1,-1), colour); //sets theLatestKiller to nothing
        }
        movingFrom.removePiece();
        movingTo.addPiece(moving);
        moving->resetConsecutiveKills();
        moving->setMoved();
        return newBoard;
    }
    else{
        throw InvalidMove{};
    }
}
