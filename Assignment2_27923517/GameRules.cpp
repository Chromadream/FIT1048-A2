#include "GameRules.h"
#include <iostream>

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

void GameRules::GameStart(void)
{
	int removedCardSize = removedCard.size();
	while (removedCardSize < 52)
	{
		for (int i = 0; i < GameRules::Players.size; i++)
		{
			std::cout << "It's player " << i << " turn." << std::endl;
			Player currentPlayer = GameRules::Players[i];
			if (currentPlayer.isHuman == true)
			{
				GameRules::HumanTurn(i);
			}
			else
			{
				GameRules::AITurn(i);
			}
			removedCardSize = removedCard.size();
			if (removedCardSize == 52) 
			{
				break;
			}
		}
	}
	GameRules::endgame();
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
			GameRules::CheckPoint(TradedCards.back(), DestIndex);
			TradedCards.pop_back();
		}
		FishOrNot = false;
	}
	return FishOrNot;
}

void GameRules::CheckPoint(Card currentCard, int playerIndex)
{
	std::string cardValue = currentCard.getValue();
	int count = 0;
	std::vector<std::string> playerHands = GameRules::Players[playerIndex].returnHandValue;
	for (int i = 0; i < playerHands.size; i++)
	{
		if (playerHands[i] == cardValue)
		{
			count++;
		}
	}
	if (count == 4)
	{
		for (int i = 0; i < playerHands.size; i++)
		{
			if (playerHands[i] == cardValue)
			{
				GameRules::removedCard.push_back(currentCard);
			}
		}
		GameRules::Players[playerIndex].addPoint();
	}
}

void GameRules::Fish(int playerIndex)
{
	Player CardDest = GameRules::Players[playerIndex];
	Card FishedCard = GameRules::Deck.PopCard();
	CardDest.addHand(FishedCard);
	GameRules::CheckPoint(FishedCard, playerIndex);
}

int GameRules::playerCheck(int playerIndex)
{
	int PlayerSize = GameRules::Players.size();
	int userinput;
	bool validity = false;
	while (!validity)
	{
		std::cin >> userinput;
		if (userinput >= 0 && userinput < PlayerSize && userinput != playerIndex)
		{
			validity = true;
		}
		else
		{
			std::cout << "The index input is invalid. Please try with other number: ";
		}
	}
	return userinput;
}


void GameRules::HumanTurn(int playerIndex)
{
	std::cout << GameRules::Players[playerIndex].PrettyPrintHand << std::endl;
	int targetIndex = playerCheck(playerIndex);
	std::string CardValue;
}