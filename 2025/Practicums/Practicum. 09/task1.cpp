#include <iostream>
#include <fstream>
#include <cstring>

namespace HELPERS
{

	const int SIZE_FOR_REGISTER = 8;

	bool isDigit(char ch) 
	{

		return ch >= '0' && ch <= '9';

	}

	bool isUpper(char ch)
	{

		return ch >= 'A' && ch <= 'Z';

	}

}

class Registration 
{
private:

	char data[HELPERS::SIZE_FOR_REGISTER + 1];

	bool validation(const char* data) const
	{

		if (!(strlen(data) == HELPERS::SIZE_FOR_REGISTER || strlen(data) == HELPERS::SIZE_FOR_REGISTER - 1)) return false;
		if (!HELPERS::isUpper(data[0]) || !HELPERS::isUpper(data[strlen(data) - 1]) || !HELPERS::isUpper(data[strlen(data) - 2])) return false;
		
		bool pred = strlen(data) == HELPERS::SIZE_FOR_REGISTER;

		if (pred) 
		{


			for (int i = 2; i <= 5; i++)
			{

				if (!HELPERS::isDigit(data[i])) return false;
				
			}

			return true;

		}

		for (int i = 1; i <= 4; i++)
		{

			if (!HELPERS::isDigit(data[i])) return false;

		}

		return true;

	}

public:

	Registration() = delete;

	Registration(const char* data) 
	{

		if (!validation(data)) throw std::logic_error("Error");

		strncpy(this->data, data, strlen(data));
		this->data[strlen(data)] = '\0';

	}

	const char* getData() const 
	{

		return data;

	}

	friend bool operator == (const Registration& r1, const Registration& r2) 
	{

		return strcmp(r1.getData(), r2.getData()) == 0;

	}

	friend bool operator != (const Registration& r1, const Registration& r2)
	{

		return !(r1 == r2);

	}

};

int main()
{

	try
	{

		Registration r1("C1234AB");
		Registration r2("XY1111YX"); 
		Registration r3 = r1;

		std::cout << r1.getData() << std::endl;
		std::cout << r2.getData() << std::endl;
		std::cout << (r1 == r2) << std::endl;
		std::cout << (r1 == r3) << std::endl;

		Registration r4("111145");

	}
	catch (const std::exception& e)
	{

		std::cout << e.what() << std::endl;

	}
	

	return 0;

}
