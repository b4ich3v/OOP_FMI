#include "TechManager.h"

TechManager::TechManager(const MyString& name, const MyString& projectName, const MyString& techSpecialization):
	Employee(name), Manager(name, projectName), Engineer(name, techSpecialization) {}

void TechManager::printInfo() const 
{

	Manager::printInfo();

}

void TechManager::assignTask(const MyString& task) const 
{

	std::cout << " TechManager " << getName() <<" assigns task: " << task << std::endl;

}
