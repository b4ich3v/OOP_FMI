#include <iostream>

union ipAddress
{

	int number
	uint8_t parts[4];

};

int main()
{

	ipAddress ip;
	ip.number = 2563931973;
	std::cout << (unsigned int)ip.parts[0] << "." << (unsigned int)ip.parts[1]
		      << "." << (unsigned int)ip.parts[2] << "." << (unsigned int)ip.parts[3];

	return 0;

}
