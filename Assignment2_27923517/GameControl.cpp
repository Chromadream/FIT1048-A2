#include "GameControl.h"
#include <iostream>

/*
 * GameControl::GameControl(int totalPlayer, int humanPlayer)
 * GameControl constructor
 * Adjustable player size
 */
GameControl::GameControl(int totalPlayer, int humanPlayer)
{
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
		for (int k = 0; k < totalPlayer; k++)
		{
			GameControl::DealCard(k);//dealing new cards
		}
	}
}
/*
 * GameControl::GameStart(void)
 * An instance of running game
 */
void GameControl::GameStart(void)
{
	int counter = 1;//turn count to control the AI's behavior
	bool handNotEmpty;
	while (GameControl::removedCard.size() < 52)
	{
		for (size_t i = 0; i < GameControl::Players.size(); i++)
		{
			handNotEmpty = true;//assumes that the player's hand is not empty
			std::cout << "It's Player " << i << "'s turn. Current turn count is: " << counter << std::endl;
			if (GameControl::Players[i].Hand.size() == 0)
			{
				handNotEmpty = GameControl::emptyHand(i);//checking if a player's hand is empty, and add card if empty
			}
			if (handNotEmpty)
			{
				if (GameControl::Players[i].isHuman == true)
				{
					GameControl::HumanTurn(i);//human turn
				}
				else
				{
					GameControl::AITurn(i, counter);//AI turn
				}
			}
			else
			{
				std::cout << "Player's hand is empty. Skipped." << std::endl;
			}
			if (GameControl::removedCard.size() >= 52)
			{
				break;//if all card is played, then break the player loop
			}
			std::cout << "\n\n";
		};
		counter++;
	}
	GameControl::endgame();//calling scoreboard and winner determination
}

/*
 * void GameControl::SevenCardDeal(int playerIndex)
 * deals seven cards in the case of a player's hand is empty, and the deck has 7 or more cards
 */
void GameControl::SevenCardDeal(int playerIndex)
{
	for (int i = 0; i < 7; i++)
	{
		GameControl::DealCard(playerIndex);//deals seven new card
	}
}

/*
 * void GameControl::DealCard(int playerIndex)
 * take last card from deck, and add it to the specified player's hand
 */
void GameControl::DealCard(int playerIndex)
{
	Card dealtCard = GameControl::Deck.PopCard();//get a card from the deck
	GameControl::Players[playerIndex].addHand(dealtCard);//append the card to the player's hand
}

/*
 * bool GameControl::TradeCard(int SourceIndex, int DestIndex, std::string CardValue)
 * Trade Cards with value specified by CardValue, from Player [SourceIndex] to Player[DestIndex]
 * Returns a boolean that determines whether a player should fish or not
 */
bool GameControl::TradeCard(int SourceIndex, int DestIndex, std::string CardValue)
{
	std::cout << "Player " << DestIndex << " asks " << CardValue << " from Player " << SourceIndex << std::endl;
	bool FishOrNot;
	std::vector<Card> TradedCards;
	TradedCards = GameControl::Players[SourceIndex].removeHand(CardValue);//retrieve card from the player asked
	if (TradedCards.empty()) {
		//if the Player[SourceIndex] doesn't have the card asked
		std::cout << "Player " << SourceIndex << " doesn't have the card. Fish!" << std::endl;
		FishOrNot = true;
	}
	else
	{
		GameControl::Players[DestIndex].Hand.insert(GameControl::Players[DestIndex].Hand.end(), TradedCards.begin(), TradedCards.end());
		//Append the received cards to the destination player's hand
		GameControl::CheckPoint(DestIndex);//check if the player made a point
		FishOrNot = false;
	}
	return FishOrNot;
}

/*
 * void GameControl::CheckPoint(int playerIndex)
 * Checks if the player have 4 cards of the same value
 * And add a point to the player, if a player does have 4 cards of the same value
 * Also prints the set of cards.
 */
void GameControl::CheckPoint(int playerIndex)
{
	std::string cardValue = GameControl::Players[playerIndex].Hand.back().getValue();//gets the value of the last card appended
	int count = 0;//initiates counter
	std::vector<std::string> playerHands = GameControl::Players[playerIndex].returnHandValue();//gets all values of the player's cards at hand
	for (size_t i = 0; i < playerHands.size(); i++)
	{
		if (playerHands[i] == cardValue)
		{
			count++;//counts the instance of the card
		}
	}
	if (count == 4)
	{
		std::vector<Card> removingCard = GameControl::Players[playerIndex].removeHand(cardValue);//add the card to the removed pile
		std::cout << "A book is made: ";
		for (int i = 0; i < 4; i++)
		{
			std::cout << "[" << removingCard[i].getValue() <<" "<< removingCard[i].getSuit() << "]";//prints the card
			GameControl::removedCard.push_back(removingCard.back());//add the card to the removed pile
		}
		std::cout << std::endl;
		GameControl::Players[playerIndex].addPoint();//add point to the player
	}
}

/*
 * void GameControl::Fish(int playerIndex)
 * Takes a card from the deck/pile to the player's hand
 * Also checks the player's point afterwards
 */
void GameControl::Fish(int playerIndex)
{
	int deckSize = GameControl::Deck.deckSize();//check deck size
	if(deckSize>0)
	{
		GameControl::DealCard(playerIndex);//deals card to the player
		GameControl::CheckPoint(playerIndex);//check if the player made a point
	}
	else
	{
		std::cout << "Can't fish, pile is empty." << std::endl;//the case where pile is empty
	}
}

/*
 * int GameControl::indexCheck(int playerIndex)
 * Checks player index input, whether it within the range of players participating
 * and the player doesn't reference its own index
 */
int GameControl::indexCheck(int playerIndex)
{
	int PlayerSize = GameControl::Players.size();//get the player size
	int userinput;
	bool validity = false;
	while (!validity)
	{
		std::cin >> userinput;
		if (std::cin.fail())
		{
			//the case where user input is not an integer
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			std::cout << "The index input is invalid. Please try with other number: ";
		}
		else
		{
			if (userinput >= 0 && userinput < PlayerSize && userinput != playerIndex)
			{
				validity = true;
				//if user inputs a valid player index number
			}
			else
			{
				std::cout << "The index input is invalid. Please try with other number: ";
			}
		}
	}
	return userinput;
}

/*
 * void GameControl::HumanTurn(int playerIndex)
 * The function that will be initiated if the current player is not an AI
 * Prints the current hand, before asking target index and target card
 */
void GameControl::HumanTurn(int playerIndex)
{
	//variable initiation
	std::string CardValue;
	int targetIndex;
	bool fish = false;
	while (!fish)
	{
		//loops until player fishes for card
		GameControl::PrettyPrintHand(playerIndex);
		if (GameControl::Players.size() > 2)
		{
			//asks the index of player to be asked for card
			//only if there's more than 2 players
			std::cout << "Please enter the index of the player to ask for card from: ";
			targetIndex = indexCheck(playerIndex);
		}
		else
		{
			//the case where two players are playing, either Human-AI or Human-Human
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
		CardValue = GameControl::handCheck(playerIndex);//checks if the value inserted is valid or not
		fish = GameControl::TradeCard(targetIndex, playerIndex, CardValue);
		if (fish == true)
		{
			GameControl::Fish(playerIndex);
		}
	}
}

/*
 * void GameControl::PrettyPrintHand(int playerIndex)
 * Prints the hand of the current player in a good way
 */
void GameControl::PrettyPrintHand(int playerIndex)
{
	std::vector<std::string> HandSuits = GameControl::Players[playerIndex].returnHandSuit();
	std::vector<std::string> HandValues = GameControl::Players[playerIndex].returnHandValue();
	int size = HandSuits.size();
	for (int i = 0; i < size; i++)
	{
		std::cout << "[" << HandValues[i] <<" "<< HandSuits[i] << "]";
		if (i%6 == 0 && i>=6)
		{
			std::cout << std::endl;
			//in the case where there are more than six cards, the next cards will be on different line
		}
	}
	std::cout << "\n";
}

/*
 * void GameControl::AITurn(int playerIndex, int currentTurnCount)
 * The case where the current player is the computer player
 * Turn count determines which behavior that will be used for playing
 */
void GameControl::AITurn(int playerIndex, int currentTurnCount)
{
	if (currentTurnCount < 5)
	{
		RandomAI(playerIndex);//uses completely random AI
	}
	else
	{
		cheatingAI(playerIndex);//asks random card, but first "peeks" for which player have the card
	}
}

/*
 * void GameControl::RandomAI(int playerIndex)
 * A completely random computer player algorithm
 * Asks random card from random player
 */
void GameControl::RandomAI(int playerIndex)
{
	bool notItself = false;
	int targetIndex;
	bool fish = false;
	while (!fish)
	{
		while (notItself == false)
		{
			//targets random player
			targetIndex = rand() % GameControl::Players.size();
			if (targetIndex != playerIndex)
			{
				notItself = true;
			}
		}
		std::string CardValue;
		int handSize = GameControl::Players[playerIndex].Hand.size();//get current player's hand
		CardValue = GameControl::Players[playerIndex].Hand[rand() % handSize].getValue();//asks random card
		fish = GameControl::TradeCard(targetIndex, playerIndex, CardValue);
		if (fish == true)
		{
			GameControl::Fish(playerIndex);
		}
	}
}

/*
 * int GameControl::exposeCard(int playerIndex, std::string cardToSearch)
 * Searches for Card with cardToSearch value from all players in the game
 * If no player have the card with value asked, will return random value
 *
 * This function serves as a reason why Player's hand are a public variable
 */
int GameControl::exposeCard(int playerIndex, std::string cardToSearch)
{
	int playerSize = GameControl::Players.size();
	int targetIndex = NULL;
	bool notItself = false;
	std::vector<std::string> currentHandValue;
	for (int i = 0; i < playerSize; i++)
	{
		//checks other player's hand
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
		//the case where no other player have the card with the same value as cardToSearch variable
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

/*
 * void GameControl::cheatingAI(int playerIndex)
 * AI algorithm where it still asks for random card
 * but "cheats" by running through all player's hand to determine which player to ask
 * In the case of the cards are not in any other player's hand, it will ask from a random player
 * Provides illusion of fairness, while giving the AI player slight edge on the game
 */
void GameControl::cheatingAI(int playerIndex)
{
	int targetIndex;
	bool fish = false;
	int handSize;
	std::string CardValue;
	while (!fish)
	{
		handSize = GameControl::Players[playerIndex].Hand.size();
		CardValue = GameControl::Players[playerIndex].Hand[rand() % handSize].getValue();
		targetIndex = GameControl::exposeCard(playerIndex, CardValue);
		fish = GameControl::TradeCard(targetIndex, playerIndex, CardValue);
		if (fish == true)
		{
			GameControl::Fish(playerIndex);
		}
	};
}

/*
 * void GameControl::endgame(void)
 * Shows scoreboard when the endgame condition is achieved
 */
void GameControl::endgame(void)
{
	system("cls");
	int currentPoint;
	int maxPoint=0, maxPointIndex;
	std::cout << "Scoreboard" << std::endl;
	for (size_t i = 0; i < GameControl::Players.size(); i++)
	{
		//prints points of all players
		currentPoint = GameControl::Players[i].getPoint();
		std::cout << "Player " << i << " : " << currentPoint << "pts"<<std::endl;
		if (currentPoint > maxPoint)
		{
			//determines the winner of the game
			maxPoint = currentPoint;
			maxPointIndex = i;
		}
	}
	std::cout << "The winner is Player " << maxPointIndex << " with " << maxPoint << "pts" << std::endl;
	std::cout << "Thank you for playing." << std::endl;
}

/*
 * bool GameControl::emptyHand(int playerIndex)
 * The functin that will be run if the current player's hand is zero
 * Returns a boolean that will determine whether the player's turn will be skipped or not
 */
bool GameControl::emptyHand(int playerIndex)
{
	int deckSize = GameControl::Deck.deckSize();
	bool handNotEmpty = true;
	if (deckSize >= 7)
	{
		//if deck size still adequate for drawing seven cards
		GameControl::SevenCardDeal(playerIndex);
	}
	else if (deckSize == 0)
	{
		//skipping player if the deck and hand is empty
		handNotEmpty = false;
	}
	else
	{
		//take remaining cards from the deck
		for (int i = 0; i < deckSize; i++)
		{
			GameControl::DealCard(playerIndex);
		}
	}
	return handNotEmpty;
}

/*
 * std::string GameControl::handCheck(int playerIndex)
 * Check if the player's string input is valid or not
 * and if the value that the player's asked is on hand or not
 * As the game only allows that the player can only ask for card that are on the hand
 */
std::string GameControl::handCheck(int playerIndex)
{
	std::vector<std::string> PossibleValue = GameControl::Players[playerIndex].returnHandValue();
	std::string input;
	bool validity = false;
	while (validity == false)
	{
		std::cin >> input;
		input[0] = toupper(input[0]);//convert value to uppercase, so that the user input can be case insensitive
		if (std::find(PossibleValue.begin(), PossibleValue.end(), input) != PossibleValue.end())
		{
			//the case where the value asked is also on the player's hand
			validity = true;
		}
		else
		{
			//case where input is invalids
			std::cout << "You can't ask for a card you don't have. Please try again: ";
		}
	}
	return input;
}
