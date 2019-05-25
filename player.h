#ifndef _PLAYER_H_
#define _PLAYER_H_
enum class Colour { White, Black };
#include "utility"
class Player {
protected:
	Colour colour;
	bool isAI = false;
	int aiLevel;
public:
	Player(Colour colour = Colour::White);
	Player(Colour colour, int level);
	Player& operator=(const Player &rhs);
	Colour getColour();
        bool getIsAI();
	int getAILevel();
//	virtual std::pair< std::pair<int, int>, std::pair<int, int> > getMove(Board b) = 0;
};
#endif

