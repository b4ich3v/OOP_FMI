#include "SetByCriteria.h"

bool isPrime(int number) 
{

	for (int i = 2; i < number; i++)
	{

		if (number % i == 0) return false;

	}

	return true;

}

bool allTo(int number) 
{

	return true;

}

int main() 
{

	SetByCriteria s1(10, isPrime);
	SetByCriteria s2(47, allTo);
	s1.print();
	s2.print();

	return 0;

}


