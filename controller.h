#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "display.h"
#include "board.h"
#include "move.h"
#include "king.h"
#include "bishop.h"
#include "queen.h"
#include "pawn.h"
#include "knight.h"
#include "rook.h"
#include <string>
#include <iostream>
#include <sstream>
#include "castle.h"
#include "normalmove.h"
#include "capture.h"
#include "enpassant.h"
#include "promotepawn.h"
#include "ai.h"
#include <algorithm>
class Controller {
    ChessDisplay *display;
    Board curBoard;
    std::vector<Player> players;
    std::vector<Board> history;
    int turn = 0;

    int p1Score = 0;
    int p2Score = 0;
    bool firstblood = true;
    bool tacticalNuke = false;
    bool CODchess = false;
    
    void undo(); // doneish
    void normalGame(); // done
    int setupGame(); // done
    void resign(); // done
    bool gameOver(); // done
    int move(); // done
    int start(); // done
    void printScore(); // done
    void insertToBoard(std::string type, std::string pos, Colour colour);
    void removeFromBoard(std::string pos);
    int convertCoords(char c);
    void killMsg(Piece *p, Piece *old);
    Board killStreak(Board b, std::pair<int,int> dest, Piece *p, Piece *old, bool is_ai);
    
public:
    Controller(ChessDisplay *d, int size); // done
    void play();    // done
    ~Controller(); // done
    friend class Move;
};

#endif
