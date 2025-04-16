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

public:

	UnoCard(Color color);

	Color getColor() const;

};

