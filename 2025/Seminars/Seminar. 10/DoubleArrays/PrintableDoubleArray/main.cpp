#include "PrintableDoubleArray.h"

int main()
{

	double arr[5] = { 1 ,2 ,3 ,4 ,5 };
	PrintableDoubleArray pd1(arr, 5);
	std::cout << pd1 << std::endl;

	PrintableDoubleArray pd2;
	std::cin >> pd2;
	std::cout << pd2 << std::endl;

	return 0;

}

