#ifndef GRAPHICS
#define GRAPHICS
#include <string>
#include <iostream>
#include "display.h"
#include "window.h"
#include "board.h"
#include "square.h"

class GraphicsDisplay : public ChessDisplay {
    Xwindow w{500,650};
    std::string getPiece(Piece *p);
public:
    void printKillMsg(std::string msg) override;
    void printKillStreakMsg(std::string msg) override;
    void printInfoMsg(std::string msg) override;
    void printBoard(Board board) override;
    void printCODBoard(Board board) override;
    void printMsg(std::string msg) override;
    ~GraphicsDisplay();
};

#endif
