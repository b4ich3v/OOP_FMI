#include <cstring>
#include <iostream>
#pragma once

class MyString
{
private:

	char* data = nullptr;
	size_t size = 0;
	size_t capacity = 8;

	void free();

	void copyFrom(const MyString& other);

	void moveTo(MyString&& other);

	void resize(size_t newCapacity);

public:

	MyString();

	MyString(const char* data);

	MyString(const MyString& other);

	MyString(MyString&& other) noexcept;

	MyString& operator = (const MyString& other);

	MyString& operator = (MyString&& other) noexcept;

	~MyString();

	size_t getSize() const;

	size_t getCapacity() const;

	const char* getData() const;

	MyString substr(int i, int offset);

	friend std::ostream& operator << (std::ostream& os, const MyString& str);

	friend std::istream& operator >> (std::istream& is, MyString& str);

	char& operator [] (size_t index);

	const char& operator [] (size_t index) const;

};

