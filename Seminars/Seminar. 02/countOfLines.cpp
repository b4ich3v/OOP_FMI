#include <iostream>
#include <fstream>

int countOfLines(const char* fileName)
{

	std::ifstream file(fileName);

	if (!file.is_open()) 
	{

		std::cout << "Error";
		return -1;

	}

	int count = 0;
	char buff[1024];

	while (file.getline(buff, 1024))
	{

		count++;

	}

	file.close();
	return count;

}


int main() 
{

	const char fileName[] = "dada.cpp";
	std::cout << countOfLines(fileName);

	return 0;

}
