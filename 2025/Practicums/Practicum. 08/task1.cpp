#include <iostream>
#include <cstring>

class ComplexNumber 
{
private:

	double re = 0;
	double im = 0;

public:

	ComplexNumber(double real, double imaginary): re(real), im(imaginary) {}

	ComplexNumber& operator += (const ComplexNumber & other) 
	{

		re += other.re;
		im += other.im;

		return *this;

	}

	ComplexNumber& operator -= (const ComplexNumber& other)
	{

		re -= other.re;
		im -= other.im;

		return *this;

	}

	ComplexNumber& operator *= (const ComplexNumber& other)
	{

		double newReal = re * other.re - (im * other.im);
		double newIm = re * other.im + im * other.re;

		re = newReal;
		im = newIm;

		return *this;

	}

	ComplexNumber& operator /= (const ComplexNumber& other)
	{

		ComplexNumber nom = *this;
		ComplexNumber denom = other;
		ComplexNumber helper = ~(denom);

		nom *= helper;
		denom *= helper;

		int realPartFromDenom = denom.re;
		nom.re /= realPartFromDenom;
		nom.im /= realPartFromDenom;
		*this = nom;

		return *this;

	}

	friend ComplexNumber operator ~ (const ComplexNumber& number) 
	{

		return ComplexNumber(number.re, -1 * number.im);

	}

	friend std::ostream& operator << (std::ostream& os, const ComplexNumber& number)
	{

		os << number.re << "+";
		os << "(" << number.im << "*i" << ")";

		return os;

	}

	friend std::istream& operator >> (std::istream& is, ComplexNumber& number)
	{

		is >> number.re;
		is.ignore(2);
		is >> number.im;
		is.ignore(3);

		return is;

	}

	friend bool operator == (const ComplexNumber & num1, const ComplexNumber & num2)
	{

		if (num1.re == num2.re) 
		{

			return num1.im != num2.im;

		}
		
		return num1.re != num2.re;

	}

};

ComplexNumber operator + (const ComplexNumber& num1, const ComplexNumber& num2) 
{

	ComplexNumber result(num1);
	result += num2;

	return result;

}

ComplexNumber operator - (const ComplexNumber& num1, const ComplexNumber& num2)
{

	ComplexNumber result(num1);
	result -= num2;

	return result;

}

ComplexNumber operator * (const ComplexNumber& num1, const ComplexNumber& num2)
{

	ComplexNumber result(num1);
	result *= num2;

	return result;

}

ComplexNumber operator / (const ComplexNumber& num1, const ComplexNumber& num2)
{

	ComplexNumber result(num1);
	result /= num2;

	return result;

}

int main()
{

	ComplexNumber number1(1, 1);
	ComplexNumber number2(16, -5);
	ComplexNumber number3(11, 9);
	ComplexNumber number4(3, -1);

	std::cout << number1 + number2 << std::endl;
	std::cout << number1 - number2 << std::endl;
	std::cout << number1 * number4 << std::endl;
	std::cout << number2 / number3 << std::endl;

	return 0;

}
