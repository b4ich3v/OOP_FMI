#include <cstring>
#include <iostream>
#include <fstream>
#pragma once

namespace HELPERS
{

	const char PATTERN[17] = "0123456789ABCDEF";

	int charToDigit(char ch);

}

class KBaseNumber
{
private:

	int decimalNumber = 0;
	char* strNumber = nullptr;
	int countingSystem = 10;

	void setStrNumber(const char* strNumber);

	void setCountingSystem(int countingSystem);

	void setDecimalNumber();

	void free();

	void copyFrom(const KBaseNumber& other);

public:

	KBaseNumber() = default;

	KBaseNumber(const char* strNumber, int countingSystem);

	KBaseNumber(const KBaseNumber& other);

	KBaseNumber& operator = (const KBaseNumber& other);

	~KBaseNumber();

	void update(const char* strNumber, int countingSystem);

	void print() const;

	void convertTo(int newCountingSystem);

	bool compareWith(const KBaseNumber& other) const;

	void saveToFile(std::ofstream& file) const;

	void readFromFile(std::ifstream& file);

};
