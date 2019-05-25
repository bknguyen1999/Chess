#ifndef _AI_H
#define _AI_H
#include "player.h"
#include <utility>
#include "board.h"
#include "move.h"
typedef std::pair< std::pair<int, int>, std::pair<int, int>> movepair;
class AI {

	// fields idrk
	Colour colour;
  int level;
	Colour enemyColour;
	int evaluate (Board b, Colour currcolour);
	movepair getL1move(Board b);
	movepair  getL2move(Board b);
	movepair  getL3move(Board b);
	movepair  getL4move(Board b);
	movepair  getL5move(Board b);
	int getpieceval(PieceType type);
	//std::vector<movepair> moveGen(Board b);
	movepair minimaxroot(Board b, int depth, bool maximizingPlayer);
  std::pair<int, movepair> minimax(Board b, int depth, bool maximizingPlayer, int alpha, int beta, movepair curr);
	public:
//	std::pair<int, Board> minimax(Board b, int depth, bool maximizingPlayer, int alpha, int beta);
//	Board getL4move(Board b);
	Board makeMove(Move movehero, Board b, Colour currColour);
	AI(Colour colour, int level);
	bool getIsAI();
	movepair getMove(Board b);
};
#endif
