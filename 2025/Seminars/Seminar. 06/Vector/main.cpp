#include "Vector.h"

int main() 
{

	int arr1[4] = { 1, 2, 3, 4 };
	int arr2[4] = { -1, 76, 31, 0 };

	Vector v1(arr1, 4);
	Vector v2(arr2, 4);
	Vector v3;

	v1 += v2;
	std::cout << v1 << std::endl;

	v3.push(1);
	v3.push(1);
	v3.push(99);

	std::cout << v3 << std::endl;

	Vector multipliedVector = v3 * 2;
	std::cout << multipliedVector << std::endl;

	multipliedVector[2] = -111;
	std::cout << multipliedVector << std::endl;

	multipliedVector.pop();
	std::cout << multipliedVector << std::endl;

	return 0;
	
}
