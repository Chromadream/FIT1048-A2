#include "OtherFunc.h"

int IntegerCheck(int upperLimit, int lowerLimit)
{
	int value;
	bool validity = false;
	while (validity == false)
	{
		std::cin >> value;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			std::cout << "The value is invalid. Try a different value: ";
		}
		else
		{
			
			if (value >= lowerLimit  && value <= upperLimit)
			{
				validity = true;
			}
			else
			{
				std::cout << "The value is invalid. Try a different value: ";
			}
		}
	}
	return value;
}

std::string ValidityCheck(void)
{
	std::vector<std::string> PossibleValue = { "A","2","3","4","5","6","7","8","9","10","J","Q","K" };
	std::string input;
	bool validity = false;
	while (validity == false)
	{
		std::cin >> input;
		input[0] = toupper(input[0]);
		if (std::find(PossibleValue.begin(), PossibleValue.end(), input) != PossibleValue.end())
		{
			validity = true;
		}
		else
		{
			std::cout << "The value entered is invalid. Please enter a valid value.";
		}
	}
	return input;
}
