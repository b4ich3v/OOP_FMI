#include <iostream>
#pragma once

enum class Color
{

	RED = 0,
	GREEN = 1,
	BLUE = 2,
	YELLOW = 3

};

class DigitUnoCard;

class SpecialUnoCard;

class WithdrawalUnoCard;

class UnoCard
{
private:

	Color color;

public:

	UnoCard(Color color);

	Color getColor() const;

	virtual bool isDigitUnoCard(const UnoCard* ptr) const;

	virtual bool isSpecialUnoCard(const UnoCard* ptr) const;

	virtual bool isWithdrawalUnoCard(const UnoCard* ptr) const;

	virtual void printCard(const UnoCard* ptr) const;

	virtual UnoCard* clone() const = 0;

	virtual ~UnoCard() = default;

};

