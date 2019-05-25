#include "player.h"
using namespace std;
Player::Player(Colour colour): colour{colour} {
}

Player::Player(Colour colour, int level): colour{colour}, aiLevel{level} {
	isAI = true;
}

Colour Player::getColour() {
  return colour;
}

bool Player::getIsAI() {
  return isAI;
}

int Player::getAILevel() {
  return aiLevel;
}

Player &Player::operator=(const Player &rhs) {
    colour = rhs.colour;
    aiLevel = rhs.aiLevel;
    isAI = rhs.isAI;
    return *this;
}

/*
pair<pair<int, int>, pair<int, int>> getMove(Board &b) {
	return make_pair(make_pair(-1,-1), make_pair(-1,-1));
}*/
