#include "DigitUnoCard.h"

DigitUnoCard::DigitUnoCard(int number, Color color): UnoCard(color)
{

	if (number < 0 || number > 9) throw std::logic_error("Error");

	this->number = number;

}

bool DigitUnoCard::isDigitUnoCard(const UnoCard* ptr) const
{

	return true;

}

bool DigitUnoCard::isSpecialUnoCard(const UnoCard* ptr) const 
{

	return false;

}

bool DigitUnoCard::isWithdrawalUnoCard(const UnoCard* ptr) const 
{

	return false;

}

void DigitUnoCard::printCard(const UnoCard* ptr) const 
{

	std::cout << number << " ";
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

UnoCard* DigitUnoCard::clone() const 
{

	return new DigitUnoCard(*this);

}
