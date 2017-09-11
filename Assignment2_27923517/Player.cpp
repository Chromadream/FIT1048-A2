#include "Player.h"
#include <iostream>

/*
 * Player::Player(bool isHuman)
 * A constructor function for the Player class
 */
Player::Player(bool isHuman)
{
	Player::isHuman = isHuman;
	Player::PlayerPoint = 0;
};
/*
 * void Player::addHand(Card newCard)
 * Adds a card to the Player's hand
 */
void Player::addHand(Card newCard)
{
	Player::Hand.push_back(newCard);
}

/*
 * void Player::addHand(std::string Value)
 * Remove cards from Player's Hand 
 * which have the Card Value requested
 */
std::vector<Card> Player::removeHand(std::string Value)
{
	//initialization
	std::vector<Card> removedCards;
	std::string currentCardValue;
	int HandSize = Player::Hand.size();
	int j = 0;
	for (int i = 0; i < HandSize; i++)
	{
		currentCardValue = Player::Hand[i].getValue();
		if (currentCardValue == Value)
		{
			//adds the card to the new vector
			removedCards.push_back(Player::Hand[i]);
		}
	}
	while(j < HandSize)
	{
		currentCardValue = Player::Hand[j].getValue();
		if (currentCardValue == Value)
		{
			Player::Hand.erase(Player::Hand.begin()+j);//removes the card from Player's hand
			j = 0;//resets loop iterator as the vector size changes
			HandSize = Player::Hand.size();//updates vector size
		}
		else if (j == HandSize)
		{
			break;
		}
		j++;
	}
	return removedCards;
}

/*
 * std::vector<std::string> Player::returnHandValue(void)
 * Returns all card values from hand
 */
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

/*
 * std::vector<std::string> Player::returnHandSuit(void)
 * Returns all card suits from hand
 */
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

/*
 * void Player::addPoint(void)
 * Add a point to Player
 */
void Player::addPoint(void)
{
	Player::PlayerPoint += 1;
}

/*
 * void Player::getPoint(void)
 * Returns a Player's point
 */
int Player::getPoint(void)
{
	return PlayerPoint;
}
