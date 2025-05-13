#include "Employee.h"
#pragma once

class Engineer: virtual public Employee
{
private:

	MyString techSpecialization;

public:

	Engineer(const MyString& name, const MyString& techSpecialization);

	void printInfo() const override;

};

