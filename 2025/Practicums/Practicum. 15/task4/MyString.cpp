#include "MyString.h"

void MyString::free() 
{

	delete[] data;
	data = nullptr;
	size = 0;
	capacity = 8;

}

void MyString::copyFrom(const MyString& other) 
{

	data = new char[strlen(other.data) + 1];
	size = strlen(other.data);
	capacity = other.capacity;

	strncpy(data, other.data, strlen(other.data));
	data[strlen(other.data)] = '\0';

}

void MyString::moveTo(MyString&& other) 
{

	data = other.data;
	size = other.size;
	capacity = other.capacity;

	other.data = nullptr;
	other.size = 0;
	other.capacity = 8;

}

void MyString::resize(size_t newCapacity) 
{

	if (newCapacity <= capacity) return;

	char* newData = new char[newCapacity] {};
	strncpy(newData, data, strlen(data));
	newData[strlen(data)] = '\0';

	delete[] data;
	data = newData;
	capacity = newCapacity;

}

MyString::MyString():
	MyString("") {}

MyString::MyString(const char* data) 
{

	if (!data) throw std::logic_error("Error");

	this->data = new char[strlen(data) + 1];
	strncpy(this->data, data, strlen(data));
	this->data[strlen(data)] = '\0';
	this->size = strlen(data);
	this->capacity = size * 2;

}

MyString::MyString(const MyString& other) 
{

	copyFrom(other);

}

MyString::MyString(MyString&& other) noexcept 
{

	moveTo(std::move(other));

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

MyString& MyString::operator = (MyString&& other) noexcept
{

	if (this != &other)
	{

		free();
		moveTo(std::move(other));

	}

	return *this;

}

MyString::~MyString() 
{

	free();

}

size_t MyString::getSize() const 
{

	return size;

}

size_t MyString::getCapacity() const 
{

	return capacity;

}

const char* MyString::getData() const 
{

	return data;

}

MyString MyString::substr(int i, int offset) 
{

	if (i + offset >= size || i < 0 || i + offset < 0) throw std::logic_error("Error");

	char* newData = new char[strlen(data) + 1];
	strncpy(newData, data, strlen(data));
	newData[strlen(data)] = '\0';

	const char* beginPtr = newData;
	beginPtr += i;

	char* endPtr = newData;
	endPtr += (i + offset);
	*endPtr = '\0';

	MyString result(beginPtr);
	delete[] newData;
	newData = nullptr;
	return result;

}

std::ostream& operator << (std::ostream& os, const MyString& str) 
{

	os << str.getData();
	return os;

}

std::istream& operator >> (std::istream& is, MyString& str) 
{

	char buffer[1024];
	is.getline(buffer, 1024, '\n');
	
	str = std::move(MyString(buffer));
	return is;

}

char& MyString::operator [] (size_t index) 
{

	if (index >= size) throw std::logic_error("Error");
	return data[index];

}

const char& MyString::operator [] (size_t index) const
{

	if (index >= size) throw std::logic_error("Error");
	return data[index];

}
