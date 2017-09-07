#ifndef PLAYER_H
#define PLAYER_H
#include "Card.h"
#include <vector>
#include <string>

class Player{
public:
	bool isHuman;
	void Player::addHand(Card newCard);
	void sortHand(void);
	void addPoint(void);
	std::vector<Card> removeHand(std::string Value);
	std::vector<std::string> returnHandValue(void);
	std::vector<std::string> returnHandSuit(void);
	std::string PrettyPrintHand(void);
	Player(bool isHuman);
private:
	std::vector<Card> Hand;
	int PlayerPoint;
};

#endif // !PLAYER_H
