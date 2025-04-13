#include <iostream>
#include <utility>
#pragma once

namespace CONSTANTS 
{

	const int countOfBitsInOneByte = 8;

}

class BitSet
{
private:

	uint8_t* data = nullptr;
	int size = 0;
	int capacity = 8;

	void resize(int newCapacity);

	void free();

	void copyFrom(const BitSet& other);

	void moveTo(BitSet&& other);

	int getBucketIndex(int number) const;

	int indexInBucket(int number) const;

public:

	BitSet();

	BitSet(int maxNumber);

	BitSet(const BitSet& other);

	BitSet& operator = (const BitSet& other);

	BitSet(BitSet&& other) noexcept;

	BitSet& operator = (BitSet&& other) noexcept;

	~BitSet();

	BitSet& operator &= (const BitSet& other);

	BitSet& operator |= (const BitSet& other);

	void addNumber(int number);

	void removeNumber(int number);

	bool hasNumber(int number) const;
	
	void removeAllNumbers();

	void printSet() const;

};

BitSet operator & (const BitSet& s1, const BitSet& s2);

BitSet operator | (const BitSet& s1, const BitSet& s2);
