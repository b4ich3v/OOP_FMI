#include "Interval.h"

size_t HELPERS::getCountOfDigits(int number)
{

	size_t counter = 0;

	while (number)
	{

		counter += 1;
		number /= 10;

	}

	return counter;

}

bool HELPERS::isPrime(int number) 
{

	for (int i = 2; i < number; i++)
	{

		if (!(number % i)) return false;

	}

	return true;

}

bool HELPERS::hasDiffDigits(int number) 
{

	int digitsCounter[9]{ 0 };

	while (number)
	{

		int currentDigit = number % 10;
		digitsCounter[currentDigit] += 1;
		number /= 10;

	}

	for (int i = 0; i < 9; i++)
	{

		if (digitsCounter[i] > 1) return false;

	}

	return true;

}

bool HELPERS::isPalindrome(int number)
{

	int size = getCountOfDigits(number);
	int* array = new int[size];

	for (int i = 0; i < size; i++)
	{

		array[i] = number % 10;
		number /= 10;

	}

	for (int i = 0; i < size / 2; i++)
	{

		if (array[i] != array[size - i - 1]) return false;

	}

	delete[] array;
	return true;

}

size_t HELPERS::getCountByCondition(int start, int end, predicate func) 
{

	size_t counter = 0;

	for (int i = start; i <= end; i++)
	{

		if (func(i)) counter += 1;

	}

	return counter;

}

void Interval::setStart(int start) 
{

	this->start = start;

}

void Interval::setEnd(int end)
{

	this->end = end;

}

Interval::Interval()
{

	setStart(0);
	setEnd(0);

}

Interval::Interval(int start, int end) 
{

	if (start <= end)
	{

		setStart(start);
		setEnd(end);

	}
	else
	{

		setStart(0);
		setEnd(0);

	}

}

bool Interval::isInInterval(int number) const 
{

	return number >= start && number <= end;

}

size_t Interval::getLen() const
{

	return std::abs(end - start);

}

size_t Interval::countOfPrimesInInterval() const 
{

	return HELPERS::getCountByCondition(start, end, HELPERS::isPrime);

}

size_t Interval::countOfNumbersWDDInInterval() const 
{

	return HELPERS::getCountByCondition(start, end, HELPERS::hasDiffDigits);

}

size_t Interval::countOfPalindromesInInterval() const 
{

	return HELPERS::getCountByCondition(start, end, HELPERS::isPalindrome);

}

bool Interval::areStartAndEndAPOT() const 
{

	int mask = 0b1;
	uint8_t bits = 0b0;

	for (int i = 0; i < 32; i++)
	{

		if (start & (~(mask << i))) bits |= (mask << 0);
		if (end & (~(mask << i))) bits |= (mask << 1);

	}

	return bits == 0b11;

}

Interval& Interval::operator & (const Interval& other) 
{

	this->start = std::max(this->start, other.start);
	this->end = std::min(this->end, other.end);

}

bool Interval::isSubinterval(const Interval& other) const
{

	return other.start >= this->start && other.end <= this->end;

}

void Interval::print() const
{

	std::cout << start << " " << end << std::endl;

}
