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

