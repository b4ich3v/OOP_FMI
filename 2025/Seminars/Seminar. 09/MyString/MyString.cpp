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
	this->size = 8;
	this->data = new char[capacity] {0};
	int newSize = strlen(data);

	while (newSize >= capacity) resize(capacity * 2);

	this->size = newSize;
	strncpy(this->data, data, size);
	this->data[size] = '\0';

}

MyString::MyString(const char letter)
{

	capacity = 8;
	size = 1;
	data = new char[capacity];
	data[0] = letter;
	data[1] = '\0';

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

	while (size + other.size + 1 > capacity) resize(capacity * 2);
	strcat(data, other.data);
	size = strlen(data);

	return *this;

}

MyString& MyString::operator += (const char letter)
{

	if (size + 1 >= capacity) resize(capacity * 2);
	data[size] = letter;
	size += 1;
	data[size] = '\0';

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

void MyString::changePtrIndex(int offset)
{

	size = size - offset;
	char* newData = new char[size + 1];
	char* fictivePtr = data + offset;
	strncpy(newData, fictivePtr, size);
	newData[size] = '\0';

	delete[] data;
	data = newData;

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

	os << str.getData() << std::endl;

	return os;

}

std::istream& operator >> (std::istream& is, MyString& str)
{

	int size = 0;
	char buffer[1024];

	is.getline(buffer, 1024);
	size = strlen(buffer);

	char* data = new char[size + 1];
	strncpy(data, buffer, size);
	data[size] = '\0';

	MyString newStr = data;
	str = newStr;

	delete[] data;
	data = nullptr;
	return is;

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

MyString::MyString(MyString&& other) noexcept
{

	moveTo(std::move(other));

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
