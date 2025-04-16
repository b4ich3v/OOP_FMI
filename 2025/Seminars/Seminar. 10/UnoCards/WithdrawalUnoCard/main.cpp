#include "WithdrawalUnoCard.h"

int main()
{

	WithdrawalUnoCard card1(CountOfCardToBeDrawn::FOUR, Color::BLUE);
	WithdrawalUnoCard card2(CountOfCardToBeDrawn::SIX, Color::RED);
	card1.printWithdrawalUnoCard();
	card2.printWithdrawalUnoCard();

	return 0;

}
