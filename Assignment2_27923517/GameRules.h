#ifndef GAMECONTROL_H
#define GAMECONTROL_H
#include "Card.h"
#include "Deck.h"
#include "Player.h"
#include <vector>
#include <string>
class GameRules {
public:
	std::vector<Player> Players;
	void DealCard(int playerIndex);
	bool TradeCard(int SourceIndex, int DestIndex, std::string CardValue);
	void PointCheck(int playerIndex);
	void SevenCardDeal(int playerIndex);
	void Fish(int playerIndex);
	GameRules(int totalPlayer, int humanPlayer);
private:
	Deck Deck;
};
#endif // !GAMECONTROL_H
