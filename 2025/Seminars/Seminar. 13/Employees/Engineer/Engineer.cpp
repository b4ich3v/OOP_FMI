#include "Engineer.h"

Engineer::Engineer(const MyString& name, const MyString& techSpecialization):
	Employee(name), techSpecialization(techSpecialization) {}

void Engineer::printInfo() const 
{

	std::cout << getName();
	std::cout << techSpecialization;
	std::cout << std::endl;

}
