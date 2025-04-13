#include "SetByCriteria.h"

SetByCriteria::SetByCriteria(int number, predicate func): BitSet(number) 
{

	funciton = func;
	fillSet(number);

}

bool SetByCriteria::hasCurrentNumber(int number) const
{

	return hasNumber(number);

}

void SetByCriteria::print() const 
{

	printSet();

}

void SetByCriteria::fillSet(int bound) 
{

	for (int i = 0; i <= bound; i++)
	{

		if (funciton(i)) addNumber(i);

	}

}
