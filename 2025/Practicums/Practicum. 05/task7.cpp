#include <iostream>
#include <fstream>
#include <cstdint>

namespace HELPERS
{

	const int BITS_IN_ONE_BYTE = 8;
	const int MAX_COUNT_EQUAL_NUMBERS = 3;
	const int MIN_COUNT_EQUAL_NUMBERS = 0;

	const int TWO_BITS_MASKS[4] = { 0b00, 0b01, 0b10, 0b11 };

}

class MultiSetLessThanТhree
{
private:

	uint16_t* data = nullptr;
	int size = 0;
	int capacity = 8;
	int maxNumber = 0;

	int getBucket(int number) const
	{

		return number / HELPERS::BITS_IN_ONE_BYTE;

	}

	int getIndex(int number) const
	{

		return (number % HELPERS::BITS_IN_ONE_BYTE) * 2;

	}

	void resize(int newCapacity)
	{

		if (newCapacity <= capacity) return;

		uint16_t* newData = new uint16_t[newCapacity]{ 0 };

		for (int i = 0; i < capacity; i++)
		{

			newData[i] = data[i];

		}

		delete[] data;
		data = newData;
		capacity = newCapacity;

	}

	void free()
	{

		delete[] data;
		data = nullptr;
		capacity = 8;
		size = 0;
		maxNumber = 0;

	}

	void copyFrom(const MultiSetLessThanТhree& other)
	{

		data = new uint16_t[other.capacity];

		for (int i = 0; i < other.capacity; i++)
		{

			data[i] = other.data[i];

		}

		capacity = other.capacity;
		size = other.size;
		maxNumber = other.maxNumber;

	}

public:

	MultiSetLessThanТhree()
	{

		maxNumber = 0;
		size = 0;
		capacity = 8;
		maxNumber = 0;
		data = new uint16_t[capacity]{ 0 };

	}

	MultiSetLessThanТhree(int number)
	{

		capacity = 8;
		size = 0;
		maxNumber = number;
		data = new uint16_t[capacity]{ 0 };

		while (maxNumber >= capacity) resize(capacity * 2);

		addNumber(number);

	}

	MultiSetLessThanТhree(const MultiSetLessThanТhree& other)
	{

		copyFrom(other);

	}

	MultiSetLessThanТhree& operator = (const MultiSetLessThanТhree& other)
	{

		if (this != &other)
		{

			free();
			copyFrom(other);

		}

		return *this;

	}

	~MultiSetLessThanТhree()
	{

		free();

	}

	int countOfNumber(int number) const
	{

		int currentBucket = getBucket(number);
		int currentIndex = getIndex(number);

		if (currentBucket >= capacity) return 0;

		return (data[currentBucket] >> currentIndex) & HELPERS::TWO_BITS_MASKS[3];

	}

	void proccesTwoBits(int currentBucket, int currentIndex, int number, bool pred)
	{

		uint16_t twoBitsMask = data[currentBucket];
		(twoBitsMask >>= currentIndex) &= HELPERS::TWO_BITS_MASKS[3];

		if (pred)
		{

			if (twoBitsMask == HELPERS::TWO_BITS_MASKS[0]) twoBitsMask = HELPERS::TWO_BITS_MASKS[1];
			else if (twoBitsMask == HELPERS::TWO_BITS_MASKS[1]) twoBitsMask = HELPERS::TWO_BITS_MASKS[2];
			else if (twoBitsMask == HELPERS::TWO_BITS_MASKS[2]) twoBitsMask = HELPERS::TWO_BITS_MASKS[3];
			else return;

		}
		else
		{

			if (twoBitsMask == HELPERS::TWO_BITS_MASKS[3]) twoBitsMask = HELPERS::TWO_BITS_MASKS[2];
			else if (twoBitsMask == HELPERS::TWO_BITS_MASKS[2]) twoBitsMask = HELPERS::TWO_BITS_MASKS[1];
			else if (twoBitsMask == HELPERS::TWO_BITS_MASKS[1]) twoBitsMask = HELPERS::TWO_BITS_MASKS[0];
			else return;

		}

		data[currentBucket] &= (~(HELPERS::TWO_BITS_MASKS[3] << currentIndex));
		data[currentBucket] |= (twoBitsMask << currentIndex);

	}

	void addNumber(int number)
	{

		if (countOfNumber(number) == HELPERS::MAX_COUNT_EQUAL_NUMBERS || number < 0) return;

		int currentBucket = getBucket(number);
		int currentIndex = getIndex(number);
		maxNumber = std::max(maxNumber, number);

		while (currentBucket >= capacity) resize(capacity * 2);

		proccesTwoBits(currentBucket, currentIndex, number, true);
		size += 1;

	}

	void removeNumber(int number)
	{

		if (countOfNumber(number) == HELPERS::MIN_COUNT_EQUAL_NUMBERS || number < 0) return;

		int currentBucket = getBucket(number);
		int currentIndex = getIndex(number);

		proccesTwoBits(currentBucket, currentIndex, number, false);
		size -= 1;

	}

	void print() const
	{

		for (int i = 0; i <= maxNumber; i++)
		{

			int currentNumberCount = countOfNumber(i);

			for (int j = 0; j < currentNumberCount; j++)
			{

				std::cout << i << " ";

			}

		}

		std::cout << std::endl;

	}

	MultiSetLessThanТhree getIntersection(const MultiSetLessThanТhree& other)
	{

		MultiSetLessThanТhree result;
		int newMaxNumber = std::min(maxNumber, other.maxNumber);

		for (int i = 0; i <= newMaxNumber; i++)
		{

			int currentNumberCount1 = countOfNumber(i);
			int currentNumberCount2 = other.countOfNumber(i);
			int sizeForInnerCycle = std::min(currentNumberCount1, currentNumberCount2);

			for (int j = 0; j < sizeForInnerCycle; j++)
			{

				result.addNumber(i);

			}

		}

		return result;

	}

	MultiSetLessThanТhree getUnion(const MultiSetLessThanТhree& other)
	{

		MultiSetLessThanТhree result;
		int newMaxNumber = std::max(maxNumber, other.maxNumber);

		for (int i = 0; i <= newMaxNumber; i++)
		{

			int currentNumberCount1 = countOfNumber(i);
			int currentNumberCount2 = other.countOfNumber(i);
			int sizeForInnerCycle = std::min(currentNumberCount1 + currentNumberCount2, HELPERS::MAX_COUNT_EQUAL_NUMBERS);

			for (int j = 0; j < sizeForInnerCycle; j++)
			{

				result.addNumber(i);

			}

		}

		return result;

	}

};

int main()
{

	MultiSetLessThanТhree ms1;
	ms1.addNumber(1);
	ms1.addNumber(1);
	ms1.addNumber(1);
	ms1.addNumber(4);
	ms1.addNumber(5);
	ms1.addNumber(5);
	ms1.addNumber(2);
	ms1.print();
	std::cout << std::endl;

	ms1.removeNumber(1);
	ms1.removeNumber(4);
	ms1.removeNumber(4);
	ms1.removeNumber(1);
	ms1.addNumber(27);
	ms1.print();

	MultiSetLessThanТhree ms2;
	ms2.addNumber(1);
	ms2.addNumber(1);
	ms2.addNumber(125);
	ms2.addNumber(14);
	ms2.addNumber(5);
	ms2.addNumber(1);
	ms2.print();
	std::cout << std::endl;

	MultiSetLessThanТhree intersectionOfTwo = ms1.getIntersection(ms2);
	MultiSetLessThanТhree unionOfTwo = ms1.getUnion(ms2);
	intersectionOfTwo.print();
	unionOfTwo.print();

	return 0;

}
