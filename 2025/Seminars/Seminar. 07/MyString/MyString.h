#include <iostream>
#include <cstring>
#pragma once

class MyString
{
private:

	char* data = nullptr;
	int size = 0;
	int capacity = 8;

	void free();

	void copyFrom(const MyString& other);

	void resize(int newCapacity);

public:

	MyString();

	MyString(const char* data);

	MyString(const char letter);

	MyString(const MyString& other);

	MyString& operator = (const MyString& other);

	MyString& operator += (const MyString& other);

	MyString& operator += (const char letter);

	~MyString();

	char& operator [] (int index);

	const char operator [] (int index) const;

	const char* getData() const;

	int getSize() const;

	void changePtrIndex(int offset);

	friend std::ostream& operator << (std::ostream& os, const MyString& str);

	friend std::istream& operator >> (std::istream& is, MyString& str);

};

bool operator >= (const MyString& str1, const MyString& str2);

bool operator <= (const MyString& str1, const MyString& str2);

bool operator > (const MyString& str1, const MyString& str2);

bool operator < (const MyString& str1, const MyString& str2);

bool operator == (const MyString& str1, const MyString& str2);

bool operator != (const MyString& str1, const MyString& str2);

MyString operator + (const MyString& str1, const MyString& str2);
