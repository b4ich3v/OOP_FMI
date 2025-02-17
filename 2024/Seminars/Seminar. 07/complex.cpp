#include <iostream>
#include "complex.h"

Complex::Complex() 
{

	real = 0;
	imaginary = 0;

}

Complex::Complex(double r, double i)
{

	this->real = r;
	this->imaginary = i;

}

Complex& Complex::operator += (const Complex& other) 
{

	real += other.real;
	imaginary += other.imaginary;

	return *this;

}

Complex& Complex::operator -= (const Complex& other)
{

	real += other.real;
	imaginary += other.imaginary;

	return *this;

}

Complex& Complex::operator*=(const Complex& other)
{

	double tempReal = real * other.real - imaginary * other.imaginary;
	double tempImaginary = real * other.imaginary + imaginary * other.real;
	real = tempReal;
	imaginary = tempImaginary;

	return *this;

}

Complex& Complex::operator /= (const Complex& other)
{

	if (other.real == 0 && other.imaginary == 0)
	{

		throw std::logic_error("Error");

	}

	Complex Conjugated = other.getConjugated(); 
	Complex otherCopy(other);

	*this *= Conjugated;
	otherCopy *= Conjugated; 

	if (otherCopy.real != 0)
	{

		real /= otherCopy.real;
		imaginary /= otherCopy.real;

	}

	return *this;

}

double Complex::getReal() const
{

	return real;

}

double Complex::getIm() const
{

	return imaginary;

}

void Complex::setReal(double r)
{

	this->real = r;

}

void Complex::setIm(double i)
{

	this->imaginary = i;

}

Complex Complex::getConjugated() const 
{

	Complex result(*this);
	result.imaginary *= -1;

	return result;

}

std::ostream& operator << (std::ostream& os, const Complex& other)
{

	os << other.real;
	os << " ";
	os << other.imaginary;

	return os;

}

std::istream& operator >> (std::istream& is, Complex& other)
{

	is >> other.real;
	is >> other.imaginary;

	return is;

}

bool operator == (const Complex& lhs, const Complex& rhs)
{

	return lhs.getReal() == rhs.getReal() && lhs.getIm() == rhs.getIm();

}

bool operator != (const Complex& lhs, const Complex& rhs)
{

	return !(lhs == rhs);

}

Complex operator + (const Complex& lhs, const Complex& rhs)
{

	Complex result(lhs);
	result += rhs;

	return result;

}

Complex operator - (const Complex& lhs, const Complex& rhs)
{

	Complex result(lhs);
	result -= rhs;

	return result;

}

Complex operator * (const Complex& lhs, const Complex& rhs)
{

	Complex result(lhs);
	result *= rhs;

	return result;

}

Complex operator / (const Complex& lhs, const Complex& rhs)
{

	Complex result(lhs);
	result /= rhs;

	return result;

}
