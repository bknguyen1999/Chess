#ifndef _MOVEGEN_H
#define _MOVEGEN_H
#include "player.h"
#include <utility>
#include "board.h"
#include "move.h"
typedef std::pair< std::pair<int, int>, std::pair<int, int>> movepair;
class MoveGen {
	Board board;
	Colour colour;
	
	public:
	MoveGen(Board board, Colour colour);
	bool legalMoveLeft();
	std::vector<movepair> getLegalMoves();
};
#endif
