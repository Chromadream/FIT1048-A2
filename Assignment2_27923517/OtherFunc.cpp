#include "OtherFunc.h"

int IntegerCheck(int upperLimit, int lowerLimit)
{
	int value;
	bool validity = false;
	while (validity == false)
	{
		std::cin >> value;
		if (value >= lowerLimit || value <= upperLimit)
		{
			validity = true;
		}
		else
		{
			std::cout << "The value is invalid. Try a different value: ";
		}
	}
	return value;
}

std::string ValidityCheck(int FeatureSet)
{
	std::vector<std::string> PossibleSuit = { "Diamond","Club","Spade","Heart" };
	std::vector<std::string> PossibleValue = { "A","2","3","4","5","6","7","8","9","10","J","Q","K" };
	std::string input;
	bool validity = false;
	while (validity == false)
	{
		std::cin >> input;
		switch (FeatureSet)
		{
		case 0:
			input[0] = toupper(input[0]);
			if (std::find(PossibleSuit.begin(), PossibleSuit.end(), input) != PossibleSuit.end())
			{
				validity = true;
			};
			break;
		case 1:
			input[0] = toupper(input[0]);
			if (std::find(PossibleValue.begin(), PossibleValue.end(), input) != PossibleValue.end())
			{
				validity = true;
			};
			break;
		}
	}
	return input;
}
