#include "WrapperInt.h"
#pragma once

class DynamicArrayOfPointers
{
private:

	WrapperInt** arrayOfInts = nullptr;
	int countOfInts = 0;
	int capacity = 8;

	void resize(int newCapacity);

	void copyFrom(const DynamicArrayOfPointers& other);

	void moveTo(DynamicArrayOfPointers&& other);

	void free();

public:

	DynamicArrayOfPointers();

	DynamicArrayOfPointers(const DynamicArrayOfPointers& other);

	DynamicArrayOfPointers(DynamicArrayOfPointers&& other) noexcept;

	DynamicArrayOfPointers& operator = (const DynamicArrayOfPointers& other);

	DynamicArrayOfPointers& operator = (DynamicArrayOfPointers&& other) noexcept;

	~DynamicArrayOfPointers();

	void addInt(const WrapperInt& number);

	void removeInt(int index);

	friend std::ostream& operator << (std::ostream& os, const DynamicArrayOfPointers& arr);

	friend std::istream& operator >> (std::istream& is, DynamicArrayOfPointers& arr);

};


