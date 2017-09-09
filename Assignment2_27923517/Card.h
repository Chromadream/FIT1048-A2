#ifndef CARD_H
#define CARD_H
#include <string>

class Card {
public:
	Card();
	Card(std::string Suit, std::string Value);
	std::string getSuit();
	std::string getValue();
private:
	std::string Suit;
	std::string Value;
};

#endif // !CARD_H
