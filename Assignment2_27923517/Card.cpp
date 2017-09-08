#include "Card.h"

Card::Card(std::string Suit, std::string Value)
{
	Card::Suit = Suit;
	Card::Value = Value;
}
std::string Card::getSuit()
{
	return Card::Suit;
}
std::string Card::getValue()
{
	return Card::Value;
}

