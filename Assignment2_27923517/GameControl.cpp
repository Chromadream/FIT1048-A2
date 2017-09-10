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
	for (int j = 0; j < 7; j++) 
	{
		for (int i = 0; i < totalPlayer; i++)
		{
			GameControl::DealCard(i);//dealing new cards
		}
	}
}

void GameControl::GameStart(void)
{
	int counter = 1;//turn count to control the AI
	while (GameControl::removedCardCount < 52)
	{
		for (size_t i = 0; i < GameControl::Players.size(); i++)
		{
			std::cout << "It's Player " << i << "'s turn. Current turn count is: " << counter << std::endl;
			if (GameControl::Players[i].Hand.size() == 0)
			{
				GameControl::emptyHand(i);//checking if a player's hand is empty, and add card if empty
			}
			if (GameControl::Players[i].isHuman == true)
			{
				GameControl::HumanTurn(i);//human turn
			}
			else
			{
				GameControl::AITurn(i, counter);//AI turn
			}
			if (GameControl::removedCardCount == 52)
			{
				break;//if all card is played, then break the player loop
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
		GameControl::DealCard(playerIndex);//deals seven new card
	}
}

void GameControl::DealCard(int playerIndex)
{
	Card dealtCard = GameControl::Deck.PopCard();//get a card from the deck
	GameControl::Players[playerIndex].addHand(dealtCard);//append the card to the player's hand
}

bool GameControl::TradeCard(int SourceIndex, int DestIndex, std::string CardValue)
{
	std::cout << "Player " << DestIndex << " asks " << CardValue << " from player " << SourceIndex << std::endl;
	bool FishOrNot;
	std::vector<Card> TradedCards;
	TradedCards = GameControl::Players[SourceIndex].removeHand(CardValue);//retrieve card from the player asked
	if (TradedCards.empty()) {
		//if the player doesn't have the card asked
		std::cout << "Player" << SourceIndex << " doesn't have the card. Fish!" << std::endl;
		FishOrNot = true;
	}
	else
	{
		for (size_t i = 0; i < TradedCards.size(); i++)
		{
			GameControl::Players[DestIndex].addHand(TradedCards.back());//append the card
			GameControl::CheckPoint(TradedCards.back(), DestIndex);//check the point of the card
			TradedCards.pop_back();//remove the card that was appended
		}
		FishOrNot = false;
	}
	return FishOrNot;
}

void GameControl::CheckPoint(Card currentCard, int playerIndex)
{
	std::string cardValue = currentCard.getValue();//gets the value of the card
	int count = 0;//initiates counter
	std::vector<std::string> playerHands = GameControl::Players[playerIndex].returnHandValue();//gets all values of the player's cards at hand
	for (size_t i = 0; i < playerHands.size(); i++)
	{
		if (playerHands[i] == cardValue)
		{
			count++;
		}
	}
	if (count == 4)
	{
		std::vector<Card> removingCard = GameControl::Players[playerIndex].removeHand(cardValue);//throw the card away
		removedCardCount += 4;//add the used card counter
		GameControl::Players[playerIndex].addPoint();//add point to the player
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
	std::string CardValue;
	int targetIndex;
	bool fish = false;
	while (!fish)
	{
		GameControl::PrettyPrintHand(playerIndex);
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
		fish = GameControl::TradeCard(targetIndex, playerIndex, CardValue);
		if (fish == true)
		{
			GameControl::Fish(playerIndex);
		}
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
	bool fish = false;
	while (!fish)
	{
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
		fish = GameControl::TradeCard(targetIndex, playerIndex, CardValue);
		if (fish == true)
		{
			GameControl::Fish(playerIndex);
		}
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
	bool fish = false;
	int handSize;
	while (!fish)
	{
		handSize = GameControl::Players[playerIndex].Hand.size();
		std::string CardValue = GameControl::Players[playerIndex].Hand[rand() % handSize].getValue();
		targetIndex = GameControl::exposeCard(playerIndex, CardValue);
		fish = GameControl::TradeCard(targetIndex, playerIndex, CardValue);
		if (fish == true)
		{
			GameControl::Fish(playerIndex);
		}
	};
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
