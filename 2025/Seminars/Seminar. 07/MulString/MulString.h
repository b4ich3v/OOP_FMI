#include "MyString.h"
#pragma once

class MulString
{
private:

	MyString str;

public:

	MulString(const MyString& str);

	MulString(const char* data);

	MulString& operator *= (int k);

	MulString& operator %= (const MulString& other);

	const char* getData() const;
		 
	friend std::ostream& operator << (std::ostream& os, const MulString s);

};

bool operator == (const MulString& s1, const MulString& s2);

bool operator != (const MulString& s1, const MulString& s2);

MulString operator * (const MulString& s, int k);

MulString operator * (int k, const MulString& s);

MulString operator % (const MulString& s1, const MulString& s2);

