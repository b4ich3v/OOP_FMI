#include "SetByString.h"

void SetByString::fillSet(const MyString& str) 
{

	const char* strData = str.getData();

	for (int i = 0; i < str.getSize(); i++)
	{

		if (strData[i] == ' ') continue;
		if (!isDigit(strData[i])) throw std::logic_error("Error");

	}

	std::stringstream ss(strData);
	int currentNumber = 0;

	while (!ss.eof())
	{

		ss >> currentNumber;
		addNumber(currentNumber);

	}

	this->str = str;

}

SetByString::SetByString(int number, const MyString& str): BitSet(number)
{

	fillSet(str);

}

bool SetByString::hasCurrentNumber(int number) const 
{

	return hasNumber(number);

}

void SetByString::setAt(int index, char newSym) 
{

	if (index < 0 || index >= str.getSize()) throw std::logic_error("Error");
	str[index] = newSym;

	removeAllNumbers();
	fillSet(str);

}

void SetByString::print() const 
{

	printSet();

}

bool isDigit(char ch) 
{

	return ch >= '0' && ch <= '9';

}
