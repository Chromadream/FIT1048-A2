#include "Deck.h"

Deck::Deck() {
	std::string PossibleSuit[4] = { "Diamond","Club","Spade","Heart" };
	std::string PossibleValue[13] = { "A","2","3","4","5","6","7","8","9","10","J","Q","K" };
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			cardDeck.push_back(Card(PossibleSuit[i], PossibleValue[j]));
		}
	}
}

void Deck::DeckShuffle()
{
	std::random_shuffle(cardDeck.begin(), cardDeck.end(), time(NULL));
}

Card Deck::PopCard()
{
	Card poppedCard;
	poppedCard = cardDeck.back();
	cardDeck.pop_back();
	return poppedCard;
}