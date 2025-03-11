#include <iostream>
#include <fstream>
#include <cstring>

namespace CONSTANTS
{

	const int DEFAULT_CAPACITY = 8;
	const int COUNT_OF_BITS_IN_BUCKET = 8;

}

class Set
{
private:

	char* positiveNumbers = nullptr;
	char* negativeNumbers = nullptr;
	int capacity;
	int size;
	int maxNumber;

	int getBucket(int number) const
	{

		return number / CONSTANTS::COUNT_OF_BITS_IN_BUCKET;

	}

	int getIndex(int number) const
	{

		return number % CONSTANTS::COUNT_OF_BITS_IN_BUCKET;

	}

	bool addNumberPositive(int number)
	{

		if (hasNumberPositive(number)) return false;

		if (size == capacity) resize(capacity * 2);
		maxNumber = std::max(maxNumber, number);
		if (maxNumber > capacity) resize(maxNumber);

		int bucket = getBucket(number);
		int index = getIndex(number);

		positiveNumbers[bucket] |= (1 << index);
		size += 1;
		return true;

	}

	bool addNumberNegative(int number)
	{

		if (hasNumberNegative(number)) return false;

		if (size == capacity) resize(capacity * 2);
		maxNumber = std::max(maxNumber, std::abs(number));
		if (maxNumber > capacity) resize(maxNumber);

		int bucket = getBucket(std::abs(number));
		int index = getIndex(std::abs(number));

		negativeNumbers[bucket] |= (1 << index);
		size += 1;
		return true;

	}

	bool removeNumberPositive(int number)
	{

		if (size == 0) return false;

		int bucket = getBucket(number);
		int index = getIndex(number);

		positiveNumbers[bucket] &= ~(1 << index);
		size -= 1;
		return true;

	}

	bool removeNumberNegative(int number)
	{

		if (size == 0) return false;

		int bucket = getBucket(std::abs(number));
		int index = getIndex(std::abs(number));

		negativeNumbers[bucket] &= ~(1 << index);
		size -= 1;
		return true;

	}

	void resize(int newCapacity)
	{

		if (newCapacity <= capacity) return;

		char* newDataPos = new char[newCapacity]();
		char* newDataNeg = new char[newCapacity]();

		memcpy(newDataPos, positiveNumbers, capacity);
		memcpy(newDataNeg, negativeNumbers, capacity);

		delete[] positiveNumbers;
		delete[] negativeNumbers;

		positiveNumbers = newDataPos;
		negativeNumbers = newDataNeg;

		capacity = newCapacity;

	}

	void copyFrom(const Set& other)
	{

		size = other.size;
		capacity = other.capacity;
		maxNumber = other.maxNumber;

		char* newDataPos = new char[other.capacity] {0};
		char* newDataNeg = new char[other.capacity] {0};

		memcpy(newDataPos, other.positiveNumbers, capacity);
		memcpy(newDataNeg, other.negativeNumbers, capacity);

		delete[] positiveNumbers;
		delete[] negativeNumbers;
		positiveNumbers = newDataPos;
		negativeNumbers = newDataNeg;

	}

	void moveTo(Set&& other) 
	{

		positiveNumbers = other.positiveNumbers;
		negativeNumbers = other.negativeNumbers;
		size = other.size;
		capacity = other.capacity;
		maxNumber = other.maxNumber;

		other.positiveNumbers = nullptr;
		other.negativeNumbers = nullptr;
		other.capacity = CONSTANTS::DEFAULT_CAPACITY;
		other.size = 0;
		other.maxNumber = 0;

	}

	void free()
	{

		delete[] positiveNumbers;
		delete[] negativeNumbers;
		positiveNumbers = nullptr;
		negativeNumbers = nullptr;
		size = 0;
		capacity = CONSTANTS::DEFAULT_CAPACITY;

	}

public:

	Set()
	{

		size = 0;
		maxNumber = 0;

		capacity = CONSTANTS::DEFAULT_CAPACITY;
		positiveNumbers = new char[capacity] {0};
		negativeNumbers = new char[capacity] {0};

	}

	Set(const Set& other)
	{

		copyFrom(other);

	}

	Set(Set&& other) noexcept
	{

		moveTo(std::move(other));

	}

	Set& operator = (const Set& other)
	{

		if (this != &other)
		{

			free();
			copyFrom(other);

		}

		return *this;

	}

	Set& operator = (Set&& other) noexcept 
	{

		if (this != &other)
		{

			free();
			moveTo(std::move(other));

		}

		return *this;

	}

	~Set()
	{

		free();

	}

	void serialize(std::ofstream& file) 
	{

		if (!file.is_open()) return;

		file.write((const char*)&capacity, sizeof(int));
		file.write((const char*)&size, sizeof(int));
		file.write((const char*)&maxNumber, sizeof(int));
		
		file.write((const char*)positiveNumbers, capacity * sizeof(char));
		file.write((const char*)negativeNumbers, capacity * sizeof(char));

		file.close();

	}

	void deserialize(std::ifstream& file)
	{

		if (!file.is_open()) return;

		free(); 

		file.read((char*)&capacity, sizeof(int));
		file.read((char*)&size, sizeof(int));
		file.read((char*)&maxNumber, sizeof(int));

		positiveNumbers = new char[capacity]();
		negativeNumbers = new char[capacity]();

		file.read((char*)positiveNumbers, capacity * sizeof(char));
		file.read((char*)negativeNumbers, capacity * sizeof(char));

	}

	bool hasNumberPositive(int number) const
	{

		if (number > maxNumber || number < 0) return false;

		int bucket = getBucket(number);
		int index = getIndex(number);

		return (positiveNumbers[bucket] & (1 << index)) != 0;

	}

	bool hasNumberNegative(int number) const
	{

		if (std::abs(number) > maxNumber || number >= 0) return false;

		int bucket = getBucket(std::abs(number));
		int index = getIndex(std::abs(number));

		return (negativeNumbers[bucket] & (1 << index)) != 0;

	}

	void printSet() const
	{

		std::cout << "{ ";

		for (int i = 0; i <= maxNumber; i++)
		{

			if (hasNumberPositive(i)) std::cout << i << " ";
			if (hasNumberNegative(-i)) std::cout << -i << " ";

		}

		std::cout << "}" << std::endl;

	}

	bool addNumber(int number)
	{

		if (number >= 0) return addNumberPositive(number);
		else return addNumberNegative(number);

	}

	bool removeNumber(int number)
	{

		if (number >= 0) return removeNumberPositive(number);
		else return removeNumberNegative(number);

	}

	void precalculateSize() 
	{

		int newSize = 0;

		for (int i = 0; i <= maxNumber; i++)
		{

			if (hasNumberPositive(i)) newSize += 1;
			if (hasNumberNegative(-i)) newSize += 1;

		}

		size = newSize;

	}

	int getSize() const
	{

		return size;

	}

	int getCapacity() const
	{

		return capacity;

	}

	int getMaxNumber() const
	{

		return maxNumber;

	}

	void setUnion(const Set& other)
	{

		int newCapacity = std::max(capacity, other.getCapacity());
		if (newCapacity > capacity) resize(newCapacity);

		maxNumber = std::max(maxNumber, other.getMaxNumber());

		int minBuckets = std::min(capacity, other.getCapacity()) / CONSTANTS::COUNT_OF_BITS_IN_BUCKET;

		for (int i = 0; i < minBuckets; i++)
		{

			positiveNumbers[i] |= other.positiveNumbers[i];
			negativeNumbers[i] |= other.negativeNumbers[i];

		}

		if (other.getCapacity() > capacity)
		{

			memcpy(positiveNumbers + minBuckets, other.positiveNumbers + minBuckets, (other.getCapacity() - minBuckets) * sizeof(char));
			memcpy(negativeNumbers + minBuckets, other.negativeNumbers + minBuckets, (other.getCapacity() - minBuckets) * sizeof(char));

		}

		precalculateSize();

	}

	void setIntersection(const Set& other)
	{

		int minBuckets = std::min((maxNumber / CONSTANTS::COUNT_OF_BITS_IN_BUCKET) + 1,
			(other.getMaxNumber() / CONSTANTS::COUNT_OF_BITS_IN_BUCKET) + 1);

		for (int i = 0; i < minBuckets; i++)
		{

			positiveNumbers[i] &= other.positiveNumbers[i];
			negativeNumbers[i] &= other.negativeNumbers[i];

		}

		for (int i = minBuckets; i < (maxNumber / CONSTANTS::COUNT_OF_BITS_IN_BUCKET) + 1; i++)
		{

			positiveNumbers[i] = 0;
			negativeNumbers[i] = 0;

		}

		precalculateSize();

	}

};

int main()
{

	std::ofstream file("../file.dat", std::ios::binary);

	Set s1;
	s1.addNumber(4);
	s1.addNumber(3);
	s1.addNumber(5);
	s1.addNumber(1);
	s1.addNumber(-1);
	s1.addNumber(-125);
	s1.printSet();

	s1.removeNumber(3);
	s1.removeNumber(4);
	s1.removeNumber(-1);
	s1.printSet();

	s1.serialize(file);

	Set s2;
	s2.addNumber(4);
	s2.addNumber(15);
	s2.addNumber(-3);
	s2.printSet();

	s1.setUnion(s2);
	s1.printSet();

	s2.setIntersection(s1);
	s2.printSet();

	return 0;

}
