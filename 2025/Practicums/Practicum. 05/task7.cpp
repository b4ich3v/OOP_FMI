#include <iostream>
#include <fstream>
#include <cstdint>

namespace HELPERS
{

	const int BITS_IN_ONE_BYTE = 8;
	const int BITS_IN_TWO_BYTES = 16;

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

		uint16_t* newData = new uint16_t[newCapacity];

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
		data = new uint16_t[capacity];

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

		uint16_t twoBitsMask = data[currentBucket];
		(twoBitsMask >>= currentIndex) &= 0b11;

		return twoBitsMask;

	}

	void proccesTwoBits(int currentBucket, int currentIndex, int number, bool pred) 
	{

		uint16_t twoBitsMask = data[currentBucket];
		(twoBitsMask >>= currentIndex) &= 0b11;

		if (pred)
		{

			if (twoBitsMask == 0b00) twoBitsMask = 0b01;
			else if (twoBitsMask == 0b01) twoBitsMask = 0b10;
			else if (twoBitsMask == 0b10) twoBitsMask = 0b11;
			else return;

		}
		else
		{

			if (twoBitsMask == 0b11) twoBitsMask = 0b10;
			else if (twoBitsMask == 0b10) twoBitsMask = 0b01;
			else if (twoBitsMask == 0b01) twoBitsMask = 0b00;
			else return;

		}

		data[currentBucket] &= (~(0b11 << currentIndex));
		data[currentBucket] |= (twoBitsMask << currentIndex);

	}

	void addNumber(int number)
	{

		if (countOfNumber(number) == 3 || number < 0) return;

		int currentBucket = getBucket(number);
		int currentIndex = getIndex(number);
		maxNumber = std::max(maxNumber, number);

		while (currentBucket >= capacity) resize(capacity * 2);

		proccesTwoBits(currentBucket, currentIndex, number, true);
		size += 1;

	}

	void removeNumber(int number)
	{

		if (countOfNumber(number) == 0 || number < 0) return;

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

	ms1.removeNumber(1);
	ms1.removeNumber(4);
	ms1.removeNumber(4);
	ms1.removeNumber(1);
	ms1.print();

	ms1.addNumber(27);
	ms1.print();

	return 0;

}
