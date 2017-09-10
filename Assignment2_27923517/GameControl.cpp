#include "GameControl.h"
#include <iostream>

GameControl::GameControl(int totalPlayer, int humanPlayer)
{
	GameControl::removedCardCount = 0;
	GameControl::Deck.DeckShuffle();//Shuffling the deck
	for (int i = 0; i < humanPlayer; i++)
	{
		GameControl::Players.push_back(Player(true));//adding Human player
	}
	for (int i = 0; i < totalPlayer - humanPlayer; i++)
	{
		GameControl::Players.push_back(Player(false));//adding AI player
	}
	for (int j = 0; j < totalPlayer; j++) 
	{
		GameControl::SevenCardDeal(j);//deals new card
	}
}

void GameControl::GameStart(void)
{
	int counter = 1;
	while (GameControl::removedCardCount < 52)
	{
		for (size_t i = 0; i < GameControl::Players.size(); i++)
		{
			std::cout << "It's Player " << i << "'s turn. Current turn count is: " << counter << std::endl;
			if (GameControl::Players[i].Hand.size() == 0)
			{
				GameControl::emptyHand(i);
			}
			if (GameControl::Players[i].isHuman == true)
			{
				GameControl::HumanTurn(i);
			}
			else
			{
				GameControl::AITurn(i, counter);
			}
			if (GameControl::removedCardCount == 52)
			{
				break;
			}
			std::cout << "\n\n";
		};
		counter++;
	}
	GameControl::endgame();
}

void GameControl::SevenCardDeal(int playerIndex)
{
	for (int i = 0; i < 7; i++)
	{
		GameControl::DealCard(playerIndex);
	}
}

void GameControl::DealCard(int playerIndex)
{
	Card dealtCard = GameControl::Deck.PopCard();
	GameControl::Players[playerIndex].addHand(dealtCard);
}

bool GameControl::TradeCard(int SourceIndex, int DestIndex, std::string CardValue)
{
	std::cout << "Player " << DestIndex << " asks " << CardValue << " from player " << SourceIndex << std::endl;
	bool FishOrNot;
	std::vector<Card> TradedCards;
	TradedCards = GameControl::Players[SourceIndex].removeHand(CardValue);
	if (TradedCards.empty()) {
		std::cout << "Player" << SourceIndex << " doesn't have the card. Fish!" << std::endl;
		FishOrNot = true;
	}
	else
	{
		for (size_t i = 0; i < TradedCards.size(); i++)
		{
			GameControl::Players[DestIndex].addHand(TradedCards.back());
			GameControl::CheckPoint(TradedCards.back(), DestIndex);
			TradedCards.pop_back();
		}
		FishOrNot = false;
	}
	return FishOrNot;
}

void GameControl::CheckPoint(Card currentCard, int playerIndex)
{
	std::string cardValue = currentCard.getValue();
	int count = 0;
	std::vector<std::string> playerHands = GameControl::Players[playerIndex].returnHandValue();
	for (size_t i = 0; i < playerHands.size(); i++)
	{
		if (playerHands[i] == cardValue)
		{
			count++;
		}
	}
	if (count == 4)
	{
		std::vector<Card> removingCard = GameControl::Players[playerIndex].removeHand(cardValue);
		removedCardCount += 4;
		GameControl::Players[playerIndex].addPoint();
	}
}

void GameControl::Fish(int playerIndex)
{
	Card FishedCard = GameControl::Deck.PopCard();
	GameControl::Players[playerIndex].addHand(FishedCard);
	GameControl::CheckPoint(FishedCard, playerIndex);
}

int GameControl::playerCheck(int playerIndex)
{
	int PlayerSize = GameControl::Players.size();
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


void GameControl::HumanTurn(int playerIndex)
{
	GameControl::PrettyPrintHand(playerIndex);
	std::string CardValue;
	int targetIndex;
	if (GameControl::Players.size() > 2)
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
	bool fish = GameControl::TradeCard(targetIndex, playerIndex, CardValue);
	if (fish == true)
	{
		GameControl::Fish(playerIndex);
	}
}


void GameControl::PrettyPrintHand(int playerIndex)
{
	std::vector<std::string> HandSuits = GameControl::Players[playerIndex].returnHandSuit();
	std::vector<std::string> HandValues = GameControl::Players[playerIndex].returnHandValue();
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

void GameControl::AITurn(int playerIndex, int currentTurnCount)
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

void GameControl::RandomAI(int playerIndex)
{
	bool notItself = false;
	int targetIndex;
	while (notItself == false)
	{
		targetIndex = rand() % GameControl::Players.size();
		if (targetIndex != playerIndex)
		{
			notItself = true;
		}
	}
	std::string CardValue;
	int handSize = GameControl::Players[playerIndex].Hand.size();
	CardValue = GameControl::Players[playerIndex].Hand[rand() % handSize].getValue();
	bool fish = GameControl::TradeCard(targetIndex, playerIndex, CardValue);
	if (fish == true)
	{
		GameControl::Fish(playerIndex);
	}
}

int GameControl::exposeCard(int playerIndex, std::string cardToSearch)
{
	int playerSize = GameControl::Players.size();
	int targetIndex = NULL;
	bool notItself = false;
	std::vector<std::string> currentHandValue;
	for (int i = 0; i < playerSize; i++)
	{
		if (i != playerIndex)
		{
			currentHandValue = GameControl::Players[i].returnHandSuit();
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
			targetIndex = rand() % GameControl::Players.size();
			if (targetIndex != playerIndex)
			{
				notItself = true;
			}
		}
	}
	return targetIndex;
}

void GameControl::cheatingAI(int playerIndex)
{
	int targetIndex;
	int handSize = GameControl::Players[playerIndex].Hand.size();
	std::string CardValue = GameControl::Players[playerIndex].Hand[rand() % handSize].getValue();
	targetIndex = GameControl::exposeCard(playerIndex, CardValue);
	bool fish = GameControl::TradeCard(targetIndex, playerIndex, CardValue);
	if (fish == true)
	{
		GameControl::Fish(playerIndex);
	}
}

void GameControl::endgame(void)
{
	system("cls");
	int currentPoint;
	int maxPoint=0, maxPointIndex;
	for (int i = 0; i < GameControl::Players.size(); i++)
	{
		currentPoint = GameControl::Players[i].getPoint();
		std::cout << "Player " << i << " : " << currentPoint << "pts"<<std::endl;
		if (currentPoint > maxPoint)
		{
			maxPoint = currentPoint;
			maxPointIndex = i;
		}
		std::cout << "The winner is Player " << maxPointIndex << " with " << maxPoint << "pts"<<std::endl;
		std::cout << "Thank you for playing." << std::endl;
	}
}

void GameControl::emptyHand(int playerIndex)
{
	int deckSize = GameControl::Deck.deckSize();
	if (deckSize >= 7)
	{
		GameControl::SevenCardDeal(playerIndex);
	}
	else
	{
		for (int i = 0; i < deckSize; i++)
		{
			GameControl::DealCard(playerIndex);
		}
	}
}
