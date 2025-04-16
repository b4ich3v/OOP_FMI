#include "WithdrawalUnoCard.h"

WithdrawalUnoCard::WithdrawalUnoCard(CountOfCardToBeDrawn count, Color color): UnoCard(color), count(count) {}

bool WithdrawalUnoCard::isDigitUnoCard(const UnoCard* ptr) const  
{

	return false;

}

bool WithdrawalUnoCard::isSpecialUnoCard(const UnoCard* ptr) const 
{

	return false;

}

bool WithdrawalUnoCard::isWithdrawalUnoCard(const UnoCard* ptr) const 
{

	return true;

}

UnoCard* WithdrawalUnoCard::clone() const 
{

	return new WithdrawalUnoCard(*this);

}

void WithdrawalUnoCard::printCard(const UnoCard* ptr) const 
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
