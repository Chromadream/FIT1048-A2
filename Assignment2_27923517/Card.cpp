#include "Card.h"
#include <sstream>

Card::Card()
{
	Card::Suit = "Spades";
	Card::Value = "Ace";
};

Card::Card(std::string Suit, std::string Value)
{
	Card::Suit = Suit;
	Card::Value = Value;
}
std::string Card::getSuit()
{
	std::stringstream Suit;
	Suit << Card::Suit;
	return Suit.str();
}
std::string Card::getValue()
{
	std::stringstream Value;
	Value << Card::Value;
	return Value.str();
}

