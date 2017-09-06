#ifndef PLAYER_H
#define PLAYER_H
#include "Card.h"
#include <vector>
#include <string>

class Player{
public:
	bool isHuman;
	void addHand(std::vector<Card> newCards);
	void sortHand(void);
	std::vector<Card> removeHand(std::string Value);
	std::vector<std::string> returnHandValue(void);
	std::vector<std::string> returnHandSuit(void);
	Player(bool isHuman);
private:
	std::vector<Card> Hand;
};

#endif // !PLAYER_H
