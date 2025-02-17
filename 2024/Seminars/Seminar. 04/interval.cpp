#include <iostream>

class Interval
{
private:

	int start;
	int end;

	static bool isPrime(int number)
	{

		for (int i = 2; i < number; i++)
		{

			if (number % i == 0)
			{

				return false;

			}

		}

		return true;

	}

	static int countOfDigits(int number)
	{

		int size = 0;

		while (number != 0)
		{

			size++;
			number /= 10;

		}

		return size;

	}

	static bool isPalindrome(int number)
	{

		int size = countOfDigits(number);
		int* array = new int[size];

		for (int i = 0; i < size; i++)
		{

			array[size - i - 1] = number % 10;
			number /= 10;

		}

		for (int i = 0; i < size; i++)
		{

			if (array[size - i - 1] != array[i])
			{

				delete[] array;
				return false;

			}
		}

		delete[] array;
		return true;

	}

	static bool isPowerOfTwo(int number)
	{

		return number > 0 && (number & (number - 1)) == 0;

	}

	static bool withoutRepetitive(int number)
	{

		int size = countOfDigits(number);
		int* array = new int[size];

		for (int i = 0; i < size; i++)
		{

			array[size - i - 1] = number % 10;
			number /= 10;

		}

		for (int i = 0; i < size; i++)
		{


			for (int j = i + 1; j < size; j++)
			{

				if (array[i] == array[j])
				{

					delete[] array;
					return false;
					break;

				}

			}
			
		}

		delete[] array;
		return true;

	}

public:

	Interval() : start(0), end(0) {}

	Interval(const Interval& other)
	{

		this->start = other.end;
		this->end = other.end;

	}

	Interval(int a, int b)
	{

		if (a <= b)
		{

			std::swap(a, b);

		}

		this->start = a;
		this->end = b;

	}

	int getStart() const 
	{

		return start;

	}

	int getEnd() const
	{

		return end;

	}

	int distance() const 
	{

		return std::abs(end - start);

	}

	bool isInInterval(int number) 
	{

		return number >= start && number <= end;

	}

	int getPrimesCount() const 
	{

		int count = 0;

		for (int i = start; i < end; i++)
		{

			if (isPrime(i)) 
			{

				count++;

			}

		}

		return count;

	}

	int getWithoutRepetitiveCount() const
	{

		int count = 0;

		for (int i = start; i < end; i++)
		{

			if (withoutRepetitive(i))
			{

				count++;

			}

		}

		return count;

	}

	int getPalindromesCount() const
	{

		int count = 0;

		for (int i = start; i < end; i++)
		{

			if (isPalindrome(i))
			{

				count++;

			}

		}

		return count;

	}

	bool startAndEndArePowerOfTwo() const 
	{

		return (isPowerOfTwo(start) && isPowerOfTwo(end));

	}

};

Interval intersectIntervals(const Interval& first, const Interval& second)
{

	int newStart = std::max(first.getStart(), second.getStart());
	int newEnd = std::min(first.getEnd(), second.getEnd());

	if (newStart <= newEnd) 
	{

		return Interval(newStart, newEnd);

	}
	else
	{

		return Interval(0, 0); 

	}

}

int main() 
{

	Interval first(5, 15);
	Interval second(10, 20);

	Interval intersection = intersectIntervals(first, second);

	std::cout << "Intersection: [" << intersection.getStart() << ", " << intersection.getEnd() << "]" << std::endl;

	return 0;

}
