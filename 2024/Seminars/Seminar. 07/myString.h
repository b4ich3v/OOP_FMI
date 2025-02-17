#pragma once
#include <fstream>

class MyString 
{
private:

	char* data;
	int size;
	int capacity;

	explicit MyString(int size);

	void free();

	void copyFrom(const MyString& other);

	void resize(int number);

public:

	MyString();

	MyString(const char* data);

	MyString(const MyString& other);

	MyString& operator = (const MyString& other);

	MyString& operator += (const MyString & other);

	~MyString();

	int getCapacity() const;

	int getSize() const;

	const char* c_str() const;

	char& operator [] (int index);

	char operator [] (int index) const;

	friend std::istream& operator >> (std::istream& is, MyString& other);

	friend std::ostream& operator << (std::ostream& os, const MyString& other);

};

MyString operator + (const MyString& lhs, const MyString& rhs);

bool operator == (const MyString& lhs, const MyString& rhs);

bool operator != (const MyString& lhs, const MyString& rhs);

bool operator < (const MyString& lhs, const MyString& rhs);

bool operator <= (const MyString& lhs, const MyString& rhs);

bool operator > (const MyString& lhs, const MyString& rhs);

bool operator >= (const MyString& lhs, const MyString& rhs);
