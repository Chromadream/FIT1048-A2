#include "GameRules.h"
#include "OtherFunc.h"
#include <iostream>
int main(void)
{
	std::cout << "Welcome to GoFish C++!" << std::endl;
	std::cout << "Please enter the total player in this game: (Max 4, Min 2)";
	int TotalPlayer = IntegerCheck(4, 2);
	std::cout << "\n";
	std::cout << "Please enter the human player in this game: ";
	int HumanPlayer = IntegerCheck(TotalPlayer, 2);
	std::cout << std::endl;
	GameRules Game = GameRules(TotalPlayer, HumanPlayer);
	Game.GameStart();
	system("pause");
	return 0;
}