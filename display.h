#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>
#include "board.h"

class ChessDisplay {
public:
    virtual void printKillMsg(std::string msg) = 0;
    virtual void printKillStreakMsg(std::string msg)=0;
    virtual void printBoard(Board b) = 0;
    virtual void printCODBoard(Board b) = 0;
    virtual void printInfoMsg(std::string msg) = 0;
    virtual void printMsg(std::string msg) = 0;
    virtual ~ChessDisplay();
};

#endif
