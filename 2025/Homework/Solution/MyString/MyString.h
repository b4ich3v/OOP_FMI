#include <cstring>
#include <iostream>
#pragma once

constexpr int MAX_SIZE_BUFFER = 1024;

class MyString
{
private:

	char* data = nullptr;
	size_t capacity = 8;

	void free();

	void copyFrom(const MyString& other);

	void moveTo(MyString&& other);

	void resize(size_t newCapacity);

public:

	MyString();

	MyString(size_t capacity);

	MyString(const char* data);

	MyString(const MyString& other);

	MyString(MyString&& other) noexcept;

	~MyString();

	MyString& operator = (const MyString& other);

	MyString& operator = (MyString&& other) noexcept;

	MyString& operator += (const MyString& other);

	MyString& operator += (const char* data);

	const char& operator [] (size_t index) const;

	char& operator [] (size_t index);

	MyString substr(size_t from, size_t to) const;

	bool empty() const;

	const char* getData() const;

	size_t size() const;

	friend std::ostream& operator << (std::ostream& os, const MyString& str);

	friend std::istream& operator >> (std::istream& is, MyString& str);

};

MyString operator + (const MyString& left, const MyString& right);

MyString operator + (const MyString& str, const char* data);

MyString operator + (const char* data, const MyString& str);
