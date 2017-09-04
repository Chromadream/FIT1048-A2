#ifndef CARD_H
#define CARD_H
#include <string>
class Card {
public:
	Card();
	Card(std::string Suit, std::string Value);
private:
	std::string Suit;
	std::string Value;
};

#endif // !CARD_H
