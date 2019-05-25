#include "capture.h"
#include <iostream>
using namespace std;
Capture::Capture(Board board, pair<int,int> from, pair<int,int> dest, Colour colour): Move{board, from, dest, colour}{}

Board Capture::movePiece(char promoteTo){
    if(checkMove()){
        int rowFrom = from.first;
        int colFrom = from.second;
        int rowDest = dest.first;
        int colDest = dest.second;
        if(board.getSquare(rowDest,colDest).getPiece() == nullptr){
            throw InvalidMove{};
        }
        Board newBoard = board;
        Square &movingFrom = newBoard.getSquare(rowFrom, colFrom);
        Piece *moving = movingFrom.getPiece()->clonePiece();
        Square &movingTo = newBoard.getSquare(rowDest, colDest);
        newBoard.setEnPassant(make_pair(-1,-1));

        pair<int,int> latestKillerOldPos = movingFrom.getPos();
        pair<int,int> latestKillerNewPos = movingTo.getPos();
        pair<int,int> oldLKPos = newBoard.getLatestKiller(colour);
        if(latestKillerOldPos == oldLKPos){ // piece that captured other piece was the latest killer or there was no latest killer
            newBoard.setLatestKiller(latestKillerNewPos, colour);
            moving->incConsecutiveKills();
            moving->incKillCount();
        }
        else{ // piece that captured was not the latest killer
            int rowOldLK = oldLKPos.first;
            int colOldLK = oldLKPos.second;
            if(oldLKPos != make_pair(-1, -1)){
                Piece *oldLK = newBoard.getSquare(rowOldLK, colOldLK).getPiece();
                if(oldLK != nullptr){
                    oldLK->resetConsecutiveKills();
                }
            }
            newBoard.setLatestKiller(latestKillerNewPos, colour);
            moving->incKillCount();
            moving->incConsecutiveKills();
        }
        if(movingTo.getPiece()){
            movingTo.removePiece();
        }
        movingFrom.removePiece();
        movingTo.addPiece(moving);
        moving->setMoved();
        return newBoard;
    }
    else{
        throw InvalidMove{};
    }
}
