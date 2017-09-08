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
	int counter = 0;
	while (removedCardSize < 52)
	{
		for (size_t i = 0; i < GameRules::Players.size(); i++)
		{
			std::cout << "It's player " << i << " turn." << std::endl;
			Player currentPlayer = GameRules::Players[i];
			if (currentPlayer.isHuman == true)
			{
				GameRules::HumanTurn(i);
			}
			else
			{
				//GameRules::AITurn(i,counter);
			}
			removedCardSize = removedCard.size();
			if (removedCardSize == 52) 
			{
				break;
			}
			counter++;
		}
	}
	//GameRules::endgame();
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
	Card dealtCard = GameRules::Deck.PopCard();
	dealtPlayer.addHand(dealtCard);
}

bool GameRules::TradeCard(int SourceIndex, int DestIndex, std::string CardValue)
{
	std::cout << "Player " << DestIndex << " asks " << CardValue << " from player " << SourceIndex << std::endl;
	bool FishOrNot;
	Player CardSource = GameRules::Players[SourceIndex];
	Player CardDest = GameRules::Players[DestIndex];
	std::vector<Card> TradedCards;
	TradedCards = CardSource.removeHand(CardValue);
	if (TradedCards.empty()) {
		std::cout << "The player" << SourceIndex << " doesn't have the card; Fish!" << std::endl;
		FishOrNot = true;
	}
	else
	{
		for (size_t i = 0; i < TradedCards.size(); i++)
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
	std::vector<std::string> playerHands = GameRules::Players[playerIndex].returnHandValue();
	for (size_t i = 0; i < playerHands.size(); i++)
	{
		if (playerHands[i] == cardValue)
		{
			count++;
		}
	}
	if (count == 4)
	{
		for (size_t i = 0; i < playerHands.size(); i++)
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
	GameRules::PrettyPrintHand(playerIndex);
	std::string CardValue;
	std::cout << "Please enter the index of the player to ask for card from: ";
	int targetIndex = playerCheck(playerIndex);
	std::cout << "Please enter the value of the card to ask to: (2-A)";
	CardValue = ValidityCheck();
	bool fish = GameRules::TradeCard(targetIndex, playerIndex, CardValue);
	if (fish == true)
	{
		GameRules::Fish(playerIndex);
	}
}

void GameRules::PrettyPrintHand(int playerIndex)
{
	Player currentPlayer = GameRules::Players[playerIndex];
	std::vector<std::string> HandSuits = currentPlayer.returnHandSuit();
	std::vector<std::string> HandValues = currentPlayer.returnHandValue();
	int size = HandSuits.size();
	for (int i = 0; i < size; i++)
	{
		std::cout << "[" << HandSuits[i] << HandValues[i] << "]";
	}
}
