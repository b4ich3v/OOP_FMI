#include "DoubleArray.h"
#pragma once

class PrintableDoubleArray: public DoubleArray
{
public:

	PrintableDoubleArray();

	PrintableDoubleArray(double* array, int size);

	friend std::istream& operator >> (std::istream& is, DoubleArray& db);

	friend std::ostream& operator << (std::ostream& os, const DoubleArray& db);

};

