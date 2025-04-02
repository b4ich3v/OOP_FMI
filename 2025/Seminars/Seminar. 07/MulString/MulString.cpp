#include "MulString.h"

const char* MulString::getData() const
{

	return str.getData();

}

MulString::MulString(const MyString& str) : str(str) {}

MulString::MulString(const char* data): str(data) {}

MulString& MulString::operator *= (int k) 
{

	MyString fictive((*this).str);
	MulString result(fictive);

	for (int i = 0; i < k; i++)
	{

		result.str += fictive;

	}

	*this = result;
	return *this;

}

MulString& MulString::operator %= (const MulString& other)
{

	bool contains[256]{ false };
	int size1 = str.getSize();
	int size2 = other.str.getSize();

	for (int i = 0; i < size1; i++) contains[(int)str[i]] = true;

	for (int i = 0; i < size2; i++) contains[(int)other.str[i]] = true;

	MyString fictiveString(' ');

	for (int i = 0; i <= 256; i++)
	{

		if (contains[i])
		{

			fictiveString += (char)i;

		}

	}

	fictiveString.changePtrIndex(2);
	MulString result(fictiveString);
	(*this) = result;

	return *this;

}

MulString operator * (const MulString& s, int k) 
{

	MulString result(s);
	result *= k;

	return result;

}

MulString operator * (int k, const MulString& s)
{

	MulString result(s);
	result *= k;

	return result;

}

MulString operator % (const MulString& s1, const MulString& s2) 
{

	MulString result(s1);
	result %= s2;

	return result;

}

bool operator == (const MulString& s1, const MulString& s2) 
{

	return strcmp(s1.getData(), s2.getData());

}

bool operator != (const MulString& s1, const MulString& s2)
{

	return !(s1 == s2);

}

std::ostream& operator << (std::ostream& os, const MulString s)
{

	os << s.str;
	return os;

}
