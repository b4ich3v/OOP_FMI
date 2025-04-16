#include "DoubleArray.h"
#pragma once

class ModifiableDoubleArray: public DoubleArray
{
public:

	ModifiableDoubleArray();

	ModifiableDoubleArray(double* array, int size);

	void push_back(double number);

	void pop_back();

	const double last() const;

};


