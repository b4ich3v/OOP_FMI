#include "immutableString.h"
#pragma warning (disable : 4996)

ImmutableString::ImmutableString(const char* data)
{

	data = pool.getString(data);
	size = strlen(data);

}

ImmutableString::ImmutableString(const ImmutableString& other)
{

	data = pool.getString(other.data);
	size = other.size;

}

void ImmutableString::debug() const
{

	ImmutableString::pool.debug();

}

ImmutableString::~ImmutableString() 
{

	pool.removeString(data);

}

int ImmutableString::length() const 
{

	return size;

}

const char* ImmutableString::c_str() const 
{

	return data;

}

char ImmutableString::operator [] (int index) const
{

	if (index >= size) 
	{
		
		throw std::logic_error("Error");

	}

	return data[index];

}

std::ostream& operator << (std::ostream& os, const ImmutableString& str)
{

	return os << str.c_str();

}

bool operator < (const ImmutableString& lhs, const ImmutableString& rhs)
{

	return strcmp(lhs.c_str(), rhs.c_str()) < 0;

}

bool operator <= (const ImmutableString& lhs, const ImmutableString& rhs)
{

	return strcmp(lhs.c_str(), rhs.c_str()) <= 0;

}

bool operator >= (const ImmutableString& lhs, const ImmutableString& rhs)
{

	return strcmp(lhs.c_str(), rhs.c_str()) >= 0;

}

bool operator > (const ImmutableString& lhs, const ImmutableString& rhs)
{

	return strcmp(lhs.c_str(), rhs.c_str()) > 0;

}

bool operator == (const ImmutableString& lhs, const ImmutableString& rhs)
{

	return strcmp(lhs.c_str(), rhs.c_str()) == 0;

}

bool operator != (const ImmutableString& lhs, const ImmutableString& rhs)
{ 
	return strcmp(lhs.c_str(), rhs.c_str()) !=
		0;

}
