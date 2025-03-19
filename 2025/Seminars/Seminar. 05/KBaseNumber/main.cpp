#include "KBaseNumber.h"

int main()
{

	std::ofstream file1("../file.dat", std::ios::binary);

	KBaseNumber num1("CE9A", 16);
	num1.print(); 
	num1.saveToFile(file1);

	KBaseNumber num2 = num1;
	num2.convertTo(8);
	num2.print(); 

	std::cout << num1.compareWith(num2) << std::endl; 

	num2.update("1312", 4);
	std::cout << num2.compareWith(num1) << std::endl; 

	std::ifstream file2("../file.dat", std::ios::binary);

	KBaseNumber num3;
	num3.readFromFile(file2);
	num3.print(); 

	return 0;

}
