#include "SpecialCustomFunction.h"

SpecialCustomFunction::SpecialCustomFunction(const SpecialCustomFunction& other) 
{

	copyFrom(other);

}

SpecialCustomFunction::SpecialCustomFunction(predicate function, int* specialNumbers, int countOfNumbers) 
{

	setFunction(function);
	setSpecialNumbers(specialNumbers, countOfNumbers);
	this->isOperatorForNegationCalled = false;

}

SpecialCustomFunction& SpecialCustomFunction::operator = (const SpecialCustomFunction& other) 
{

	if (this != &other)
	{

		free();
		copyFrom(other);

	}

	return *this;

}

SpecialCustomFunction::~SpecialCustomFunction() 
{

	free();

}

void SpecialCustomFunction::incrementByOne()
{

	for (int i = 0; i < countOfNumbers; i++)
	{

		specialNumbers[i] += 1;

	}

}

void SpecialCustomFunction::decrementByOne()
{

	for (int i = 0; i < countOfNumbers; i++)
	{

		specialNumbers[i] -= 1;

	}

}

void SpecialCustomFunction::free() 
{

	delete[] specialNumbers;
	specialNumbers = nullptr;
	function = nullptr;
	countOfNumbers = 0;
	isOperatorForNegationCalled = false;

}

void SpecialCustomFunction::printSpecialNumbers() const 
{

	for (int i = 0; i < countOfNumbers; i++)
	{

		std::cout << specialNumbers[i] << " ";

	}

	std::cout << std::endl;

}

void SpecialCustomFunction::negationOfSpecialNumbers() 
{

	if (isOperatorForNegationCalled) 
	{

		for (int i = 0; i < countOfNumbers; i++)
		{

			specialNumbers[i] = -specialNumbers[i];

		}

	}

}

void SpecialCustomFunction::copyFrom(const SpecialCustomFunction& other) 
{

	delete[] this->specialNumbers;
	this->specialNumbers = new int[other.countOfNumbers];

	for (int i = 0; i < other.countOfNumbers; i++)
	{

		this->specialNumbers[i] = other.specialNumbers[i];

	}

	this->countOfNumbers = other.countOfNumbers;
	this->function = other.function;
	this->isOperatorForNegationCalled = other.isOperatorForNegationCalled;

}

void SpecialCustomFunction::setFunction(predicate function)
{

	this->function = function;

}

void SpecialCustomFunction::setSpecialNumbers(int* specialNumbers, int countOfNumbers) 
{

	if (!specialNumbers || specialNumbers == this->specialNumbers || countOfNumbers < 0) return;

	delete[] this->specialNumbers;
	this->specialNumbers = new int[countOfNumbers];

	for (int i = 0; i < countOfNumbers; i++)
	{

		this->specialNumbers[i] = specialNumbers[i];

	}

	this->countOfNumbers = countOfNumbers;

}

bool SpecialCustomFunction::isSpecialNumber(int number) const
{

	for (int i = 0; i < countOfNumbers; i++)
	{

		if (specialNumbers[i] == number) return true;

	}

	return false;

}

int SpecialCustomFunction::operator () (int number) const
{

	if (isSpecialNumber(number)) return number * number;
	else return function(number);

}

SpecialCustomFunction& SpecialCustomFunction::operator ++ () 
{

	incrementByOne();

	return *this;

}

SpecialCustomFunction SpecialCustomFunction::operator ++ (int dummyParam) 
{

	SpecialCustomFunction old(*this);
	incrementByOne();

	return old;

}

SpecialCustomFunction& SpecialCustomFunction::operator -- () 
{

	decrementByOne();

	return *this;

}

SpecialCustomFunction SpecialCustomFunction::operator -- (int dummy)
{

	SpecialCustomFunction old(*this);
	decrementByOne();

	return old;

}

SpecialCustomFunction operator ! (const SpecialCustomFunction& func) 
{

	SpecialCustomFunction result(func);
	result.isOperatorForNegationCalled = true;
	result.negationOfSpecialNumbers();
	result.isOperatorForNegationCalled = false;

	return result;

}
