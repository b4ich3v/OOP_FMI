#include <iostream>
#include <climits>  
#include <cstring> 

enum class Error
{

	Invalid,
	Valid,
	Nullptr,
	EmptyText,
	Overflow

};

struct ResultPair
{
public:

	int number;
	Error error;

};

int toDigit(char ch)
{

	return ch - '0';

}

bool isValid(char ch)
{

	return ch >= '0' && ch <= '9';

}

ResultPair parse(const char* str)
{

	if (str == nullptr)
	{

		return { 0, Error::Nullptr };

	}

	if (strlen(str) == 0)
	{

		return { 0, Error::EmptyText };

	}

	int iter = 1;
	bool isNegative = false;
	int number = 0;

	for (int i = 0; i < strlen(str) - 1; i++) iter *= 10;

	if (*str == '-')
	{

		isNegative = true;
		str += 1;
		iter /= 10;

	}

	while (*str != '\0')
	{

		if (!isValid(*str))
		{

			return { 0, Error::Invalid };

		}
		else
		{

			if (number > (INT_MAX / 10) || (number == INT_MAX / 10 && toDigit(*str) > INT_MAX % 10))
			{

				return { 0, Error::Overflow };

			}

			number += toDigit(*str) * iter;
			iter /= 10;
			str += 1;

		}

	}

	if (isNegative)
	{

		number *= -1;
		return { number, Error::Valid };

	}

	return { number, Error::Valid };

}

int main()
{

	char str[17] = "123";
	ResultPair result = parse(str);

	std::cout << result.number << " ";

	switch (result.error)
	{

	case Error::Invalid: std::cout << "invalid"; break;
	case Error::Valid: std::cout << "valid"; break;
	case Error::Nullptr: std::cout << "nullptr"; break;
	case Error::Overflow: std::cout << "overflow"; break;
	case Error::EmptyText: std::cout << "emptyText"; break;

	}

	return 0;

}
