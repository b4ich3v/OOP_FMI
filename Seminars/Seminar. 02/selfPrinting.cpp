#include <iostream>
#include <fstream>

void selfPrinting(const char* fileName)
{

	std::ifstream file(fileName);

	if (!file.is_open())
	{

		std::cout << "Error";
		return;

	}

	char ch;

	while (file.get(ch))
	{

		std::cout << ch;

	}

	if (file.bad()) 
	{

		std::cout << "Error: Reading from file failed" << std::endl;

	}

	file.close();
	return;

}

int main() 
{

	const char fileName[] = "dada.cpp";
	selfPrinting(fileName);

	return 0;

}
