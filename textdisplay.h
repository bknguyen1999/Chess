#ifndef TXTDISP_H
#define TXTDISP_H

#include <iostream>
#include "display.h"

class TextDisplay : public ChessDisplay {
    void printSquare(Square sqr, std::pair<int, int> pos);
    void printPiece(Piece *p);
public:
    TextDisplay();
    void printCODBoard(Board b) override;
    void printKillMsg(std::string msg) override;
    void printInfoMsg(std::string msg) override;
    void printBoard(Board b) override;
    void printMsg(std::string msg) override;
    void printKillStreakMsg(std::string msg) override;
    ~TextDisplay() override;
};

#endif
