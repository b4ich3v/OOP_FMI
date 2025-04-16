#include <iostream>
#pragma once

enum class Color
{

	RED = 0,
	GREEN = 1,
	BLUE = 2,
	YELLOW = 3

};

class UnoCard
{
private:

	Color color;
	int number = 0;

public:

	UnoCard(int number, Color color);

	void printCard() const;

};


