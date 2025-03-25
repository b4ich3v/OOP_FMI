#include <iostream>
#pragma once

class ComplexNumber
{
private:

	double real = 0;
	double imaginary = 0;

	void setRealPart(double real);

	void setImaginaryPart(double imaginary);

	ComplexNumber getConjugate() const;

public:

	ComplexNumber() = default;

	ComplexNumber(const ComplexNumber& other);

	ComplexNumber(double real, double imaginary);

	double getRealPart() const;

	double getImaginaryPart() const;

	ComplexNumber& operator = (const ComplexNumber& other);

	ComplexNumber& operator *= (const ComplexNumber& other);

	ComplexNumber& operator += (const ComplexNumber& other);

	ComplexNumber& operator -= (const ComplexNumber& other);

	ComplexNumber& operator /= (const ComplexNumber& other);

	ComplexNumber& operator ^= (int power);

	friend std::ostream& operator << (std::ostream& os, const ComplexNumber& number);

	friend std::istream& operator >> (std::istream& is, ComplexNumber& number);

};

ComplexNumber operator * (const ComplexNumber& left, const ComplexNumber& right);

ComplexNumber operator + (const ComplexNumber& left, const ComplexNumber& right);

ComplexNumber operator - (const ComplexNumber& left, const ComplexNumber& right);

ComplexNumber operator / (const ComplexNumber& left, const ComplexNumber& right);

ComplexNumber operator ^ (const ComplexNumber& number, int power);

bool operator == (const ComplexNumber& left, const ComplexNumber& right);

bool operator != (const ComplexNumber& left, const ComplexNumber& right);
