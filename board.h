#ifndef _BOARD_H_
#define _BOARD_H_
#include "square.h"
#include <utility>
#include <vector>
//#include "move.h"

//class Move;


enum class State {
    WhiteCheck, BlackCheck, Stalemate, Normal, WhiteCheckmate, BlackCheckmate, Illegal
};

class Board {
  int boardSize;
  State boardState;
  std::vector<std::vector<Square>> chessBoard;
  std::pair<int,int> enPassantCoord = std::make_pair(-1,-1);
  std::pair<int,int> latestKillerWhite = std::make_pair(-1,-1);
  std::pair<int,int> latestKillerBlack = std::make_pair(-1,-1);
public:
    State isCheck(const Colour colour);
    State isCheckmate(const Colour colour);
    Board(int boardSize);
    Board(const Board &other);
    Board &operator=(const Board &other);
    Board &operator=(Board &&other);
    bool operator==(const Board &other);
    ~Board();
    Square &getSquare(int row, int col);
    std::pair<int,int> getenPassant();
    void setEnPassant(std::pair<int,int> enPassant);
    State getState();
    bool isValid(); // for controller check if valid board
    int getSize();
    void addPiece(Piece *p, int row, int col);
    void removePiece(int row, int col);
    std::vector<std::pair<int,int>> getPieces(const Colour colour);
    std::pair<int,int> getLatestKiller(Colour c);
    void setLatestKiller(std::pair<int,int> killer, Colour c);
};
#endif
