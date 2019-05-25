#include "promotepawn.h"
#include "capture.h"
#include <iostream>
#include "queen.h"
#include "piece.h"
#include "rook.h"
#include "bishop.h"
#include "knight.h"
using namespace std;

PromotePawn::PromotePawn(Board board, pair<int,int> from, pair<int,int> dest, Colour colour): Move{board, from,dest,colour}{}

Board PromotePawn::movePiece(char promoteTo){
    if(checkMove()){
        int rowFrom = from.first;
        int colFrom = from.second;
        int rowDest = dest.first;
        int colDest = dest.second;
        Board newBoard = board;
        Piece *promote = nullptr;
        if(promoteTo == 'Q' || promoteTo == 'q'){
            promote = new Queen{colour};
        }
        else if(promoteTo == 'R' || promoteTo == 'r'){
            promote = new Rook{colour};
        }
        else if(promoteTo == 'B' || promoteTo == 'b'){
            promote = new Bishop{colour};
        }
        else if(promoteTo == 'N' || promoteTo == 'n'){
            promote = new Knight{colour};
        }
        else{
            throw InvalidMove();
        }
        Square &fromSqr = newBoard.getSquare(rowFrom,colFrom);
        Square &destSqr = newBoard.getSquare(rowDest,colDest);
        Piece *moving = fromSqr.getPiece();
        promote->setKillCount(moving->getKilledCount());
        promote->setConsecutiveKills(moving->getConsecutiveKills());
        pair<int,int> oldLKPos = newBoard.getLatestKiller(colour);
        pair<int,int> latestKillerOldPos = fromSqr.getPos();
        pair<int,int> latestKillerNewPos = destSqr.getPos();
        if(destSqr.getPiece() != nullptr){
            destSqr.removePiece();
            if(latestKillerOldPos == oldLKPos){ //the latest killer is the same piece making the kill
                newBoard.setLatestKiller(latestKillerNewPos, colour);
                promote->incConsecutiveKills();
                promote->incKillCount();
            }
            else{ // kills something but the killer wasnt the latest killer

                int rowOldLK = oldLKPos.first;
                int colOldLK = oldLKPos.second;
                if(oldLKPos != make_pair(-1,-1)){
                    Piece *oldLK = newBoard.getSquare(rowOldLK, colOldLK).getPiece();
                    if(oldLK != nullptr){
                        oldLK->resetConsecutiveKills();
                    }
                }
                newBoard.setLatestKiller(latestKillerNewPos, colour);
                promote->incConsecutiveKills();
                promote->incKillCount();
            }
        }
        else{
            if(oldLKPos != make_pair(-1,-1)){
                int rowOldLK = oldLKPos.first;
                int colOldLK = oldLKPos.second;
                Piece *oldLK = newBoard.getSquare(rowOldLK, colOldLK).getPiece();
                if(oldLK != nullptr){
                    oldLK->resetConsecutiveKills();
                }
            }
            newBoard.setLatestKiller(make_pair(-1,-1), colour); //sets theLatestKiller to nothing
            promote->resetConsecutiveKills();
        }
        fromSqr.removePiece();
        destSqr.addPiece(promote);
        promote->setMoved();
        newBoard.setEnPassant(make_pair(-1,-1));
        return newBoard;
    }
    else{
        throw InvalidMove{};
    }
}
