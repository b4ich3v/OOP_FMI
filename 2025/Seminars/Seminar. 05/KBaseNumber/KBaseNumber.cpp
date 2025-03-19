#include "KBaseNumber.h"

void KBaseNumber::setStrNumber(const char* strNumber)
{
	if (strNumber == nullptr) return;

	delete[] this->strNumber;
	this->strNumber = new char[strlen(strNumber) + 1];
	strncpy(this->strNumber, strNumber, strlen(strNumber));
	this->strNumber[strlen(strNumber)] = '\0';

}

void KBaseNumber::setCountingSystem(int countingSystem)
{

	if (countingSystem <= 0 || countingSystem > 16) return;

	this->countingSystem = countingSystem;

}

void KBaseNumber::setDecimalNumber()
{

	decimalNumber = 0;

	int len = strlen(strNumber);
	int power = 1;

	for (int i = len - 1; i >= 0; i--) 
	{

		int digit = HELPERS::charToDigit(strNumber[i]);

		if (digit < 0 || digit >= countingSystem) 
		{

			decimalNumber = 0;
			return; 

		}

		decimalNumber += digit * power;
		power *= countingSystem;

	}

}

void KBaseNumber::free()
{

	delete[] strNumber;
	strNumber = nullptr;
	countingSystem = 2;
	decimalNumber = 0;

}

void KBaseNumber::copyFrom(const KBaseNumber& other)
{

	strNumber = new char[strlen(other.strNumber) + 1];
	strncpy(this->strNumber, other.strNumber, strlen(other.strNumber));
	this->strNumber[strlen(other.strNumber)] = '\0';
	this->countingSystem = other.countingSystem;
	this->decimalNumber = other.decimalNumber;

}

void KBaseNumber::convertTo(int newCountingSystem)
{

	if (newCountingSystem < 2 || newCountingSystem > 16) return;

	char buffer[65] = { 0 };
	int number = decimalNumber;
	int index = 0;

	if (number == 0)
	{

		buffer[0] = '0';
		buffer[1] = '\0';

	}
	else 
	{

		while (number > 0) 
		{

			buffer[index++] = HELPERS::PATTERN[number % newCountingSystem];
			number /= newCountingSystem;

		}

		buffer[index] = '\0';

		for (int i = 0; i < index / 2; i++)
		{

			std::swap(buffer[i], buffer[index - i - 1]);

		}
			
	}

	setStrNumber(buffer);
	countingSystem = newCountingSystem;

}

KBaseNumber::KBaseNumber(const char* strNumber, int countingSystem)
{

	setStrNumber(strNumber);
	setCountingSystem(countingSystem);
	setDecimalNumber();

}

KBaseNumber::KBaseNumber(const KBaseNumber& other)
{

	copyFrom(other);

}

KBaseNumber& KBaseNumber::operator = (const KBaseNumber& other)
{

	if (this != &other)
	{

		free();
		copyFrom(other);

	}

	return *this;

}

KBaseNumber::~KBaseNumber()
{

	free();

}

void KBaseNumber::update(const char* strNumber, int countingSystem)
{

	free();
	setStrNumber(strNumber);
	setCountingSystem(countingSystem);
	setDecimalNumber();

}

void KBaseNumber::print() const
{

	std::cout << strNumber << "(" << countingSystem << ")" << std::endl;

}

bool KBaseNumber::compareWith(const KBaseNumber& other) const
{

	return decimalNumber > other.decimalNumber;

}

void KBaseNumber::saveToFile(std::ofstream& file) const
{

	if (!file.is_open()) return;

	int sizeOfStrNumber = strlen(strNumber);

	file.write((const char*)&sizeOfStrNumber, sizeof(int));
	file.write((const char*)strNumber, sizeOfStrNumber);
	file.write((const char*)&countingSystem, sizeof(int));
	file.write((const char*)&decimalNumber, sizeof(int));

	file.close();

}

void KBaseNumber::saveToFile(const char* fileName) const
{

	if (!fileName) return;

	std::ofstream file(fileName, std::ios::binary);
	
	saveToFile(file);

}

void KBaseNumber::readFromFile(std::ifstream& file)
{

	if (!file.is_open()) return;

	free();
	int sizeOfStrNumber = 0;

	file.read((char*)&sizeOfStrNumber, sizeof(int));
	strNumber = new char[sizeOfStrNumber + 1];
	file.read((char*)strNumber, sizeOfStrNumber);
	strNumber[sizeOfStrNumber] = '\0';
	file.read((char*)&countingSystem, sizeof(int));
	file.read((char*)&decimalNumber, sizeof(int));
	
	file.close();

}

void KBaseNumber::readFromFile(const char* fileName)
{

	if (!fileName) return;

	std::ifstream file(fileName, std::ios::binary);
	
	readFromFile(file);

}

int HELPERS::charToDigit(char ch)
{

	if ('0' <= ch && ch <= '9') return ch - '0';
	if (ch >= 'A' && ch <= 'F') return 10 + (ch - 'A');
	if (ch >= 'a' && ch <= 'f') return ch - 'a' + 10;

	return -1;

}
