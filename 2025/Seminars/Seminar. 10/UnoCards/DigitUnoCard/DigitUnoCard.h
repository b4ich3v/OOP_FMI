#include "UnoCard.h"
#pragma once

class DigitUnoCard: public UnoCard
{
private:

	int number = 0;

public:

	DigitUnoCard(int number, Color color);

	void printDigitUnoCard() const;

};


