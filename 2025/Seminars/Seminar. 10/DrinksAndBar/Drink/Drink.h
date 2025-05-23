#include <iostream>
#include <cstring>
#pragma once

class Drink
{
private:

	char* name = nullptr;
	double quantity = 0;

	void free();

	void copyFrom(const Drink& other);

	void moveTo(Drink&& other);

public:

	Drink();

	Drink(const char* name, double quantity);

	Drink(const Drink& other);

	Drink(Drink&& other) noexcept;

	Drink& operator = (const Drink& other);

	Drink& operator = (Drink&& other) noexcept;

	const char* getName() const;

	double getQuantity() const;

	virtual ~Drink();

	virtual void print() const;

	virtual Drink* clone() const;

};

