#include "myString.h"
#include <cstring>
#include <algorithm>
#pragma warning (disable : 4996)

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

MyString::MyString() : MyString("") {}

MyString::MyString(const char* newData)
{

    size = std::strlen(newData);
    allocatedDataSize = dataToAllocByStringLen(size);
    data = new char[allocatedDataSize];
    std::strcpy(data, newData);

}

MyString::MyString(size_t stringLength)
{

    allocatedDataSize = dataToAllocByStringLen(stringLength);
    data = new char[allocatedDataSize];
    size = 0;
    data[0] = '\0';

}

MyString::MyString(const MyString& other)
{

    copyFrom(other);

}

MyString::MyString(MyString&& other) noexcept
{

    moveFrom(std::move(other));

}

void MyString::moveFrom(MyString&& other)
{

    data = other.data;
    other.data = nullptr;

    size = other.size;
    other.size = 0;

    allocatedDataSize = other.allocatedDataSize;
    other.allocatedDataSize = 0;

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

    return allocatedDataSize - 1;

}

size_t MyString::getSize() const
{

    return size;

}

const char* MyString::c_str() const
{

    return data;

}

MyString& MyString::operator+=(const MyString& other)
{

    if (getSize() + other.getSize() + 1 > allocatedDataSize)
        resize(dataToAllocByStringLen(getSize() + other.getSize()));

    std::strncat(data, other.data, other.getSize());

    size = getSize() + other.getSize();
    return *this;

}

char& MyString::operator[](size_t index)
{

    return data[index]; 

}

const char& MyString::operator[](size_t index) const
{

    return data[index]; 

}

std::ostream& operator<<(std::ostream& os, const MyString& obj)
{

    return os << obj.data;

}

std::istream& operator>>(std::istream& is, MyString& ref)
{

    char buff[1024];
    is >> buff;
    size_t buffStringSize = std::strlen(buff);

    if (buffStringSize > ref.getCapacity())
        ref.resize(dataToAllocByStringLen(buffStringSize));

    strcpy(ref.data, buff);
    ref.size = buffStringSize;

    return is;

}

void MyString::resize(unsigned newAllocatedDataSize)
{

    char* newData = new char[newAllocatedDataSize + 1];
    std::strcpy(newData, data);
    delete[] data;
    data = newData;
    allocatedDataSize = newAllocatedDataSize;

}

void MyString::free()
{

    delete[] data;

}

void MyString::copyFrom(const MyString& other)
{

    allocatedDataSize = other.allocatedDataSize;
    data = new char[allocatedDataSize];
    std::strcpy(data, other.data);
    size = other.size;

}

MyString MyString::substr(size_t begin, size_t howMany) const
{

    if (begin + howMany > getSize())
        throw std::length_error("Error, Substr out of range");


    MyString res(howMany + 1);
    strncat(res.data, data + begin, howMany);

    return res;

}


MyString operator + (const MyString& lhs, const MyString& rhs)
{

    MyString result(lhs.getSize() + rhs.getSize());
    result += lhs; 
    result += rhs;
    return result;

}

bool operator == (const MyString& lhs, const MyString& rhs)
{

    return std::strcmp(lhs.c_str(), rhs.c_str()) == 0;

}

bool operator != (const MyString& lhs, const MyString& rhs)
{

    return std::strcmp(lhs.c_str(), rhs.c_str()) != 0;

}

bool operator < (const MyString& lhs, const MyString& rhs)
{

    return std::strcmp(lhs.c_str(), rhs.c_str()) < 0;

}

bool operator <= (const MyString& lhs, const MyString& rhs)
{

    return std::strcmp(lhs.c_str(), rhs.c_str()) <= 0;

}

bool operator > (const MyString& lhs, const MyString& rhs)
{

    return std::strcmp(lhs.c_str(), rhs.c_str()) > 0;

}

bool operator >= (const MyString& lhs, const MyString& rhs)
{

    return std::strcmp(lhs.c_str(), rhs.c_str()) >= 0;

}
