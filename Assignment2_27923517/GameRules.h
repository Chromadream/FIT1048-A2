#ifndef GAMECONTROL_H
#define GAMECONTROL_H
#include "Card.h"
#include "Deck.h"
#include "Player.h"
#include "OtherFunc.h"
#include <vector>
#include <string>
class GameRules {
public:
	void GameStart(void);
	GameRules(int totalPlayer, int humanPlayer);
private:
	std::vector<Player> Players;
	std::vector<Card> removedCard;
	Deck Deck;
	void CheckPoint(Card currentCard, int playerIndex);
	void DealCard(int playerIndex);
	bool TradeCard(int SourceIndex, int DestIndex, std::string CardValue);
	void SevenCardDeal(int playerIndex);
	void Fish(int playerIndex);
	int playerCheck(int playerIndex);
	void HumanTurn(int playerIndex);
	void PrettyPrintHand(int playerIndex);
	void AITurn(int playerIndex, int currentTurnCount);
	void RandomAI(int playerIndex);
	int exposeCard(int playerIndex, std::string cardToSearch);
	void cheatingAI(int playerIndex);
	void endgame(void);
};
#endif // !GAMECONTROL_H
