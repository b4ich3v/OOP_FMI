#include "Vector.h"

void Vector::copyFrom(const Vector& other) 
{

	this->array = new int[other.capacity];

	for (int i = 0; i < other.size; i++)
	{

		this->array[i] = other.array[i];

	}

	this->size = other.size;
	this->capacity = other.capacity;

}

void Vector::free() 
{

	delete[] array;
	array = nullptr;
	size = 0;

}

void Vector::resize(int newCapacity) 
{

	if (newCapacity <= capacity) return;

	int* newArray = new int[newCapacity];

	for (int i = 0; i < size; i++)
	{

		newArray[i] = array[i];

	}

	delete[] array;
	array = newArray;
	capacity = newCapacity;

}

void Vector::setArray(int* array, int size) 
{

	if (this->array == array || !array) throw std::logic_error("Error");

	delete[] this->array;
	this->array = new int[size];

	for (int i = 0; i < size; i++)
	{

		this->array[i] = array[i];

	}

	this->size = size;

}

Vector::Vector() 
{

	size = 0;
	capacity = 8;
	array = new int[capacity];

}

Vector::Vector(int size)
{

	this->array = new int[size] {0};
	capacity = size;

}

Vector::Vector(const Vector& other) 
{

	copyFrom(other);

}

Vector::Vector(int* array, int size) 
{

	setArray(array, size);
	this->capacity = 8;

}

Vector& Vector::operator = (const Vector& other)
{

	if (this != &other)
	{

		free();
		copyFrom(other);

	}

	return *this;

}

Vector& Vector::operator += (const Vector& other)
{

	if (this->size != other.size) throw std::logic_error("Error");

	for (int i = 0; i < size; i++)
	{

		array[i] += other.array[i];

	}

	return *this;

}

Vector& Vector::operator -= (const Vector& other)
{

	if (this->size != other.size) throw std::logic_error("Error");

	for (int i = 0; i < size; i++)
	{

		array[i] -= other.array[i];

	}

	return *this;

}

Vector& Vector::operator *= (double scalar)
{

	for (int i = 0; i < size; i++)
	{

		array[i] *= scalar;

	}

	return *this;

}

int& Vector::operator [] (int index) 
{

	if (index < 0 || index >= size) throw std::logic_error("Error");

	return array[index];

}

const int Vector::operator [] (int index) const 
{

	if (index < 0 || index >= size) throw std::logic_error("Error");

	return array[index];

}

std::istream& operator >> (std::istream& is, Vector& vector) 
{

	int size = 0;
	is >> size;

	int* data = new int[size];

	for (int i = 0; i < size; i++)
	{

		is >> data[i];

	}

	Vector newVector(data, size);
	vector = newVector;

	return is;

}

std::ostream& operator << (std::ostream& os, const Vector& vector)
{

	os << vector.size << ' ';
	
	for (int i = 0; i < vector.size; i++)
	{

		os << vector[i] << ' ';

	}

	return os;

}

Vector::~Vector()
{

	free();
	
}

void Vector::push(int number) 
{

	if (size == capacity) resize(capacity * 2);

	array[size] = number;
	size += 1;

}

void Vector::pop()
{

	if (size == 0) throw std::logic_error("Error");

	size -= 1;

}

int Vector::getSize() const 
{
	
	return size;

}

bool Vector::isEmpty() const 
{

	return size == 0;

}

Vector operator + (const Vector& left, const Vector& right)
{

	Vector result(left);
	result += right;

	return result;

}

Vector operator - (const Vector& left, const Vector& right)
{

	Vector result(left);
	result -= right;

	return result;

}

Vector operator * (const Vector& vector, double scalar)
{

	Vector result(vector);
	result *= scalar;

	return result;

}
