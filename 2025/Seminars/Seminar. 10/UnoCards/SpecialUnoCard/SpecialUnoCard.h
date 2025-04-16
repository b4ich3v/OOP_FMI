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

	void printSpecialUnoCard() const;

};

