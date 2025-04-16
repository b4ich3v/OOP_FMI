#include "SpecialUnoCard.h"

int main()
{

	SpecialUnoCard card1(Action::REVERSE, Color::BLUE);
	SpecialUnoCard card2(Action::SKIP, Color::RED);
	card1.printSpecialUnoCard();
	card2.printSpecialUnoCard();

	return 0;

}
