#include <iostream>
#include "myString.h"

static unsigned roundToPowerOfTwo(unsigned v)
{

	v--;
	v |= v >> 1;
	v |= v >> 2;
	v |= v >> 4;
	v |= v >> 8;
	v |= v >> 16;
	v++;
	return v;

}

static unsigned dataToAllocByStringLen(unsigned stringLength)
{

	return std::max(roundToPowerOfTwo(stringLength + 1), 16u);

}

MyString::MyString() 
{

	capacity = 8;
	size = 0;
	data = new char[capacity];
	data = nullptr;

}

MyString::MyString(const char* data)
{

	size = std::strlen(data);
	capacity = dataToAllocByStringLen(size);
	data = new char[capacity];
	std::strcpy(this->data, data);

}

MyString::MyString(const MyString& other) 
{

	copyFrom(other);

}

MyString::MyString(int size)
{

	capacity = dataToAllocByStringLen(size);
	data = new char[capacity];
	size = 0;
	data[0] = '\0';

}

MyString& MyString::operator = (const MyString& other)
{

	if (this != &other)
	{

		free();
		copyFrom(other);

	}

	return *this;
	
}

void MyString::free()
{

	delete[] data;
	data = nullptr;
	size = 0;
	capacity = 8;

}

void MyString::copyFrom(const MyString& other)
{

	capacity = other.capacity;
	size = other.size;

	char* newData = new char[capacity];

	for (int i = 0; i < size; i++)
	{

		newData[i] = other.data[i];

	}

	delete[] data;
	data = newData;

}

void MyString::resize(int number)
{

	char* newData = new char[number + 1];
	std::strcpy(newData, data);
	delete[] data;
	data = newData;
	capacity = number;

}

MyString::~MyString() 
{

	free();

}

int MyString::getCapacity() const 
{

	return capacity - 1;

}

int MyString::getSize() const
{

	return size;

}

const char* MyString::c_str() const 
{

	return data;

}

char& MyString::operator [] (int index)
{

	if (index <0 || index > size)
	{

		throw std::logic_error("Error");

	}

	return data[index];

}

char MyString::operator [] (int index) const
{

	if (index <0 || index > size)
	{

		throw std::logic_error("Error");

	}

	return data[index];

}

MyString& MyString::operator += (const MyString& other)
{

	if (getSize() + other.getSize() + 1 > capacity)
	{

		resize(dataToAllocByStringLen(getSize() + other.getSize()));

	}
		
	std::strncat(data, other.data, other.getSize());

	size = getSize() + other.getSize();
	return *this;

}

std::ostream& operator << (std::ostream& os, const MyString& other)
{

	os << other.data;
	return os;

}

std::istream& operator >> (std::istream& is, MyString& other)
{

	char buff[1024];
	is >> buff;

	int newSize = std::strlen(buff);

	if (newSize > other.getCapacity()) 
	{

		other.resize(dataToAllocByStringLen(newSize));

	}

	strcpy(other.data, buff);
	other.size = newSize;
	return is;

}

MyString operator + (const MyString& lhs, const MyString& rhs)
{

	MyString result(lhs);
	result += rhs;

	return result;

}

bool operator==(const MyString& lhs, const MyString& rhs)
{

	return std::strcmp(lhs.c_str(), rhs.c_str()) == 0;

}

bool operator!=(const MyString& lhs, const MyString& rhs)
{

	return std::strcmp(lhs.c_str(), rhs.c_str()) != 0;

}

bool operator<(const MyString& lhs, const MyString& rhs)
{

	return std::strcmp(lhs.c_str(), rhs.c_str()) < 0;

}

bool operator<=(const MyString& lhs, const MyString& rhs)
{

	return std::strcmp(lhs.c_str(), rhs.c_str()) <= 0;

}

bool operator>(const MyString& lhs, const MyString& rhs)
{

	return std::strcmp(lhs.c_str(), rhs.c_str()) > 0;

}

bool operator>=(const MyString& lhs, const MyString& rhs)
{

	return std::strcmp(lhs.c_str(), rhs.c_str()) >= 0;

}
