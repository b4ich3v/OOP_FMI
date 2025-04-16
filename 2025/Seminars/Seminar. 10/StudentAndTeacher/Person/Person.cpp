#include "Person.h"

void Person::free() 
{

	delete[] name;
	name = nullptr;
	age = 0;

}

void Person::copyFrom(const Person& other)
{

	name = new char[strlen(other.name) + 1];
	strncpy(name, other.name, strlen(other.name));
	name[strlen(other.name)] = '\0';

	age = other.age;

}

void Person::moveTo(Person&& other) 
{

	name = other.name;
	age = other.age;

	other.name = nullptr;
	other.age = 0;

}

Person::Person(const Person& other) 
{

	copyFrom(other);

}

Person::Person(const char* name, int age) 
{

	this->name = new char[strlen(name) + 1];
	strncpy(this->name, name, strlen(name));
	this->name[strlen(name)] = '\0';

	this->age = age;

}

Person::Person(Person&& other) noexcept 
{

	moveTo(std::move(other));

}

Person& Person::operator = (const Person& other) 
{

	if (this != &other) 
	{

		free();
		copyFrom(other);

	}

	return *this;

}

Person& Person::operator = (Person&& other) noexcept 
{

	if (this != &other) 
	{

		free();
		moveTo(std::move(other));

	}

	return *this;

}

Person::~Person() 
{

	free();

}

const char* Person::getName() const 
{

	return name;

}

int Person::getAge() const 
{

	return age;

}
