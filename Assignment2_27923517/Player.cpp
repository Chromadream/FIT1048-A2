#include "Player.h"
#include <sstream>

Player::Player(bool isHuman)
{
	Player::isHuman = isHuman;
	Player::PlayerPoint = 0;
};

void Player::addHand(Card newCard)
{
	Player::Hand.push_back(newCard);
	Player::sortHand();
}

void Player::sortHand(void)
{
	std::string CurrentCardValue;
	std::string CheckedCardValue;
	int swappedCardPosition;
	int HandSize = Player::Hand.size();
	for (int i = 0; i < HandSize; i++)
	{
		CurrentCardValue = Player::Hand[i].getValue();
		for (int j = i+1; j < HandSize; j++)
		{
			CheckedCardValue = Player::Hand[j].getValue();
			if (CheckedCardValue < CurrentCardValue)
			{
				swappedCardPosition = j;
			}
		}
		std::iter_swap(Player::Hand.begin() + i, Player::Hand.begin() + swappedCardPosition);
	}
}

std::vector<Card> Player::removeHand(std::string Value)
{
	std::vector<Card> removedCards;
	std::string currentCardValue;
	int HandSize = Player::Hand.size();
	for (int i = 0; i < HandSize; i++)
	{
		currentCardValue = Player::Hand[i].getValue();
		if (currentCardValue == Value)
		{
			removedCards.push_back(Player::Hand[i]);
		}
	}
	for (int j = 0; j < HandSize; j++)
	{
		currentCardValue = Player::Hand[j].getValue();
		if (currentCardValue == Value)
		{
			Player::Hand.erase(Player::Hand.begin()+j);
		}
	}
	Player::sortHand();
	return removedCards;
}


std::vector<std::string> Player::returnHandValue(void)
{
	std::vector<std::string> ValueList;
	int HandSize = Player::Hand.size();
	for (int i = 0; i < HandSize; i++)
	{
		ValueList.push_back(Player::Hand[i].getValue());
	}
	return ValueList;
}

std::vector<std::string> Player::returnHandSuit(void)
{
	std::vector<std::string> SuitList;
	int HandSize = Player::Hand.size();
	for (int i = 0; i < HandSize; i++)
	{
		SuitList.push_back(Player::Hand[i].getSuit());
	}
	return SuitList;
}

std::string Player::PrettyPrintHand(void)
{
	std::stringstream PrintedHand;
	for (int i = 0; i < Player::Hand.size(); i++)
	{
		PrintedHand << "[" << Player::Hand[i].getValue << Player::Hand[i].getSuit << "]";
	}
	PrintedHand << std::endl;
	return PrintedHand.str();
}

void Player::addPoint(void)
{
	Player::PlayerPoint += 1;
}
