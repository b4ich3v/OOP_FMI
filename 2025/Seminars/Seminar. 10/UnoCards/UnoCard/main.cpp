#include "UnoCard.h"

int main()
{

	try
	{

		UnoCard card1(3, Color::BLUE);
		UnoCard card2(7, Color::RED);

		card1.printCard();
		card2.printCard();

		UnoCard card3(-1, Color::GREEN);
		card3.printCard();

	}
	catch (const std::exception& e)
	{

		std::cout << e.what() << std::endl;

	}

	return 0;

}
