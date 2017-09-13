#include "Card.h"

/*
 * Card::Card(std::string Suit, std::string Value)
 * Constructor function for Card class which take card suit and value
 */
Card::Card(std::string Suit, std::string Value)
{
	Card::Suit = Suit;
	Card::Value = Value;
}

/*
 * std::string Card::getSuit()
 * Get the card's suit
 */
std::string Card::getSuit()
{
	return Card::Suit;
}

/*
 * std::string Card::getSuit()
 * Get the card's value
 */
std::string Card::getValue()
{
	return Card::Value;
}

