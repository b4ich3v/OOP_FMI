#include "SaveableDoubleArray.h"

SaveableDoubleArray::SaveableDoubleArray(): DoubleArray() {}

SaveableDoubleArray::SaveableDoubleArray(double* array, int size): DoubleArray(array, size) {}

void SaveableDoubleArray::saveToFile(std::ofstream& file) const 
{

	if (!file.is_open()) throw std::runtime_error("Error");

	int size = getSize();
	const double* array = getArr();

	file.write((const char*)&size, sizeof(int));
	file.write((const char*)array, sizeof(double) * size);

	file.close();

}

void SaveableDoubleArray::readFromFile(std::ifstream& file) 
{

	if (!file.is_open()) throw std::runtime_error("Error");

	int size = 0;
	double* array = nullptr;

	file.read((char*)&size, sizeof(int));
	array = new double[size];
	file.read((char*)array, sizeof(double) * size);

	SaveableDoubleArray result(array, size);
	*this = result;

	file.close();

}

