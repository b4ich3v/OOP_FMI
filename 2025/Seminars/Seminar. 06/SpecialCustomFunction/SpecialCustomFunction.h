#include <iostream>
#pragma once

typedef int (*predicate)(int);

class SpecialCustomFunction
{
private:

	predicate function = nullptr;
	int* specialNumbers = nullptr;
	int countOfNumbers = 0;

	mutable bool isOperatorForNegationCalled = false;

	void free();

	void copyFrom(const SpecialCustomFunction& other);

	void setFunction(predicate function);

	void incrementByOne();

	void decrementByOne();

	void setSpecialNumbers(int* specialNumbers, int countOfNumbers);

public:

	SpecialCustomFunction() = default;

	SpecialCustomFunction(predicate function, int* specialNumbers, int countOfNumbers);

	SpecialCustomFunction(const SpecialCustomFunction& other);

	SpecialCustomFunction& operator = (const SpecialCustomFunction& other);

	~SpecialCustomFunction();

	int operator () (int value) const;

	SpecialCustomFunction operator ++ (int dummyParam);

	SpecialCustomFunction& operator ++ ();

	SpecialCustomFunction operator -- (int dummyParam);

	SpecialCustomFunction& operator -- ();

	bool isSpecialNumber(int number) const;

	void negationOfSpecialNumbers();

	void printSpecialNumbers() const;

	friend SpecialCustomFunction operator ! (const SpecialCustomFunction& func);

};
