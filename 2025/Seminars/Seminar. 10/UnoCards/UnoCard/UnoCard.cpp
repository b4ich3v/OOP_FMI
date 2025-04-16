#include "UnoCard.h"

UnoCard::UnoCard(Color color) : color(color) {}

Color UnoCard::getColor() const 
{

	return color;

}

bool UnoCard::isDigitUnoCard(const UnoCard* ptr) const 
{

	return (*ptr).isDigitUnoCard(ptr);

}

bool UnoCard::isSpecialUnoCard(const UnoCard* ptr) const 
{

	return (*ptr).isSpecialUnoCard(ptr);

}

bool UnoCard::isWithdrawalUnoCard(const UnoCard* ptr) const 
{

	return (*ptr).isWithdrawalUnoCard(ptr);

}

void UnoCard::printCard(const UnoCard* ptr) const 
{

	(*ptr).printCard(ptr);

}
