#include "SpecialUnoCard.h"

int main()
{

	SpecialUnoCard card1(Action::REVERSE, Color::BLUE);
	SpecialUnoCard card2(Action::SKIP, Color::RED);
	card1.printCard(&card1);
	card2.printCard(&card2);

	return 0;

}
