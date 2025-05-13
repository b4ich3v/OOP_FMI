#include "Manager.h"

Manager::Manager(const MyString& name, const MyString& projectName) :
	Employee(name) , projectName(projectName) {}

void Manager::printInfo() const 
{

	std::cout << getName();
	std::cout << projectName;
	std::cout << std::endl;

}
