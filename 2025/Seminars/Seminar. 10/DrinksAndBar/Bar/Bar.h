#include "AlcoholicDrink.h"
#pragma once

class Bar
{
private:

	Drink** drinks = nullptr;
	int capacity = 100;
	int overallCountOfSoldDrinks = 0;

	int countOfDrinks = 0;
	int countOfNorDrinks = 0;
	int countOfAlcDrinks = 0;

	static int countOfSoldAlcDrinks;
	static int countOfSoldNorDrinks;

	void free();

	void copyFrom(const Bar& other);

	void moveTo(Bar&& other);

public:

	Bar() = default;

	Bar(const Drink* const* drinks, 
		int countOfNormalDrinks, int countOfAlcoholicDrinks, const bool* isAlcAtIndex);

	Bar(const Bar& other);

	Bar(Bar&& other) noexcept;

	Bar& operator = (const Bar& other);

	Bar& operator = (Bar&& other) noexcept;

	~Bar();

	void printBar() const;

	void printStatistic() const;

	const Drink& getDrink();

};
