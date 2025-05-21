#include <iostream>

namespace HELPERS 
{
	
	const int MAX_COUNT_OF_ELEMENTS = 100;

	unsigned int naturalProgFunc(unsigned int start)
	{

		return start + 1;

	}

	unsigned int plusTenProgFunc(unsigned int start)
	{

		return start + 10;

	}

}

struct ProgressionResultFromOperations 
{
public:

	size_t index = 0;
	unsigned int output = 0;

	ProgressionResultFromOperations() = default;

	explicit ProgressionResultFromOperations(size_t index, unsigned int output):
		index(index), output(output) {}

};

typedef unsigned int (*predicate)(unsigned int);

class ArithmeticProgression
{
private:

	predicate function = nullptr;
	unsigned int firstTerm = 0;
	ProgressionResultFromOperations info[HELPERS::MAX_COUNT_OF_ELEMENTS];

	void evaluateFromDiff(unsigned int input1, unsigned int input2, size_t index, char operation)
	{

		if (index < 0 || index >= HELPERS::MAX_COUNT_OF_ELEMENTS) throw std::logic_error("Error");

		if (operation == '+') info[index] = ProgressionResultFromOperations(index, input1 + input2);
		else if (operation == '-') info[index] = ProgressionResultFromOperations(index, input1 - input2);
		else throw std::logic_error("Error");

	}

public:

	ArithmeticProgression(unsigned int firstTerm, predicate function) :
		firstTerm(firstTerm), function(function) {}

	ArithmeticProgression() :
		firstTerm(0), function(HELPERS::naturalProgFunc) {}

	ArithmeticProgression& operator += (const ArithmeticProgression& other)
	{
	
		unsigned int prev1 = firstTerm;
		unsigned int prev2 = other.firstTerm;

		for (int i = 0; i < HELPERS::MAX_COUNT_OF_ELEMENTS; i++)
		{

			unsigned int next1 = function(prev1);
			unsigned int next2 = other.function(prev2);

			evaluateFromDiff(next1, next2, i, '+');

			prev1 = next1;
			prev2 = next2;

		}

		this->function = nullptr;
		this->firstTerm += other.firstTerm;

		return *this;

	}

	ArithmeticProgression& operator -= (const ArithmeticProgression& other)
	{

		unsigned int prev1 = firstTerm;
		unsigned int prev2 = other.firstTerm;

		for (int i = 0; i < HELPERS::MAX_COUNT_OF_ELEMENTS; i++)
		{

			unsigned int next1 = function(prev1);
			unsigned int next2 = other.function(prev2);

			evaluateFromDiff(next1, next2, i, '-');

			prev1 = next1;
			prev2 = next2;

		}

		this->function = nullptr;
		this->firstTerm -= other.firstTerm;

		return *this;

	}

	void printArithmeticProgression(int iter) const
	{

		if (iter < 0 || iter >= HELPERS::MAX_COUNT_OF_ELEMENTS) throw std::logic_error("Error");

		if (function != nullptr)
		{

			unsigned int prev = firstTerm;

			for (int i = 0; i < iter; i++)
			{

				unsigned int next = function(prev);
				std::cout << prev << " ";
				prev = next;

			}

		}
		else
		{

			std::cout << firstTerm << " ";

			for (int i = 0; i < iter; i++)
			{

				std::cout << info[i].output << " ";

			}

		}

		std::cout << std::endl;

	}

};

int main() 
{

	ArithmeticProgression naturalProg;
	naturalProg.printArithmeticProgression(10);

	ArithmeticProgression plusTenProg(0, HELPERS::plusTenProgFunc);
	plusTenProg.printArithmeticProgression(10);

	naturalProg += plusTenProg;
	naturalProg.printArithmeticProgression(10);

	return 0;

}

