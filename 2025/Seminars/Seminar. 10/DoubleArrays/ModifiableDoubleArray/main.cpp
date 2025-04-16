#include "ModifiableDoubleArray.h"

int main()
{

	double array[5] = { 1, 2, 3, 4, 5 };
	ModifiableDoubleArray md(array, 5);

	md.push_back(1);
	std::cout << md[5] << std::endl;

	md.pop_back();
	std::cout << md[4] << std::endl;

	std::cout << md.last() << std::endl;

	return 0;

}

