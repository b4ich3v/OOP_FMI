#include "MyString.h"
#include <cstring>
#pragma warning(disable: 4996)

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

void MyString::resize(unsigned newAllocatedDataSize)
{
	char* newData = new char[newAllocatedDataSize + 1];

	std::strcpy(newData, _data);
	delete[] _data;
	_data = newData;

	_allocatedDataSize = newAllocatedDataSize;

}

MyString::MyString() : MyString("") {}

MyString::MyString(const char* data)
{
	_size = strlen(data);
	_allocatedDataSize = dataToAllocByStringLen(_size);
	_data = new char[_allocatedDataSize];
	strcpy(_data, data);
}

MyString::MyString(size_t stringLength)
{
	_allocatedDataSize = dataToAllocByStringLen(stringLength);
	_size = 0;

	_data = new char[_allocatedDataSize];
	_data[0] = '\0';
}

void MyString::copyFrom(const MyString& other)
{
	_size = other._size;
	_allocatedDataSize = other._allocatedDataSize;

	_data = new char[_allocatedDataSize];
	strcpy(_data, other._data);
}

void MyString::moveFrom(MyString&& other)
{
	_size = other._size;
	_allocatedDataSize = other._allocatedDataSize;

	other._size = other._allocatedDataSize = 0;

	_data = other._data;
	other._data = nullptr;

}


void MyString::free()
{
	delete[] _data;
}

MyString::MyString(const MyString& other)
{
	copyFrom(other);
}

MyString::MyString(MyString&& other) noexcept
{
	moveFrom(std::move(other));
}

MyString& MyString::operator=(const MyString& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

MyString& MyString::operator=(MyString&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

MyString::~MyString()
{
	free();
}

size_t MyString::getCapacity() const
{
	return _allocatedDataSize;
}

size_t MyString::getSize() const
{
	return _size;

}

const char* MyString::c_str() const
{
	return _data;
}

MyString& MyString::operator+=(const MyString& other)
{
	if (getSize() + other.getSize() + 1 > _allocatedDataSize)
	{
		resize(dataToAllocByStringLen(getSize() + other.getSize()));
	}

	std::strncat(_data, other._data, other.getSize());
	_size = getSize() + other.getSize();

	return *this;

}

char& MyString::operator[](size_t index)
{
	return _data[index]; //no security check
}

const char& MyString::operator[](size_t index) const
{
	return _data[index]; //no security check
}

std::ostream& operator<<(std::ostream& os, const MyString& obj)
{
	return os << obj._data;
}

std::istream& operator>>(std::istream& is, MyString& ref)
{
	char buff[1024];
	is >> buff;
	size_t buffStringSize = strlen(buff);

	if (buffStringSize > ref._allocatedDataSize)
	{
		ref.resize(dataToAllocByStringLen(buffStringSize));
	}

	strcpy(ref._data, buff);
	ref._size = buffStringSize;
	return is;
}

MyString MyString::substr(size_t begin, size_t howMany) const
{
	if (begin + howMany > _size)
	{
		throw std::length_error("Error, Substr out of range");
	}

	MyString res(howMany + 1);
	strncat(res._data, _data + begin, howMany);
	return res;
}

MyString operator+(const MyString& lhs, const MyString& rhs)
{
	MyString res(lhs._size + rhs._size);
	res += lhs;
	res += rhs;

	return res;
}

bool operator==(const MyString& lhs, const MyString& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) == 0;
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