#include <fstream>
#include "DoubleArray.h"
#pragma once

class SaveableDoubleArray: public DoubleArray
{
public:

	SaveableDoubleArray();

	SaveableDoubleArray(double* array, int size);

	void saveToFile(std::ofstream& file) const;

	void readFromFile(std::ifstream& file);

};


