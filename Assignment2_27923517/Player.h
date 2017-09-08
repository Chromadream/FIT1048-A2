#ifndef PLAYER_H
#define PLAYER_H
#include "Card.h"
#include <vector>
#include <string>

class Player{
public:
	bool isHuman;
	std::vector<Card> Hand;
	void Player::addHand(Card newCard);
	void addPoint(void);
	std::vector<Card> removeHand(std::string Value);
	std::vector<std::string> returnHandValue(void);
	std::vector<std::string> returnHandSuit(void);
	Player(bool isHuman);
private:
	
	int PlayerPoint;
};

#endif // !PLAYER_H
