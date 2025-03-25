#include "ComplexNumber.h"

ComplexNumber::ComplexNumber(double real, double imaginary) 
{

	setRealPart(real);
	setImaginaryPart(imaginary);

}

ComplexNumber::ComplexNumber(const ComplexNumber& other) 
{

	setRealPart(other.real);
	setImaginaryPart(other.imaginary);

}

void ComplexNumber::setImaginaryPart(double imaginary) 
{

	this->imaginary = imaginary;

}

void ComplexNumber::setRealPart(double real)
{

	this->real = real;

}

double ComplexNumber::getRealPart() const 
{

	return real;

}

double ComplexNumber::getImaginaryPart() const
{

	return imaginary;

}

ComplexNumber ComplexNumber::getConjugate() const 
{

	return ComplexNumber(real, -imaginary);

}

ComplexNumber& ComplexNumber::operator = (const ComplexNumber& other)
{

	setRealPart(other.real);
	setImaginaryPart(other.imaginary);

	return *this;

}

ComplexNumber& ComplexNumber::operator += (const ComplexNumber& other)
{

	this->real += other.real;
	this->imaginary += other.imaginary;

	return *this;

}

ComplexNumber& ComplexNumber::operator -= (const ComplexNumber& other)
{

	this->real -= other.real;
	this->imaginary -= other.imaginary;

	return *this;

}

ComplexNumber& ComplexNumber::operator *= (const ComplexNumber& other)
{

	double newReal = this->real * other.real - (this->imaginary * other.imaginary);
	double newImaginary = this->imaginary * other.real + other.imaginary * this->real;

	ComplexNumber newNumber(newReal, newImaginary);
	*this = newNumber;

	return *this;

}

ComplexNumber& ComplexNumber::operator /= (const ComplexNumber& other)
{

	if (other.real == 0 && other.imaginary == 0) throw std::logic_error("Error");

	ComplexNumber denom = other.getConjugate();
	denom *= other;

	double actaulDenom = denom.real;
	*this *= other.getConjugate();

	this->real /= actaulDenom;
	this->imaginary /= actaulDenom;

	return *this;

}

ComplexNumber& ComplexNumber::operator ^= (int exponent)
{
	
	if (exponent == 0)
	{

		this->real = 1;
		this->imaginary = 0;
		return *this;

	}

	bool isNegative = (exponent < 0);
	if (isNegative) exponent = -exponent;
		
	ComplexNumber base = *this;
	ComplexNumber result(1, 0); 

	for (int i = 0; i < exponent; i++) result *= base;

	if (isNegative) result = ComplexNumber(1, 0) / result;

	*this = result;
	return *this;

}

ComplexNumber operator + (const ComplexNumber& left, const ComplexNumber& right)
{

	ComplexNumber result(left);
	result += right;

	return result;

}

ComplexNumber operator - (const ComplexNumber& left, const ComplexNumber& right)
{

	ComplexNumber result(left);
	result -= right;

	return result;

}

ComplexNumber operator * (const ComplexNumber& left, const ComplexNumber& right)
{

	ComplexNumber result(left);
	result *= right;

	return result;

}

ComplexNumber operator / (const ComplexNumber& left, const ComplexNumber& right)
{

	ComplexNumber result(left);
	result /= right;

	return result;

}

ComplexNumber operator ^ (const ComplexNumber& number, int power)
{

	ComplexNumber result(number);
	result ^= power;

	return result;

}

bool operator == (const ComplexNumber& left, const ComplexNumber& right) 
{

	return (left.getRealPart() == right.getRealPart()) && (left.getImaginaryPart() == right.getImaginaryPart());

}

bool operator != (const ComplexNumber& left, const ComplexNumber& right)
{

	return !(left == right);

}

std::ostream& operator << (std::ostream& os, const ComplexNumber& number) 
{

	os << '(';
	os << number.real;
	os << ',';
	os << number.imaginary;
	os << 'i';
	os << ')';
	os << std::endl;

	return os;

}

std::istream& operator >> (std::istream& is, ComplexNumber& number)
{

	char dummy;

	is >> dummy;
	is >> number.real;
	is >> dummy;
	is >> number.imaginary;
	is >> dummy;
	is >> dummy;
	is.ignore();

	return is;

}
