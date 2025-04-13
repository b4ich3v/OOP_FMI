#include "BitSet.h"
#include "MyString.h"
#include <sstream>
#pragma once

bool isDigit(char ch);

class SetByString: private BitSet
{
private:

	MyString str;

	void fillSet(const MyString& str);

public:

	SetByString(int number, const MyString& str);

	bool hasCurrentNumber(int number) const;

	void setAt(int index, char newSym);

	void print() const;

};

