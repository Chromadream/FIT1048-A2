#include "OtherFunc.h"

/*
 * int IntegerCheck(int upperLimit, int lowerLimit)
 * Checks whether user's input is a valid integer
 * and fits the upper limit and lower limit specified
 */
int IntegerCheck(int upperLimit, int lowerLimit)
{
	int value;
	bool validity = false;
	while (validity == false)
	{
		std::cin >> value;
		if (std::cin.fail())
		{
			//the case where user's input is not an integer, or not a number
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			std::cout << "The value is invalid. Try a different value: ";
		}
		else
		{
			
			if (value >= lowerLimit  && value <= upperLimit)
			{
				//the case where the user's input is within the valid range
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

