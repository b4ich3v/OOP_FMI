#include "Drink.h"
#pragma once

class AlcoholicDrink: public Drink
{
private:

	double alcPer = 0;

public:

	AlcoholicDrink(const char* name, double quantity, double alcPer);

	double getAlcPer() const;

};


