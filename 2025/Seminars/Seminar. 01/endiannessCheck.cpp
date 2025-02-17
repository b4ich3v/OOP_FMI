#include <iostream>

bool isBigEndian() 
{

	union Helper
	{

		int number = 1;
		char ch;

	}obj;

	return (int)obj.ch == 1;

}

int main() 
{

	if (isBigEndian()) 
	{

		std::cout << "Big Endian";

	}
	else
	{

		std::cout << "Little Endian";

	}

	return 0;

}
