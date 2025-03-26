#include <iostream>

class ArithmeticProgression 
{
private:

	int first = 0;
	int diff = 1;

public:

	ArithmeticProgression() = default;

	ArithmeticProgression(int first, int diff)
	{

		this->first = first;
		this->diff = diff;

	}

	ArithmeticProgression(const ArithmeticProgression& other) 
	{

		this->first = other.first;
		this->diff = other.diff;

	}

	ArithmeticProgression& operator += (const ArithmeticProgression& other) 
	{

		this->first += other.first;
		this->diff += other.diff;

		return *this;

	}

	ArithmeticProgression& operator -= (const ArithmeticProgression& other)
	{

		this->first -= other.first;
		this->diff -= other.diff;

		return *this;

	}

	ArithmeticProgression& operator &= (unsigned int number)
	{

		first += number * first;

		return *this;

	}

	int operator [] (int index) const
	{

		if (index < 0) throw std::logic_error("Error");

		return first + (index - 1) * diff;

	}

	int operator () (unsigned int number) const 
	{

		return number * (2 * first + (number - 1) * diff) / 2;

	}

	void printToNTerm(int number) const 
	{

		if (number < 0) throw std::logic_error("Error");

		for (int i = 1; i <= number; i++)
		{

			std::cout << (*this)[i] << " ";

		}

		std::cout << std::endl;

	}

};

ArithmeticProgression operator & (const ArithmeticProgression& ap, unsigned int number)
{

	ArithmeticProgression result(ap);
	result &= number;

	return result;

}

ArithmeticProgression operator & (unsigned int number, const ArithmeticProgression& ap)
{

	ArithmeticProgression result(ap);
	result &= number;

	return result;

}

ArithmeticProgression operator + (const ArithmeticProgression& left, const ArithmeticProgression& right) 
{

	ArithmeticProgression result(left);
	result += right;

	return result;

}

ArithmeticProgression operator - (const ArithmeticProgression& left, const ArithmeticProgression& right)
{

	ArithmeticProgression result(left);
	result -= right;

	return result;

}

int main() 
{

	ArithmeticProgression ap1(3, 3);
	ArithmeticProgression ap2(1, 2);
	ArithmeticProgression ap3(-1, 0);

	ap1.printToNTerm(10);
	std::cout << ap1(3) << std::endl;
	std::cout << ap1[3] << std::endl;

	ap1 += ap2;
	ap1.printToNTerm(10);

	ArithmeticProgression diff = ap2 - ap3;
	diff.printToNTerm(5);

	return 0;
	
}
