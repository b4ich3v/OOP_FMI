#include <iostream>
#include <fstream>

int getFileSize(std::ifstream& is)
{

	if (!is.is_open()) 
	{

		std::cout << "Error";
		return -1;

	}

	int currPosition = is.tellg();
	is.seekg(0, std::ios::end);
	int size = is.tellg();
	is.seekg(currPosition, std::ios::beg);

	return size;

}

int main() 
{

	std::ifstream file("example.txt", std::ios::binary);

	if (!file)
	{

		std::cout << "Error opening file!" << std::endl;
		return 1;

	}

	std::streampos fileSize = getFileSize(file);

	if (fileSize != -1) 
	{

		std::cout << "File size: " << fileSize << " bytes" << std::endl;

	}

	file.close();
	return 0;

}

