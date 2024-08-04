#include <iostream>
#include <fstream>

void copyFile(const char* first, const char* second)
{

	std::ifstream file1(first);
	std::ofstream file2(second);

	if (!file1.is_open() || !file2.is_open())
	{

		std::cout << "Error";
		return;

	}

	while (true)
	{

		char ch = file1.get();

		if (file1.eof())
		{

			break;

		}

		if (file1.bad())
		{

			std::cout << "Error: Reading from file " << std::endl;
			break;

		}

		if (file2.bad()) 
		{

			std::cout << "Error: Writing to file " << std::endl;
			break;

		}

		file2 << ch;

	}

	file1.close();
	file2.close();

	return;

}

int main() 
{

	const char first[] = "dada.cpp";
	const char second[] = "second.txt";
	copyFile(first, second);

	return 0;

}
