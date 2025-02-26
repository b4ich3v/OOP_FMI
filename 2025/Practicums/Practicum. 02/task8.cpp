#include <iostream>
#include <fstream>

bool isOdd(int number)
{

	return number & 0x1;

}

void manipulateArr(const char* fileName1, const char* fileName2)
{

	std::ifstream file1(fileName1);
	std::ofstream file2(fileName2);

	if (!file1.is_open() || !file2.is_open()) return;

	int number = 0;

	while (true)
	{

		file1 >> number;
		if (isOdd(number)) file2 << number << " ";

		if (file1.eof()) break;

	}


	file1.close();
	file2.close();

}

int main()
{
	manipulateArr("../test1.txt", "../test2.txt");

	return 0;

}
