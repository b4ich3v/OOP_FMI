#include "SpecialUnoCard.h"

SpecialUnoCard::SpecialUnoCard(Action action, Color color): UnoCard(color), action(action) {}

void SpecialUnoCard::printSpecialUnoCard() const 
{

	switch (action)
	{

	case Action::SKIP: std::cout << "SKIP "; break;
	case Action::REVERSE: std::cout << "REVERSE "; break;
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
