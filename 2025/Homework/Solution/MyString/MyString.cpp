#include "MyString.h"

void MyString::free()
{

    delete[] data;
    data = nullptr;
    capacity = 8;

}

void MyString::copyFrom(const MyString& other)
{

    capacity = other.capacity;
    data = new char[capacity];
    strncpy(data, other.data, strlen(other.data));
    data[strlen(other.data)] = '\0';

}

void MyString::moveTo(MyString&& other)
{
    data = other.data;
    capacity = other.capacity;

    other.data = nullptr;
    other.capacity = 8;

}

void MyString::resize(size_t newCapacity)
{

    if (newCapacity <= capacity) return;

    char* newData = new char[newCapacity];
    strncpy(newData, data, strlen(data));
    newData[strlen(data)] = '\0';

    delete[] data;
    data = newData;
    capacity = newCapacity;

}

MyString::MyString()
{

    capacity = 8;
    data = new char[capacity];
    data[0] = '\0';

}

MyString::MyString(size_t capacity)
{

    data = new char[capacity] {};
    data[0] = '\0';
    this->capacity = capacity;

}

MyString::MyString(const char* data)
{

    if (!data) throw std::runtime_error("Nullptr");

    size_t sizeOfStr = strlen(data);
    this->capacity = 8;

    while (this->capacity < sizeOfStr + 1) this->capacity *= 2;

    this->data = new char[capacity];
    strncpy(this->data, data, strlen(data));
    this->data[strlen(data)] = '\0';

}

MyString::MyString(const MyString& other)
{

    copyFrom(other);

}

MyString::MyString(MyString&& other) noexcept
{

    moveTo(std::move(other));

}

MyString::~MyString()
{

    free();

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

MyString& MyString::operator += (const MyString& other)
{

    size_t size1 = size();
    size_t size2 = other.size();
    size_t needed = size1 + size2 + 1;

    while (needed > capacity) resize(capacity * 2);
    strncat(data, other.data, strlen(other.data));

    return *this;

}

MyString& MyString::operator += (const char* str)
{

    size_t size1 = size();
    size_t size2 = strlen(str);
    size_t needed = size1 + size2 + 1;

    while (needed > capacity) resize(capacity * 2);
    strncat(data, str, strlen(str));

    return *this;
}

const char& MyString::operator [] (size_t index) const
{

    if (!data || index >= size())  throw std::out_of_range("String index out of range");
    return data[index];

}

char& MyString::operator [] (size_t index)
{

    if (!data || index >= size())  throw std::out_of_range("String index out of range");
    return data[index];

}

MyString MyString::substr(size_t from, size_t to) const
{

    if (!data || from > to || to > size()) throw std::out_of_range("String substr indices");

    size_t sizeOfStr = to - from;
    MyString result;

    result.capacity = 8;
    while (result.capacity < sizeOfStr + 1) result.capacity *= 2;
    result.data = new char[result.capacity];

    const char* ptr = data + from;
    strncpy(result.data, ptr, sizeOfStr);
    result.data[sizeOfStr] = '\0';

    return result;

}

bool MyString::empty() const
{

    return !data || data[0] == '\0';

}

size_t MyString::size() const
{

    return data ? std::strlen(data) : 0;

}

const char* MyString::getData() const
{

    return data;

}

std::ostream& operator << (std::ostream& os, const MyString& str)
{

    return os << (str.data ? str.data : "");

}

std::istream& operator >> (std::istream& is, MyString& str)
{

    char buffer[MAX_SIZE_BUFFER];
    is >> buffer;

    str.free();
    str.capacity = 8;
    while (str.capacity < strlen(buffer) + 1) str.capacity *= 2;

    str.data = new char[str.capacity];
    strncpy(str.data, buffer, strlen(buffer));
    str.data[strlen(buffer)] = '\0';

    return is;

}

MyString operator + (const MyString& left, const MyString& right) 
{

    MyString result(left);
    result += right;

    return result;

}

MyString operator + (const MyString& str, const char* data) 
{

    MyString result(str);
    result += data;

    return result;

}

MyString operator + (const char* data, const MyString& str) 
{

    MyString result(str);
    result += data;

    return result;

}
