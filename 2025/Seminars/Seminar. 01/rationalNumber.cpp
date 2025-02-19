#include <iostream>

int gcd(int number1, int number2)
{

	int size = std::min(number1, number2);
	int result = 0;

	for (int i = 2; i <= size; i++)
	{

		if (!(number1 % i) && !(number2 % i)) result = i;

	}

	if (result == 0) return 1;
	return result;

}

int lcm(int number1, int number2) 
{

	return (number1 / gcd(number1, number2)) * number2;

}

struct Rational
{
public:

	int nom;
	int denom;

};

Rational adding(const Rational& r1, const Rational& r2) 
{

	int LCM = lcm(r1.denom, r2.denom); 
	int h1 = LCM / r1.denom;
	int h2 = LCM / r2.denom;
	int newNom = h1 * r1.nom + h2 * r2.nom;
	return { newNom, LCM };

}

Rational reverse(const Rational& r) 
{

	return { r.denom, r.nom };

}

Rational subtract(const Rational& r1, const Rational& r2) 
{

	Rational newR2 = { r2.nom, -r2.denom };
	return adding(r1, newR2);

}

Rational multiplication(const Rational& r1, const Rational& r2)
{

	int newNom = r1.nom * r2.nom;
	int newDenom = r1.denom * r2.denom;
	newNom /= gcd(newNom, newDenom);
	newDenom /= gcd(newNom, newDenom);

	return { newNom, newDenom };

}

Rational division(const Rational& r1, const Rational& r2) 
{

	return multiplication(r1, reverse(r2));

}

bool isValid(const Rational& r) 
{

	return r.denom != 0;

}

bool isInteger(const Rational& r)
{

	return !(r.nom % r.denom);

}
