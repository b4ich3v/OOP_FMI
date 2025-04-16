#include "UnoCard.h"

UnoCard::UnoCard(int number, Color color)
{

	if (number < 0 || number > 9) throw std::logic_error("Error");

	this->number = number;
	this->color = color;

}

void UnoCard::printCard() const 
{

	std::cout << number << " ";

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

