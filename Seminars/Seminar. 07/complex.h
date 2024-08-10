#pragma once
#include <fstream>

class Complex 
{
private:

	double real;
	double imaginary;

public:

	Complex();

	Complex(double r, double i);

	double getReal() const;

	double getIm() const;

	void setReal(double r);

	void setIm(double i);

	Complex getConjugated() const; 

	Complex& operator += (const Complex& other);

	Complex& operator -= (const Complex& other);

	Complex& operator *= (const Complex& other);

	Complex& operator /= (const Complex& other);

	friend std::istream& operator >> (std::istream& is, Complex& other);

	friend std::ostream& operator << (std::ostream& os, const Complex& other);

};

Complex operator + (const Complex& lhs, const Complex& rhs);

Complex operator - (const Complex& lhs, const Complex& rhs);

Complex operator * (const Complex& lhs, const Complex& rhs);

Complex operator / (const Complex& lhs, const Complex& rhs);

bool operator == (const Complex& lhs, const Complex& rhs);

bool operator != (const Complex& lhs, const Complex& rhs);
