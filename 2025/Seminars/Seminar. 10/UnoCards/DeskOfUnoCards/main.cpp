#include "SpecialUnoCard.h"
#include "DigitUnoCard.h"
#include "WithdrawalUnoCard.h"
#include "DeskOfUnoCards.h"

int main()
{

	DigitUnoCard d1(1, Color::BLUE);
	DigitUnoCard d2(2, Color::GREEN);
	DigitUnoCard d3(5, Color::YELLOW);
	DigitUnoCard d4(7, Color::RED);

	SpecialUnoCard s1(Action::REVERSE, Color::BLUE);
	SpecialUnoCard s2(Action::SKIP, Color::YELLOW);

	WithdrawalUnoCard w1(CountOfCardToBeDrawn::FOUR, Color::BLUE);
	WithdrawalUnoCard w2(CountOfCardToBeDrawn::SIX, Color::RED);

	DeskOfUnoCards desk;

	desk.addCard(&d1);
	desk.addCard(&d2);
	desk.addCard(&d3);
	desk.addCard(&d4);

	desk.addCard(&s1);
	desk.addCard(&s2);

	desk.addCard(&w1);
	desk.addCard(&w2);

	desk.printDesk();
	desk.removeCard(d1);
	desk.printDesk();

	return 0;

}
