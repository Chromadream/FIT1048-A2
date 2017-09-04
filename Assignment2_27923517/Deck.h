#ifndef DECK_H
#define DECK_H
#include "Card.h"
#include <vector>
#include <string>

class Deck {
public:
	Deck();
	void DeckShuffle();
private:
	std::vector<Card> cardDeck;
};

#endif // !DECK_H
