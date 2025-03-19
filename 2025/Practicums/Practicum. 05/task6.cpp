#include <iostream>
#include <fstream>
#include <cstdint>

namespace HELPERS
{

	const int BITS_IN_BYTE = 8;

}

class BitSet
{
private:

	uint8_t* data = nullptr;
	int size = 0;
	int capacity = 8;
	int maxNumber = 0;

	int getBucket(int number) const
	{

		return number / HELPERS::BITS_IN_BYTE;

	}

	int getIndex(int number) const
	{

		return number % HELPERS::BITS_IN_BYTE;

	}

	void copyFrom(const BitSet& other)
	{

		data = new uint8_t[other.capacity]{ 0 };
		size = other.size;
		maxNumber = other.maxNumber;
		capacity = other.capacity;

		for (int i = 0; i < size; i++)
		{

			data[i] = other.data[i];

		}

	}

	void free()
	{

		delete[] data;
		data = nullptr;
		size = 0;
		maxNumber = 0;
		capacity = 8;

	}

	void resize(int newCapacity)
	{

		if (newCapacity <= capacity) return;

		uint8_t* newData = new uint8_t[newCapacity]{ 0 };

		for (int i = 0; i < size; i++)
		{

			newData[i] = data[i];

		}

		delete[] data;
		data = newData;
		capacity = newCapacity;

	}

public:

	BitSet()
	{

		size = 0;
		capacity = 8;
		data = new uint8_t[capacity]{ 0 };

	}

	BitSet(int number)
	{

		size = 0;
		capacity = 8;
		data = new uint8_t[capacity]{ 0 };
		maxNumber = number;

		while (maxNumber >= capacity)
		{

			resize(capacity * 2);

		}

		addNumber(number);

	}

	BitSet(const BitSet& other)
	{

		copyFrom(other);

	}

	BitSet& operator = (const BitSet& other)
	{

		if (this != &other)
		{

			free();
			copyFrom(other);

		}

		return *this;

	}

	~BitSet()
	{

		free();

	}

	bool hasNumber(int number) const
	{

		int currentBucket = getBucket(number);
		int currentIndex = getIndex(number);

		return data[currentBucket] & (1 << currentIndex);

	}

	void addNumber(int number)
	{

		if (number < 0 || hasNumber(number)) return;
		if (size == capacity) resize(capacity * 2);

		int currentBucket = getBucket(number);
		int currentIndex = getIndex(number);

		data[currentBucket] |= (1 << currentIndex);
		maxNumber = std::max(maxNumber, number);
		size += 1;

	}

	void removeNumber(int number)
	{

		if (number < 0) return;
		if (!hasNumber(number)) return;

		int currentBucket = getBucket(number);
		int currentIndex = getIndex(number);

		data[currentBucket] &= (~(1 << currentIndex));
		size -= 1;

	}

	void print() const
	{

		for (int i = 0; i <= maxNumber; i++)
		{

			if (hasNumber(i))
			{

				std::cout << i << " ";

			}

		}

		std::cout << std::endl;

	}

	BitSet getUnion(const BitSet& other) const
	{

		int newMaxNumber = std::max(maxNumber, other.maxNumber);
		BitSet result(maxNumber);

		for (int i = 0; i <= maxNumber; i++)
		{

			if (hasNumber(i)) result.addNumber(i);
			

		}

		for (int i = 0; i <= other.maxNumber; i++)
		{

			if (other.hasNumber(i)) result.addNumber(i);

		}

		return result;

	}

	BitSet getIntersection(const BitSet& other) const
	{

		int newMaxNumber = std::min(maxNumber, other.maxNumber);
		BitSet result(newMaxNumber);

		for (int i = 0; i <= newMaxNumber; i++)
		{

			if (hasNumber(i) && other.hasNumber(i)) result.addNumber(i);

		}

		result.removeNumber(newMaxNumber);
		return result;

	}

};

int main()
{

	BitSet s1(5);
	BitSet s2(17);
	
	s1.addNumber(3);
	s1.addNumber(5);
	s1.addNumber(1);

	s2.addNumber(25);
	s2.addNumber(52);
	s2.addNumber(63);
	s2.addNumber(3);

	BitSet unionOfTwo = s1.getUnion(s2);
	unionOfTwo.print();

	BitSet intersecitonOfTwo = s1.getIntersection(s2);
	intersecitonOfTwo.print();

	return 0;

}
