#include "BitSet.h"

BitSet::BitSet() 
{

	size = 0;
	capacity = 8;
	data = new uint8_t[capacity]{ 0 };

}

BitSet::BitSet(int maxNumber) 
{

	if (maxNumber < 0) throw std::logic_error("Error");

	int byteCount = (maxNumber + CONSTANTS::countOfBitsInOneByte - 1) / CONSTANTS::countOfBitsInOneByte;
	capacity = byteCount;
	data = new uint8_t[capacity]{ 0 };

}

BitSet::BitSet(const BitSet& other) 
{

	copyFrom(other);

}

BitSet::BitSet(BitSet&& other) noexcept
{

	moveTo(std::move(other));

}

BitSet& BitSet::operator = (const BitSet& other)
{

	if (this != &other) 
	{

		free();
		copyFrom(other);

	}

	return *this;

}

BitSet& BitSet::operator = (BitSet&& other) noexcept
{

	if (this != &other)
	{

		free();
		moveTo(std::move(other));

	}

	return *this;

}

BitSet::~BitSet() 
{

	free();

}

void BitSet::resize(int newCapacity) 
{

	if (newCapacity <= capacity) throw std::logic_error("Error");

	uint8_t* newData = new uint8_t[newCapacity]{ 0 };

	for (int i = 0; i < capacity; i++)
	{

		newData[i] = data[i];

	}

	delete[] data;
	data = newData;
	capacity = newCapacity;

}

void BitSet::free() 
{

	delete[] data;
	data = nullptr;
	size = 0;
	capacity = 8;

}

void BitSet::copyFrom(const BitSet& other) 
{

	data = new uint8_t[other.capacity]{ 0 };
	size = other.size;
	capacity = other.capacity;

	for (int i = 0; i < capacity; i++)
	{

		data[i] = other.data[i];

	}

}

void BitSet::moveTo(BitSet&& other) 
{

	data = other.data;
	size = other.size;
	capacity = other.capacity;

	other.data = nullptr;
	other.size = 0;
	other.capacity = 8;

}

int BitSet::getBucketIndex(int number) const 
{

	return number / CONSTANTS::countOfBitsInOneByte;

}

int BitSet::indexInBucket(int number) const 
{

	return number % CONSTANTS::countOfBitsInOneByte;

}

bool BitSet::hasNumber(int number) const 
{

	if (number < 0) throw std::logic_error("Error");

	int bucket = getBucketIndex(number);
	int index = indexInBucket(number);

	if (bucket >= capacity) return false;

	return (data[bucket] & (1 << index)) != 0;

}

void BitSet::addNumber(int number) 
{

	if (number < 0) throw std::logic_error("Error");
	if (hasNumber(number)) return;

	int bucket = getBucketIndex(number);
	int index = indexInBucket(number);

	while (bucket >= capacity) resize(capacity * 2);

	data[bucket] |= (1 << index);
	size += 1;

}

void BitSet::removeNumber(int number) 
{

	if (number < 0) throw std::logic_error("Error");
	if (!hasNumber(number)) return;

	int bucket = getBucketIndex(number);
	int index = indexInBucket(number);

	data[bucket] &= (~(1 << index));
	size -= 1;

}

BitSet& BitSet::operator &= (const BitSet& other)
{

	int totalBits = std::min(capacity, other.capacity) * CONSTANTS::countOfBitsInOneByte;
	BitSet result(totalBits);  

	for (int i = 0; i < totalBits; i++)
	{

		if (hasNumber(i) && other.hasNumber(i)) result.addNumber(i);
			
	}

	*this = result;
	return *this;

}

BitSet& BitSet::operator |= (const BitSet& other)
{

	int totalBits = std::max(capacity, other.capacity) * CONSTANTS::countOfBitsInOneByte;
	BitSet result(totalBits);

	for (int i = 0; i < totalBits; i++)
	{

		if (hasNumber(i) || other.hasNumber(i)) result.addNumber(i);	

	}

	*this = result;
	return *this;

}

BitSet operator & (const BitSet& s1, const BitSet& s2) 
{

	BitSet result(s1);
	result &= s2;

	return result;

}

BitSet operator | (const BitSet& s1, const BitSet& s2) 
{

	BitSet result(s1);
	result |= s2;

	return result;

}

void BitSet::printSet() const 
{

	for (int i = 0; i < capacity * CONSTANTS::countOfBitsInOneByte; i++)
	{

		if (hasNumber(i)) std::cout << i << " ";
 
	}

	std::cout << std::endl;

}

void BitSet::removeAllNumbers() 
{

	for (int i = 0; i < capacity * CONSTANTS::countOfBitsInOneByte; i++)
	{

		removeNumber(i);

	}

}
