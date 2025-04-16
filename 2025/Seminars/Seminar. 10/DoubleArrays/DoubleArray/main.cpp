#include "DoubleArray.h"

int main()
{

	double arr[5] = { 1 ,2 ,3 ,4 ,5 };
	DoubleArray db1(arr, 5);
	DoubleArray db2(arr, 5);

	std::cout << (db1 == db2) << std::endl;
	std::cout << db1.isEmpty() << std::endl;
	std::cout << db1[3] << std::endl;
	std::cout << db2.getSize() << std::endl;

	return 0;

}
