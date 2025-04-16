#include "SaveableDoubleArray.h"

int main()
{

	double arr[5] = { 1 ,2 ,3 ,4 ,5 };
	SaveableDoubleArray sd1(arr, 5);

	try
	{

		std::ofstream file1("result.dat", std::ios::binary);
		sd1.saveToFile(file1);

		std::ifstream file2("result.dat", std::ios::binary);
		SaveableDoubleArray sd2;
		sd2.readFromFile(file2);

		std::cout << (sd1 == sd2) << std::endl;

	}
	catch (const std::exception& e)
	{

		std::cout << e.what() << std::endl;

	}

	return 0;

}

