#include "DigitUnoCard.h"

int main()
{

	try
	{

		DigitUnoCard card1(3, Color::BLUE);
		DigitUnoCard card2(7, Color::RED);
		card1.printCard(&card1);
		card2.printCard(&card2);

		DigitUnoCard card3(-1, Color::GREEN);
		card3.printCard(&card3);

	}
	catch (const std::exception& e)
	{

		std::cout << e.what() << std::endl;

	}

	return 0;

}
