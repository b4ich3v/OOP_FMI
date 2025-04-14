#include "WrapperInt.h"

WrapperInt::WrapperInt(int number): number(number) {}

WrapperInt& WrapperInt::operator += (const WrapperInt& other) 
{

	number += other.number;
	return *this;

}

WrapperInt& WrapperInt::operator -= (const WrapperInt& other) 
{

	number -= other.number;
	return *this;

}

WrapperInt& WrapperInt::operator *= (const WrapperInt& other) 
{

	number *= other.number;
	return *this;

}

WrapperInt& WrapperInt::operator /= (const WrapperInt& other) 
{

	number /= other.number;
	return *this;

}

WrapperInt& WrapperInt::operator ^= (int degree) 
{

	if (degree < 0) throw std::logic_error("Error");

	int result = 1;

	for (int i = 0; i < degree; i++)
	{

		result *= number;

	}

	WrapperInt newNum(result);
	*this = newNum;
	return *this;

}

std::ostream& operator << (std::ostream& os, const WrapperInt& number) 
{

	os << number.number;
	return os;

}

std::istream& operator >> (std::istream& is, WrapperInt& number) 
{

	is >> number.number;
	return is;

}

WrapperInt operator + (const WrapperInt& number1, const WrapperInt& number2) 
{

	WrapperInt result(number1);
	result += number2;

	return result;

}

WrapperInt operator - (const WrapperInt& number1, const WrapperInt& number2) 
{

	WrapperInt result(number1);
	result -= number2;

	return result;

}

WrapperInt operator * (const WrapperInt& number1, const WrapperInt& number2)
{

	WrapperInt result(number1);
	result *= number2;

	return result;

}

WrapperInt operator / (const WrapperInt& number1, const WrapperInt& number2) 
{

	WrapperInt result(number1);
	result /= number2;

	return result;

}

WrapperInt::operator int() 
{

	return number;

}

WrapperInt::operator double() 
{

	return number;

}

WrapperInt::operator bool() 
{

	return number > 1;

}

WrapperInt::operator char() 
{

	return (char)number;

}
