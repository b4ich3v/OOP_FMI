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

	void printWithdrawalUnoCard() const;

};


