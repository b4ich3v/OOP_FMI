#include <iostream>
#include <fstream>

void manipulateArr(const char* fileName1, const char* fileName2)
{

	std::ifstream file1(fileName1);
	std::ofstream file2(fileName2);

	if (!file1.is_open() || !file2.is_open()) return;

	int number1, number2 = 0;
	file1 >> number1 >> number2;

	int res1 = number1 * number2;
	int res2 = number1 + number2;

	file2 << res1 << " " << res2;

	file1.close();
	file2.close();

}

int main()
{
	manipulateArr("../test1.txt", "../test2.txt");

	return 0;

}
