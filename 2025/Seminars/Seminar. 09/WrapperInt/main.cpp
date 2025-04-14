#include "WrapperInt.h"

int main()
{

	WrapperInt number1(97);
	std::cout << number1 << std::endl;

	bool isPositive = (bool)number1;
	int copy1OfNumber1 = (int)number1;
	char symbolASCII = (char)number1;
	double copy2OfNumber1 = (double)number1;

	std::cout << isPositive << std::endl;
	std::cout << copy1OfNumber1 << std::endl;
	std::cout << symbolASCII << std::endl;
	std::cout << copy2OfNumber1 << std::endl;

	WrapperInt number2(0);
	std::cin >> number2;
	std::cout << number2 << std::endl;

	return 0;

}
