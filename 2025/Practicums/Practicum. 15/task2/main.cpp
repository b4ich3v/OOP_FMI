#include <iostream>
#include "GrString.h"

int main()
{

	GrString str1("ABCDEF");
	GrString str2("BCDGHJ");

	std::cout << str1 << std::endl;
	std::cout << (str1 / str2) << std::endl;

	str1 += str2;
	std::cout << str1;

	return 0;

}
