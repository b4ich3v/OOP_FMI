#pragma once
#include <iostream>

class WrapperInt
{
private:

	int number = 0;

public:

	WrapperInt() = delete;

	WrapperInt(int number);

	WrapperInt& operator += (const WrapperInt& other);

	WrapperInt& operator -= (const WrapperInt& other);

	WrapperInt& operator *= (const WrapperInt& other);

	WrapperInt& operator /= (const WrapperInt& other);

	WrapperInt& operator ^= (int degree);

	friend std::ostream& operator << (std::ostream& os, const WrapperInt& number);

	friend std::istream& operator >> (std::istream& is, WrapperInt& number);

	explicit operator int();

	explicit operator double();

	explicit operator bool();

	explicit operator char();

	int getNumberValue() const;

};

WrapperInt operator + (const WrapperInt& number1, const WrapperInt& number2);

WrapperInt operator - (const WrapperInt& number1, const WrapperInt& number2);

WrapperInt operator * (const WrapperInt& number1, const WrapperInt& number2);

WrapperInt operator / (const WrapperInt& number1, const WrapperInt& number2);

bool operator > (const WrapperInt& number1, const WrapperInt& number2);

bool operator >= (const WrapperInt& number1, const WrapperInt& number2);

bool operator < (const WrapperInt& number1, const WrapperInt& number2);

bool operator <= (const WrapperInt& number1, const WrapperInt& number2);

bool operator == (const WrapperInt& number1, const WrapperInt& number2);

bool operator != (const WrapperInt& number1, const WrapperInt& number2);
