#include "UnoCard.h"
#pragma once

enum class CountOfCardToBeDrawn
{

	FOUR = 0,
	SIX =  1

};

class WithdrawalUnoCard: public UnoCard
{
private:

	CountOfCardToBeDrawn count;

public:

	WithdrawalUnoCard(CountOfCardToBeDrawn count, Color color);

	bool isDigitUnoCard(const UnoCard* ptr) const override;

	bool isSpecialUnoCard(const UnoCard* ptr) const override;

	bool isWithdrawalUnoCard(const UnoCard* ptr) const override;

	UnoCard* clone() const override;

	void printCard(const UnoCard* ptr) const override;

};

