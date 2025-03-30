#pragma once

class String
{
private:

	char* data = nullptr;
	int size = 0;
	int capacity = 8;

	void free();

	void copyFrom(const String& other);

	void resize(int newCapacity);

public:

	String();

	String(const String& other);

	String& operator = (const String& other);

	~String();

	char& operator [] (int index);

	const char operator [] (int index) const;

	const char* getData() const;

	int getSize() const;

};

bool operator >= (const String& str1, const String& str2);

bool operator <= (const String& str1, const String& str2);

bool operator > (const String& str1, const String& str2);

bool operator < (const String& str1, const String& str2);

bool operator == (const String& str1, const String& str2);

bool operator != (const String& str1, const String& str2);
