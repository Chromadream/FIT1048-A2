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
	int counter = 1;
	while (removedCardSize < 52)
	{
		for (size_t i = 0; i < GameRules::Players.size(); i++)
		{
			std::cout << "It's Player " << i << "'s turn. Current turn count is: " << counter << std::endl;
			if (GameRules::Players[i].isHuman == true)
			{
				GameRules::HumanTurn(i);
			}
			else
			{
				GameRules::AITurn(i, counter);
			}
			removedCardSize = removedCard.size();
			if (removedCardSize == 52)
			{
				break;
			}
			std::cout << "\n\n";
		};
		counter++;
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
	Card dealtCard = GameRules::Deck.PopCard();
	GameRules::Players[playerIndex].addHand(dealtCard);
}

bool GameRules::TradeCard(int SourceIndex, int DestIndex, std::string CardValue)
{
	std::cout << "Player " << DestIndex << " asks " << CardValue << " from player " << SourceIndex << std::endl;
	bool FishOrNot;
	std::vector<Card> TradedCards;
	TradedCards = GameRules::Players[SourceIndex].removeHand(CardValue);
	if (TradedCards.empty()) {
		std::cout << "Player" << SourceIndex << " doesn't have the card. Fish!" << std::endl;
		FishOrNot = true;
	}
	else
	{
		for (size_t i = 0; i < TradedCards.size(); i++)
		{
			GameRules::Players[DestIndex].addHand(TradedCards.back());
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
		std::vector<Card> removingCard = GameRules::Players[playerIndex].removeHand(cardValue);
		for (size_t i = 0; i < playerHands.size(); i++)
		{
			Card currentCard = removingCard.back();
			GameRules::removedCard.push_back(currentCard);
			removingCard.pop_back();
		}
		GameRules::Players[playerIndex].addPoint();
	}
}

void GameRules::Fish(int playerIndex)
{
	Card FishedCard = GameRules::Deck.PopCard();
	GameRules::Players[playerIndex].addHand(FishedCard);
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
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			std::cout << "The index input is invalid. Please try with other number: ";
		}
		else
		{
			if (userinput >= 0 && userinput < PlayerSize && userinput != playerIndex)
			{
				validity = true;
			}
			else
			{
				std::cout << "The index input is invalid. Please try with other number: ";
			}
		}
	}
	return userinput;
}


void GameRules::HumanTurn(int playerIndex)
{
	GameRules::PrettyPrintHand(playerIndex);
	std::string CardValue;
	int targetIndex;
	if (GameRules::Players.size() > 2)
	{
		std::cout << "Please enter the index of the player to ask for card from: ";
		targetIndex = playerCheck(playerIndex);
	}
	else
	{
		if (playerIndex == 0)
		{
			targetIndex = 1;
		}
		else
		{
			targetIndex = 0;
		}
	}
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
	std::vector<std::string> HandSuits = GameRules::Players[playerIndex].returnHandSuit();
	std::vector<std::string> HandValues = GameRules::Players[playerIndex].returnHandValue();
	int size = HandSuits.size();
	for (int i = 0; i < size; i++)
	{
		std::cout << "[" << HandValues[i] <<" "<< HandSuits[i] << "]";
		if (i == 12)
		{
			std::cout << std::endl;
		}
	}
	std::cout << "\n";
}

void GameRules::AITurn(int playerIndex, int currentTurnCount)
{
	if (currentTurnCount < 5)
	{
		RandomAI(playerIndex);
	}
	else
	{
		cheatingAI(playerIndex);
	}
}

void GameRules::RandomAI(int playerIndex)
{
	bool notItself = false;
	int targetIndex;
	while (notItself == false)
	{
		targetIndex = rand() % GameRules::Players.size();
		if (targetIndex != playerIndex)
		{
			notItself = true;
		}
	}
	std::string CardValue;
	int handSize = GameRules::Players[playerIndex].Hand.size();
	CardValue = GameRules::Players[playerIndex].Hand[rand() % handSize].getValue();
	bool fish = GameRules::TradeCard(targetIndex, playerIndex, CardValue);
	if (fish == true)
	{
		GameRules::Fish(playerIndex);
	}
}

int GameRules::exposeCard(int playerIndex, std::string cardToSearch)
{
	int playerSize = GameRules::Players.size();
	int targetIndex = NULL;
	bool notItself = false;
	std::vector<std::string> currentHandValue;
	for (int i = 0; i < playerSize; i++)
	{
		if (i != playerIndex)
		{
			currentHandValue = GameRules::Players[i].returnHandSuit();
			if (std::find(currentHandValue.begin(), currentHandValue.end(), cardToSearch) != currentHandValue.end())
			{
				targetIndex = i;
				break;
			}
		}
	}
	if (targetIndex == NULL)
	{
		while (notItself == false)
		{
			targetIndex = rand() % GameRules::Players.size();
			if (targetIndex != playerIndex)
			{
				notItself = true;
			}
		}
	}
	return targetIndex;
}

void GameRules::cheatingAI(int playerIndex)
{
	int targetIndex;
	int handSize = GameRules::Players[playerIndex].Hand.size();
	std::string CardValue = GameRules::Players[playerIndex].Hand[rand() % handSize].getValue();
	targetIndex = GameRules::exposeCard(playerIndex, CardValue);
	bool fish = GameRules::TradeCard(targetIndex, playerIndex, CardValue);
	if (fish == true)
	{
		GameRules::Fish(playerIndex);
	}
}

void GameRules::endgame(void)
{

}
