#include "PrintableDoubleArray.h"

PrintableDoubleArray::PrintableDoubleArray(): DoubleArray() {}

PrintableDoubleArray::PrintableDoubleArray(double* array, int size): DoubleArray(array, size) {}

std::istream& operator >> (std::istream& is, DoubleArray& db) 
{

	int size = 0;
	is >> size;

	double* data = new double[size];

	for (int i = 0; i < size; i++)
	{

		is >> data[i];

	}

	DoubleArray newVector(data, size);
	db = newVector;
	delete[] data;

	return is;

}

std::ostream& operator << (std::ostream& os, const DoubleArray& db) 
{

	os << db.getSize() << ' ';

	for (int i = 0; i < db.getSize(); i++)
	{

		os << db[i] << ' ';

	}

	return os;

}
