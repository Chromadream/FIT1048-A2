#ifndef DECK_H
#define DECK_H
#include "Card.h"
#include <vector>
#include <string>
#include <algorithm>
#include <random>


class Deck {
public:
	Deck();
	void DeckShuffle();
	Card PopCard();
private:
	std::vector<Card> cardDeck;
};

#endif // !DECK_H
