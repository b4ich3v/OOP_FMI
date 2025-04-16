#include "UnoCard.h"
#pragma once

class DigitUnoCard: public UnoCard
{
private:

	int number = 0;

public:

	DigitUnoCard(int number, Color color);

	bool isDigitUnoCard(const UnoCard* ptr) const override;

	bool isSpecialUnoCard(const UnoCard* ptr) const override;

	bool isWithdrawalUnoCard(const UnoCard* ptr) const override;

	UnoCard* clone() const override;

	void printCard(const UnoCard* ptr) const override;

};

