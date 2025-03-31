#include "StringPool.h"
#pragma once

class ImmutableString
{
private:

	char* data = nullptr;
	int size = 0;
	static StringPool pool;

	void copyFrom(const ImmutableString& data);

	void free();

public:

	ImmutableString() = delete;

	ImmutableString(const char* data);

	ImmutableString(const ImmutableString& other);

	ImmutableString& operator = (const ImmutableString& other) = delete;

	~ImmutableString();

	int getSize() const;

	const char& operator [] (int index) const;

	const char* getData() const;

	friend std::ostream& operator << (std::ostream& os, const ImmutableString& other);

};

bool operator < (const ImmutableString& lhs, const ImmutableString& rhs);

bool operator <= (const ImmutableString& lhs, const ImmutableString& rhs);

bool operator >= (const ImmutableString& lhs, const ImmutableString& rhs);

bool operator > (const ImmutableString& lhs, const ImmutableString& rhs);

bool operator == (const ImmutableString& lhs, const ImmutableString& rhs);

bool operator != (const ImmutableString& lhs, const ImmutableString& rhs);
