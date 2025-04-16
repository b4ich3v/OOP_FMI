#include "UnoCard.h"

int main()
{

	UnoCard card(Color::BLUE);
	std::cout << (int)card.getColor() << std::endl;

	return 0;

}
