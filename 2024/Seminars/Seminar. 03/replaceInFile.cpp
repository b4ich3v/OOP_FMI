#include <iostream>
#include <fstream>

void replaceInFile(char ch1, char ch2, std::fstream& file)
{

	if (!file.is_open())
	{

		std::cout << "Error";
		return;

	}

	char current = 'a';

	while (!file.eof())
	{

		file.read((char*)&current, sizeof(char));

		if (current == ch1)
		{

			file.seekg(-1, std::ios::cur);
			file.write((const char*)&ch2, sizeof(char));
			file.flush();

		}

	}

}

int main() 
{

	std::fstream file("example.txt", std::ios::in | std::ios::out | std::ios::binary);

	if (!file) 
	{

		std::cout << "Error opening file!" << std::endl;
		return 1;

	}

	replaceInFile('a', 'b', file);

	file.close();
	return 0;

}

