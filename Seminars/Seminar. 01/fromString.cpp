#include <iostream>

bool isDigit(char ch)
{

	return ch >= '0' && ch <= '9';

}

enum ErrorCode
{

	Ok,
	Nullptr,
	InvalidString,
	Overflow

};

struct ResultPair 
{

	int number;
	ErrorCode code;

};

ResultPair fromString(const char* string)
{

    if (string == nullptr)
    {

        return { -1, ErrorCode::Nullptr };

    }

    bool isNegative = (*string == '-');

    if (isNegative)
    {

        string++;

    }

    int result = 0;

    while (*string != '\0')
    {

        if (!isDigit(*string))
        {

            return { -1, ErrorCode::InvalidString };

        }

        int currDigit = *string - '0';

        if (result > (INT_MAX - currDigit) / 10)
        {

            return { -1, ErrorCode::Overflow };

        }

        result = result * 10 + currDigit;
        string++;

    }

    if (isNegative)
    {

        return { -result, ErrorCode::Ok };

    }
    else
    {

        return { result, ErrorCode::Ok };

    }

}

int main()
{

	ResultPair pair = fromString("1237346723");

	switch (pair.code)
	{

	case ErrorCode::Ok:
		std::cout << pair.number;
		break;
	case ErrorCode::Nullptr:
		std::cout << "nullptr";
		break;
	case ErrorCode::InvalidString:
		std::cout << "invalid string";
		break;
	case ErrorCode::Overflow:
		std::cout << "overflow";
		break;
	default:
		std::cout << "Unknown error";
		break;

	}
	
	return 0;

}
