#include "GameControl.h"
#include "OtherFunc.h"
#include <iostream>
#include <time.h>
int main(void)
{
	srand(time(NULL));//RNG seeding
	//initial game setup
	std::cout << "Welcome to GoFish C++!" << std::endl;
	std::cout << "Please enter the total player in this game: (Max 4, Min 2)";
	int TotalPlayer = IntegerCheck(4, 2);
	std::cout << "\n";
	std::cout << "Please enter the human player in this game: ";
	int HumanPlayer = IntegerCheck(TotalPlayer, 1);
	std::cout << std::endl;
	GameControl Game = GameControl(TotalPlayer, HumanPlayer);//initializing GameControl class
	system("cls");
	Game.GameStart();//starting the game
	system("pause");
	return 0;
}
