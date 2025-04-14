#include "DynamicArrayOfPointers.h"

int main()
{

	WrapperInt number1 = 1;
	WrapperInt number2 = 2;
	WrapperInt number3 = 3;
	WrapperInt number4 = 4;
	WrapperInt number5 = 5;
	WrapperInt number6 = 6;
	WrapperInt number7 = 7;
	WrapperInt number8 = 8;
	WrapperInt number9 = 9;

	DynamicArrayOfPointers arr1;
	arr1.addInt(number1);
	arr1.addInt(number2);
	arr1.addInt(number3);
	arr1.addInt(number4);
	arr1.addInt(number5);
	arr1.addInt(number6);
	arr1.addInt(number7);
	arr1.addInt(number8);
	arr1.addInt(number9);
	std::cout << arr1 << std::endl;

	arr1.removeInt(0);
	arr1.removeInt(1);
	arr1.removeInt(5);
	std::cout << arr1 << std::endl;

	DynamicArrayOfPointers arr2;
	std::cin >> arr2;
	std::cout << arr2 << std::endl;

	DynamicArrayOfPointers copyOfArr2 = arr2;
	std::cout << copyOfArr2 << std::endl;

	return 0;

}
