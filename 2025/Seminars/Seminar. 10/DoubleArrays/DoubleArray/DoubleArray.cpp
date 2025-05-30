#include "DoubleArray.h"

void DoubleArray::copyFrom(const DoubleArray& other)
{

	this->array = new double[other.capacity];

	for (int i = 0; i < other.size; i++)
	{

		this->array[i] = other.array[i];

	}

	this->size = other.size;
	this->capacity = other.capacity;

}

void DoubleArray::free()
{

	delete[] array;
	array = nullptr;
	size = 0;

}

void DoubleArray::resize(int newCapacity)
{

	if (newCapacity <= capacity) return;

	double* newArray = new double[newCapacity];

	for (int i = 0; i < size; i++)
	{

		newArray[i] = array[i];

	}

	delete[] array;
	array = newArray;
	capacity = newCapacity;

}

void DoubleArray::setArray(double* array, int size)
{

	if (this->array == array || !array) throw std::logic_error("Error");

	while (capacity <= size) capacity *= 2;

	delete[] this->array;
	this->array = new double[capacity];

	for (int i = 0; i < size; i++)
	{

		this->array[i] = array[i];

	}

	this->size = size;

}

DoubleArray::DoubleArray()
{

	size = 0;
	capacity = 8;
	array = new double[capacity];

}

DoubleArray::DoubleArray(int size)
{

	this->array = new double[size] {0};
	capacity = size;

}

DoubleArray::DoubleArray(const DoubleArray& other)
{

	copyFrom(other);

}

DoubleArray::DoubleArray(double* array, int size)
{

	setArray(array, size);

}

DoubleArray& DoubleArray::operator = (const DoubleArray& other)
{

	if (this != &other)
	{

		free();
		copyFrom(other);

	}

	return *this;

}

DoubleArray::~DoubleArray()
{

	free();

}

void DoubleArray::moveTo(DoubleArray&& other) 
{

	this->array = other.array;
	this->capacity = other.capacity;
	this->size = other.size;

	other.array = nullptr;
	other.capacity = 8;
	other.size = 0;

}

DoubleArray::DoubleArray(DoubleArray&& other) noexcept 
{

	moveTo(std::move(other));

}

DoubleArray& DoubleArray::operator = (DoubleArray&& other) noexcept 
{

	if (this != &other) 
	{

		free();
		moveTo(std::move(other));

	}

	return *this;

}

bool DoubleArray::isEmpty() const 
{

	return size == 0;

}

bool operator == (const DoubleArray& arr1, const DoubleArray& arr2) 
{

	if (arr1.size != arr2.size) return false;

	for (int i = 0; i < arr1.size; i++)
	{

		if (arr1.array[i] != arr2.array[i]) return false;

	}

	return true;

}

bool operator != (const DoubleArray& arr1, const DoubleArray& arr2) 
{

	return !(arr1 == arr2);

}

double& DoubleArray::operator [] (int index) 
{

	if (index < 0 || index >= size) throw std::logic_error("Error");

	return array[index];

}

const double DoubleArray::operator [] (int index) const
{

	if (index < 0 || index >= size) throw std::logic_error("Error");

	return array[index];

}

int DoubleArray::getSize() const 
{

	return size;

}

const double* DoubleArray::getArr() const 
{

	return array;

}

void DoubleArray::incrementSize() 
{

	size += 1;

}

void DoubleArray::decrementSize() 
{

	size -= 1;

}

void DoubleArray::publicResize() 
{

	resize(capacity * 2);

}

double*& DoubleArray::getArr() 
{

	return array;

}

int DoubleArray::getCapacity() const 
{

	return capacity;

}
