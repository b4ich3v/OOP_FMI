#include "WithdrawalUnoCard.h"

int main()
{

	WithdrawalUnoCard card1(CountOfCardToBeDrawn::FOUR, Color::BLUE);
	WithdrawalUnoCard card2(CountOfCardToBeDrawn::SIX, Color::RED);
	card1.printCard(&card1);
	card2.printCard(&card2);

	return 0;

}
