#include "Card.h"

Card::Card()
{
	Card::Suit = "Spades";
	Card::Value = "Ace";
};

Card::Card(std::string Suit, std::string Value)
{
	Card::Suit = Suit;
	Card::Value = Value;
};
