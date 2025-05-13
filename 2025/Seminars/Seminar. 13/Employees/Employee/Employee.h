#include "MyString.h"
#pragma once

class Employee
{
private:

	MyString name;
	int id = 0;
	static int idMask;

public:

	Employee(const MyString& name);

	virtual void printInfo() const = 0;

	virtual ~Employee() = default;

protected:

	const MyString& getName() const;

	int getId() const;

};

