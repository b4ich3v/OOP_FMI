#pragma once
#include "stringPool.h"
#include <iostream>

class ImmutableString
{
private:

	const char* data;

	int size;

	static StringPool pool;

public:

	ImmutableString(const char* data);

	ImmutableString(const ImmutableString& other);

	ImmutableString& operator = (const ImmutableString& other) = delete;

	~ImmutableString();

	int length() const;

	char operator [] (int index) const;

	const char* c_str() const;

	void debug() const;

};

std::ostream& operator << (std::ostream& os, const ImmutableString& str);

bool operator < (const ImmutableString& lhs, const ImmutableString& rhs);

bool operator <= (const ImmutableString& lhs, const ImmutableString& rhs);

bool operator >= (const ImmutableString& lhs, const ImmutableString& rhs);

bool operator > (const ImmutableString& lhs, const ImmutableString& rhs);

bool operator == (const ImmutableString& lhs, const ImmutableString& rhs);

bool operator != (const ImmutableString& lhs, const ImmutableString& rhs);
