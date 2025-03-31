#include "ImmutableString.h"

StringPool ImmutableString::pool;

void ImmutableString::copyFrom(const ImmutableString& other) 
{

	pool.chainString(other.data);
	data = new char[strlen(other.data) + 1];
	strncpy(data, other.data, strlen(other.data));
	data[strlen(other.data)] = '\0';
	size = other.size;

}

void ImmutableString::free() 
{

	pool.unchainString(data);
	delete[] data;
	data = nullptr;

}

ImmutableString::ImmutableString(const char* data) 
{

	pool.chainString(data);
	this->data = new char[strlen(data) + 1];
	strncpy(this->data, data, strlen(data));
	this->data[strlen(data)] = '\0';
	size = strlen(data);

}

const char& ImmutableString::operator [] (int index) const 
{

	if (index < 0 || index >= size) throw std::logic_error("Error");

	return data[index];

}

const char* ImmutableString::getData() const
{

	return data;

}

ImmutableString::ImmutableString(const ImmutableString& other) 
{

	copyFrom(other);

}

ImmutableString::~ImmutableString() 
{

	free();

}

int ImmutableString::getSize() const
{

	return size;

}

std::ostream& operator << (std::ostream& os, const ImmutableString& other) 
{

	os << other.data;
	return os;

}

bool operator  <(const ImmutableString& lhs, const ImmutableString& rhs)
{

	return strcmp(lhs.getData(), rhs.getData()) < 0;

}

bool operator <= (const ImmutableString& lhs, const ImmutableString& rhs)
{

	return strcmp(lhs.getData(), rhs.getData()) <= 0;

}

bool operator >= (const ImmutableString& lhs, const ImmutableString& rhs)
{

	return strcmp(lhs.getData(), rhs.getData()) >= 0;

}

bool operator > (const ImmutableString& lhs, const ImmutableString& rhs)
{

	return strcmp(lhs.getData(), rhs.getData()) > 0;

}

bool operator == (const ImmutableString& lhs, const ImmutableString& rhs)
{

	return strcmp(lhs.getData(), rhs.getData()) == 0;

}

bool operator != (const ImmutableString& lhs, const ImmutableString& rhs)
{

	return strcmp(lhs.getData(), rhs.getData()) != 0;

}
