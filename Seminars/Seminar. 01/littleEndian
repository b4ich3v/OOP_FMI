#include <iostream>

bool isLittleEndian()
{

	union endiannessTest 
	{

		uint32_t number = 1;
		unsigned char bytes[4];

	} myTest;

	return myTest.bytes[0];

}

int main()
{

	std::cout << isLittleEndian();
	return 0;

}
