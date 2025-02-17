#include "studentExample.h"

Student::Student(char* name, int age)
{

	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
	this->age = age;

}

const char* Student::getName() const
{

	return name;

}
