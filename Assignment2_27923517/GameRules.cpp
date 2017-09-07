#include "GameRules.h"
#include <sstream>

GameRules::GameRules(int totalPlayer, int humanPlayer)
{
	GameRules::Deck.DeckShuffle();//Shuffling the deck
	for (int i = 0; i < humanPlayer; i++)
	{
		GameRules::Players.push_back(Player(true));//adding Human player
	}
	for (int i = 0; i < totalPlayer - humanPlayer; i++)
	{
		GameRules::Players.push_back(Player(false));//adding AI player
	}
	for (int j = 0; j < totalPlayer; j++) 
	{
		GameRules::SevenCardDeal(j);//deals new card
	}
}

void GameRules::SevenCardDeal(int playerIndex)
{
	for (int i = 0; i < 7; i++)
	{
		GameRules::DealCard(playerIndex);
	}
}

void GameRules::DealCard(int playerIndex)
{
	Player dealtPlayer = GameRules::Players[playerIndex];
	dealtPlayer.addHand(GameRules::Deck.PopCard);
}

bool GameRules::TradeCard(int SourceIndex, int DestIndex, std::string CardValue)
{
	bool FishOrNot;
	Player CardSource = GameRules::Players[SourceIndex];
	Player CardDest = GameRules::Players[DestIndex];
	std::vector<Card> TradedCards;
	TradedCards = CardSource.removeHand(CardValue);
	if (TradedCards.empty()) {
		FishOrNot = true;
	}
	else
	{
		for (int i = 0; i < TradedCards.size(); i++)
		{
			CardDest.addHand(TradedCards.back());
			TradedCards.pop_back();
		}
		FishOrNot = false;
	}
	return FishOrNot;
}

void GameRules::PointCheck(int playerIndex)
{

}

void GameRules::Fish(int playerIndex)
{
	Player CardDest = GameRules::Players[playerIndex];
	Card FishedCard = GameRules::Deck.PopCard();
	CardDest.addHand(FishedCard);
}