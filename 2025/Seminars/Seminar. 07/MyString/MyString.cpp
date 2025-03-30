#include "MyString.h"

MyString::MyString() 
{

	capacity = 8;
	size = 0;
	data = new char[capacity] {0};

}

MyString::MyString(const char* data)
{

	if (!data) throw std::logic_error("Error");

	this->capacity = 8;

	this->data = new char[capacity];
	strncpy(this->data, data, strlen(data));
	this->data[strlen(data)] = '\0';
	this->size = strlen(data);
	
	while (size > capacity) resize(capacity * 2);

}

MyString::MyString(const MyString& other) 
{

	copyFrom(other);

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

MyString& MyString::operator += (const MyString& other)
{

	while (size + other.size > capacity) resize(capacity * 2);
	strcat(data, other.data);
	size = strlen(data);

	return *this;

}

MyString::~MyString() 
{

	free();

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

	data = new char[other.capacity + 1];
	strncpy(data, other.data, strlen(other.data));
	data[strlen(other.data)] = '\0';
	size = other.size;
	capacity = other.capacity;

}

void MyString::resize(int newCapacity)
{

	if (newCapacity <= capacity) return;

	char* newData = new char[newCapacity];
	strncpy(newData, data, size);
	newData[size] = '\0';

	delete[] data;
	data = newData;
	capacity = newCapacity;

}

char& MyString::operator [] (int index)
{

	if (index < 0 || index >= size) throw std::logic_error("Error");

	return data[index];

}

const char MyString::operator [] (int index) const
{

	if (index < 0 || index >= size) throw std::logic_error("Error");

	return data[index];

}

const char* MyString::getData() const 
{

	return data;

}

int MyString::getSize() const
{

	return size;

}

bool operator >= (const MyString& str1, const MyString& str2) 
{

	return strcmp(str1.getData(), str2.getData()) >= 0;

}

bool operator <= (const MyString& str1, const MyString& str2)
{

	return strcmp(str1.getData(), str2.getData()) <= 0;

}

bool operator > (const MyString& str1, const MyString& str2) 
{

	return strcmp(str1.getData(), str2.getData()) > 0;

}

bool operator < (const MyString& str1, const MyString& str2) 
{

	return strcmp(str1.getData(), str2.getData()) < 0;

}

bool operator == (const MyString& str1, const MyString& str2) 
{

	return strcmp(str1.getData(), str2.getData()) == 0;

}

bool operator != (const MyString& str1, const MyString& str2) 
{

	return !(str1 == str2);

}

MyString operator + (const MyString& str1, const MyString& str2) 
{

	MyString result(str1);
	result += str2;

	return result;

}

std::ostream& operator << (std::ostream& os, const MyString& str) 
{

	os << str.getSize() << " ";
	os << str.getData() << std::endl;

	return os;

}

std::istream& operator >> (std::istream& is, MyString& str)
{

	int size = 0;
	char buffer[1024];

	is >> size;
	is >> buffer;
	is.ignore(1);

	char* data = new char[size + 1];
	strncpy(data, buffer, size);
	data[size] = '\0';

	MyString newStr = data;
	str = newStr;

	delete[] data;
	data = nullptr;
	return is;

}
