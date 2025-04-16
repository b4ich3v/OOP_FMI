#include "ModifiableDoubleArray.h"

ModifiableDoubleArray::ModifiableDoubleArray(): DoubleArray() {}

ModifiableDoubleArray::ModifiableDoubleArray(double* array, int size): DoubleArray(array, size) {}

void ModifiableDoubleArray::push_back(double number) 
{

	if (getSize() == getCapacity()) publicResize();

	int lastIndex = getSize();
	double* array = getArr();

	array[lastIndex] = number;
	incrementSize();

}

void ModifiableDoubleArray::pop_back() 
{

	if (getSize() == 0) return;

	decrementSize();

}

const double ModifiableDoubleArray::last() const 
{

	if (getSize() == 0) throw std::logic_error("Error");

	const double* array = getArr();

	return array[getSize() - 1];

}
