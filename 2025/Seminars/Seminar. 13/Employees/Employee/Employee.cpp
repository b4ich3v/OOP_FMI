#include "Employee.h"

int Employee::idMask = 0;

Employee::Employee(const MyString& name):
	name(name) 
{

	id = idMask;
	idMask += 1;

}

int Employee::getId() const 
{

	return id;

}

const MyString& Employee::getName() const
{

	return name;

}
