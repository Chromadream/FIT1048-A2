#include "Player.h"
#include <iostream>

Player::Player(bool isHuman)
{
	Player::isHuman = isHuman;
	Player::PlayerPoint = 0;
};

void Player::addHand(Card newCard)
{
	Player::Hand.push_back(newCard);
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
	return removedCards;
}


std::vector<std::string> Player::returnHandValue(void)
{
	std::vector<std::string> ValueList;
	int HandSize = Player::Hand.size();
	for (int i = 0; i < HandSize; i++)
	{
		std::string appendedString = Player::Hand[i].getValue();
		ValueList.push_back(appendedString);
	}
	return ValueList;
}

std::vector<std::string> Player::returnHandSuit(void)
{
	std::vector<std::string> SuitList;
	int HandSize = Player::Hand.size();
	for (int i = 0; i < HandSize; i++)
	{
		std::string appendedString = Player::Hand[i].getSuit();
		SuitList.push_back(appendedString);
	}
	return SuitList;
}


void Player::addPoint(void)
{
	Player::PlayerPoint += 1;
}
