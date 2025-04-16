#include "UnoCard.h"
#pragma once

enum class Action
{

	SKIP = 0,
	REVERSE = 1

};

class SpecialUnoCard: public UnoCard
{
private:

	Action action;

public:

	SpecialUnoCard(Action action, Color color);

	bool isDigitUnoCard(const UnoCard* ptr) const override;

	bool isSpecialUnoCard(const UnoCard* ptr) const override;

	bool isWithdrawalUnoCard(const UnoCard* ptr) const override;

	UnoCard* clone() const override;

	void printCard(const UnoCard* ptr) const override;

};

