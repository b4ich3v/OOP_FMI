#include "MyString.h"
#pragma once

class GrString: public MyString
{
public:

	GrString();

	GrString(const char* data);

	GrString& operator += (const GrString& other);

	GrString& operator /= (const GrString& other);

	friend std::ostream& operator << (std::ostream& os, const GrString& other);

	friend std::istream& operator >> (std::istream& is, GrString& other);

	bool operator == (const GrString& other) const;

};

GrString operator + (const GrString& left, const GrString& right);

GrString operator / (const GrString& left, const GrString& right);

