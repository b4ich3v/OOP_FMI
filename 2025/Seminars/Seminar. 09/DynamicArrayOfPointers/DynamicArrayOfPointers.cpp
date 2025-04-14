#include "DynamicArrayOfPointers.h"

DynamicArrayOfPointers::DynamicArrayOfPointers() 
{

	capacity = 8;
	countOfInts = 0;
	arrayOfInts = new WrapperInt * [capacity] {nullptr};

}

DynamicArrayOfPointers::DynamicArrayOfPointers(const DynamicArrayOfPointers& other) 
{

	copyFrom(other);

}

DynamicArrayOfPointers::DynamicArrayOfPointers(DynamicArrayOfPointers&& other) noexcept 
{

	moveTo(std::move(other));

}

DynamicArrayOfPointers& DynamicArrayOfPointers::operator = (const DynamicArrayOfPointers& other)
{

	if (this != &other) 
	{

		free();
		copyFrom(other);

	}

	return *this;

}

DynamicArrayOfPointers& DynamicArrayOfPointers::operator = (DynamicArrayOfPointers&& other) noexcept
{

	if (this != &other) 
	{

		free();
		moveTo(std::move(other));

	}

	return *this;

}

DynamicArrayOfPointers::~DynamicArrayOfPointers() 
{

	free();

}

void DynamicArrayOfPointers::addInt(const WrapperInt& number) 
{

	if (countOfInts == capacity) resize(capacity * 2);

	arrayOfInts[countOfInts] = new WrapperInt(number);
	countOfInts += 1;

}

void DynamicArrayOfPointers::removeInt(int index)
{

	if (index < 0 || index >= countOfInts) throw std::logic_error("Error");
		
	delete arrayOfInts[index];
	arrayOfInts[index] = nullptr;

	for (int i = index; i < countOfInts - 1; i++)
	{

		arrayOfInts[i] = arrayOfInts[i + 1];

	}

	arrayOfInts[countOfInts - 1] = nullptr;
	countOfInts -= 1;

}

std::ostream& operator << (std::ostream& os, const DynamicArrayOfPointers& arr) 
{

	os << arr.countOfInts << " " << arr.capacity << std::endl;

	for (int i = 0; i < arr.countOfInts; i++)
	{

		os << (*arr.arrayOfInts[i]) << " ";

	}

	return os;

}

std::istream& operator >> (std::istream& is, DynamicArrayOfPointers& arr) 
{

	int countOfInt = 0;
	int capacity = 0;

	is >> countOfInt >> capacity;
	is.ignore(1);

	arr.free();
	arr.capacity = capacity;
	arr.countOfInts = countOfInt;
	arr.arrayOfInts = new WrapperInt * [capacity] {nullptr};

	for (int i = 0; i < countOfInt; i++)
	{

		arr.arrayOfInts[i] = new WrapperInt(0);
		is >> (*arr.arrayOfInts[i]);

	}

	return is;

}

void DynamicArrayOfPointers::resize(int newCapacity) 
{

	if (newCapacity <= capacity) throw std::logic_error("Error");

	WrapperInt** newInts = new WrapperInt * [newCapacity] {nullptr};

	for (int i = 0; i < countOfInts; i++)
	{

		newInts[i] = arrayOfInts[i];
		arrayOfInts[i] = nullptr;

	}

	delete[] arrayOfInts;
	arrayOfInts = newInts;
	capacity = newCapacity;

}

void DynamicArrayOfPointers::copyFrom(const DynamicArrayOfPointers& other) 
{

	arrayOfInts = new WrapperInt * [other.capacity] {nullptr};
	capacity = other.capacity;
	countOfInts = other.countOfInts;

	for (int i = 0; i < other.countOfInts; i++)
	{

		arrayOfInts[i] = new WrapperInt(*other.arrayOfInts[i]);

	}

}

void DynamicArrayOfPointers::moveTo(DynamicArrayOfPointers&& other) 
{

	arrayOfInts = other.arrayOfInts;
	capacity = other.capacity;
	countOfInts = other.countOfInts;

	other.arrayOfInts = nullptr;
	other.capacity = 8;
	other.countOfInts = 0;

}

void DynamicArrayOfPointers::free() 
{

	for (int i = 0; i < capacity; i++)
	{

		delete arrayOfInts[i];
		arrayOfInts[i] = nullptr;

	}

	delete[] arrayOfInts;
	arrayOfInts = nullptr;
	capacity = 8;
	countOfInts = 0;

}
