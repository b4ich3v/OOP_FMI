#include "Employee.h"
#pragma once

class Manager: virtual public Employee
{
private:

	MyString projectName;

public:

	Manager(const MyString& name, const MyString& projectName);

	void printInfo() const override;

};

