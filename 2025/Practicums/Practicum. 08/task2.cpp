#include <iostream>
#include <cstring>

namespace HELPERS
{

	int GCD(int number1, int number2)
	{

		int iter = std::min(number1, number2);

		for (int i = 2; i <= iter; i++)
		{

			if (!(number1 % i) && !(number2 % i)) return i;

		}

		return 1;

	}

	int LCM(int number1, int number2)
	{

		return (number1 * number2) / GCD(number1, number2);

	}

}

class RationalNumber
{
private:

	int nom = 1;
	int denom = 1;

public:

	RationalNumber(int nominator, int denominator) : nom(nominator), denom(denominator) {}

	RationalNumber& operator += (const RationalNumber& other)
	{

		int newDenom = HELPERS::LCM(denom, other.denom);
		int newNom = (newDenom / denom) * nom + (newDenom / other.denom) * other.nom;

		newDenom /= HELPERS::GCD(newNom, newDenom);
		newNom /= HELPERS::GCD(newNom, newDenom);

		nom = newNom;
		denom = newDenom;

		return *this;

	}

	RationalNumber& operator -= (const RationalNumber& other)
	{

		int newDenom = HELPERS::LCM(denom, other.denom);
		int newNom = (newDenom / denom) * nom - (newDenom / other.denom) * other.nom;

		newDenom /= HELPERS::GCD(newNom, newDenom);
		newNom /= HELPERS::GCD(newNom, newDenom);

		nom = newNom;
		denom = newDenom;

		return *this;

	}

	RationalNumber& operator *= (const RationalNumber& other)
	{

		int newDenom = denom * other.denom;
		int newNom = nom * other.nom;

		newDenom /= HELPERS::GCD(newNom, newDenom);
		newNom /= HELPERS::GCD(newNom, newDenom);

		nom = newNom;
		denom = newDenom;

		return *this;

	}

	RationalNumber& operator /= (const RationalNumber& other)
	{

		*this *= ~(other);
		return *this;

	}

	RationalNumber operator ++ (int dummy)
	{

		RationalNumber result(*this);
		RationalNumber one(1, 1);
		*this += one;

		return result;

	}

	RationalNumber& operator ++ ()
	{

		RationalNumber one(1, 1);
		*this += one;

		return *this;

	}

	RationalNumber operator -- (int dummy)
	{

		RationalNumber result(*this);
		RationalNumber one(1, 1);
		*this -= one;

		return result;

	}

	RationalNumber& operator -- ()
	{

		RationalNumber one(1, 1);
		*this -= one;

		return *this;

	}

	friend RationalNumber operator ~ (const RationalNumber& number)
	{

		return RationalNumber(number.denom, number.nom);

	}

	friend RationalNumber operator ! (const RationalNumber& number)
	{

		return RationalNumber(-1 * number.nom, number.denom);

	}

	friend std::ostream& operator << (std::ostream& os, const RationalNumber& number)
	{

		os << number.nom << "/" << number.denom;
		return os;

	}

	friend std::istream& operator >> (std::istream& is, RationalNumber& number)
	{

		is >> number.nom;
		is.ignore(1);
		is >> number.denom;
		return is;

	}

};

RationalNumber operator + (const RationalNumber& num1, const RationalNumber& num2)
{

	RationalNumber result(num1);
	result += num2;

	return result;

}

RationalNumber operator - (const RationalNumber& num1, const RationalNumber& num2)
{

	RationalNumber result(num1);
	result -= num2;

	return result;

}

RationalNumber operator * (const RationalNumber& num1, const RationalNumber& num2)
{

	RationalNumber result(num1);
	result *= num2;

	return result;

}

RationalNumber operator / (const RationalNumber& num1, const RationalNumber& num2)
{

	RationalNumber result(num1);
	result /= num2;

	return result;

}

int main()
{

	RationalNumber number1(1, 1);
	RationalNumber number2(4, 9);
	RationalNumber number3(7, 6);
	RationalNumber number4(13, -1);

	std::cout << number1 + number4 << std::endl;
	std::cout << number1 - number4 << std::endl;
	std::cout << number2 + number3 << std::endl;
	std::cout << number2 / number1 << std::endl;

	number1--;
	std::cout << number1 << std::endl;
	number1++;

	std::cout << number1-- << std::endl;
	std::cout << number1 << std::endl;
	std::cout << --number1 << std::endl;

	return 0;

}
