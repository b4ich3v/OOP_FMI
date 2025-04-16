#include "DigitUnoCard.h"

int main()
{

	try
	{

		DigitUnoCard card1(3, Color::BLUE);
		DigitUnoCard card2(7, Color::RED);
		card1.printDigitUnoCard();
		card2.printDigitUnoCard();

		DigitUnoCard card3(-1, Color::GREEN);
		card3.printDigitUnoCard();

	}
	catch (const std::exception& e)
	{

		std::cout << e.what() << std::endl;

	}

	return 0;

}
