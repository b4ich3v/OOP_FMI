#include "WithdrawalUnoCard.h"

WithdrawalUnoCard::WithdrawalUnoCard(CountOfCardToBeDrawn count, Color color): UnoCard(color), count(count) {}

void WithdrawalUnoCard::printWithdrawalUnoCard() const 
{

	switch (count)
	{

	case CountOfCardToBeDrawn::FOUR: std::cout << "FOUR "; break;
	case CountOfCardToBeDrawn::SIX: std::cout << "SIX "; break;
	default: break;
		
	}

	Color color = getColor();

	switch (color)
	{

	case Color::RED: std::cout << "RED"; break;
	case Color::GREEN: std::cout << "GREEN"; break;
	case Color::BLUE: std::cout << "BLUE"; break;
	case Color::YELLOW: std::cout << "YELLOW"; break;
	default: break;

	}

	std::cout << std::endl;

}
