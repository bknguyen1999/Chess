#include "enpassant.h"
#include <iostream>
using namespace std;

EnPassant::EnPassant(Board board, std::pair<int,int> from, std::pair<int,int> dest, Colour colour): Move{board, from,dest,colour}{}

Board EnPassant::movePiece(char promoteTo){
    if(checkMove()){
        int rowFrom = from.first;
        int colFrom = from.second;
        int rowDest = dest.first;
        int colDest = dest.second;
        if(board.getSquare(rowDest,colDest).getPiece() != nullptr){
            throw InvalidMove{};
        }
        Board newBoard = board;
        Square &fromSqr = newBoard.getSquare(rowFrom,colFrom);
        Square &destSqr = newBoard.getSquare(rowDest, colDest);
        Piece *killer = fromSqr.getPiece()->clonePiece();
        if(newBoard.getenPassant() == make_pair(-1,-1)){
            throw InvalidMove{};
        }
        pair<int,int> EPCoord = newBoard.getenPassant();
        int rowEP = EPCoord.first;
        int colEP = EPCoord.second;
        Square &EPSqr = newBoard.getSquare(rowEP, colEP);
        if(destSqr == EPSqr && killer->getType() == PieceType::Pawn){
            if(colour == Colour::Black){
                int rowKilled = rowDest - 1;
                int colKilled = colDest;
                Square &killedSqr = newBoard.getSquare(rowKilled, colKilled);
                killedSqr.removePiece();
            }
            else{
                int rowKilled = rowDest + 1;
                int colKilled = colDest;
                Square &killedSqr = newBoard.getSquare(rowKilled,colKilled);
                killedSqr.removePiece();
            }
            destSqr.addPiece(killer);
            fromSqr.removePiece();
            killer->setMoved();
            newBoard.setEnPassant(make_pair(-1,-1));

            pair<int,int> latestKillerOldPos = fromSqr.getPos();
            pair<int,int> latestKillerNewPos = destSqr.getPos();
            pair<int,int> oldLKPos = newBoard.getLatestKiller(colour);
            if(latestKillerOldPos == oldLKPos){ // piece that captured other piece was the latest killer or there was no latest killer
                newBoard.setLatestKiller(latestKillerNewPos, colour);
                killer->incConsecutiveKills();
                killer->incKillCount();
            }
            else{ // piece that captured was not the latest killer
                int rowOldLK = oldLKPos.first;
                int colOldLK = oldLKPos.second;
                if(oldLKPos != make_pair(-1,-1)){
                    Piece *oldLK = newBoard.getSquare(rowOldLK, colOldLK).getPiece();
                    oldLK->resetConsecutiveKills();
                }
                newBoard.setLatestKiller(latestKillerNewPos, colour);
                killer->incKillCount();
                killer->incConsecutiveKills();
        }
            return newBoard;
        }
        else{
            throw InvalidMove{};
        }
    }
    throw InvalidMove{};
}
