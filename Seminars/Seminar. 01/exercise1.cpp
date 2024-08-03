#include <iostream>

void swap(int& a, int& b)
{

	int temp = a;
	a = b;
	b = temp;

}


int minOfTwoNumbers(int number1, int number2)
{

	return (number1 < number2) ? number1 : number2;

}

int gcd(int number1, int number2)
{

	int result = minOfTwoNumbers(number1, number2);

	while (result > 0) 
	{

		if (number1 % result == 0 && number2 % result == 0)
		{

			break;

		}

		result--;

	}

	return result;

}

int lcm(int number1, int number2)
{

	return (number1 / gcd(number1, number2)) * number2;

}

struct Rational
{

	int numerator;
	int denominator;

};

void normalize(Rational& r)
{

	int del = gcd(r.denominator, r.numerator);
	r.denominator /= del;
	r.numerator /= del;

}

Rational add(Rational r1,  Rational r2) 
{

	int newDenominator = lcm(r1.denominator, r2.denominator);
	int newNumerator = r1.numerator * (newDenominator / r1.denominator)
		             + r2.numerator * (newDenominator / r2.denominator);
		
	Rational toReturn;
	toReturn.numerator = newNumerator;
	toReturn.denominator = newDenominator;
	
	return toReturn;

}

Rational subtract(Rational r1, const Rational& r2)
{

	int newDenominator = lcm(r1.denominator, r2.denominator);
	int newNumerator = r1.numerator * (newDenominator / r1.denominator) 
		             - r2.numerator * (newDenominator / r2.denominator);

	Rational toReturn;
	toReturn.numerator = newNumerator;
	toReturn.denominator = newDenominator;

	return toReturn;

}

Rational multiply(Rational r1, const Rational r2) 
{

	int newDenominator = r1.denominator * r2.denominator;
	int newNumerator = r1.numerator * r2.numerator;

	int gcdOfNomAndDom = gcd(newDenominator, newNumerator);
	newDenominator /= gcdOfNomAndDom;
	newNumerator /= gcdOfNomAndDom;

	Rational toReturn;
	toReturn.numerator = newNumerator;
	toReturn.denominator = newDenominator;

	return toReturn;

}

void swapNumAndDen(Rational& r)
{

	swap(r.numerator, r.denominator);

}

Rational divide(Rational r1, Rational r2)
{

	swapNumAndDen(r2);
	return multiply(r1, r2);

}

bool areEqual(Rational r1, Rational r2)
{

	normalize(r1);
	normalize(r2);

	return ((r1.numerator == r2.numerator) && (r1.denominator == r2.denominator));

}

int main() 
{

	Rational r1 = { 2, 3 };
	Rational r2 = { 4, 5 };

	Rational sum = add(r1, r2);
	std::cout << "Sum: " << sum.numerator << "/" << sum.denominator << std::endl;

	Rational difference = subtract(r1, r2);
	std::cout << "Difference: " << difference.numerator << "/" << difference.denominator << std::endl;

	Rational product = multiply(r1, r2);
	std::cout << "Product: " << product.numerator << "/" << product.denominator << std::endl;

	Rational quotient = divide(r1, r2);
	std::cout << "Quotient: " << quotient.numerator << "/" << quotient.denominator << std::endl;

	return 0;

}
