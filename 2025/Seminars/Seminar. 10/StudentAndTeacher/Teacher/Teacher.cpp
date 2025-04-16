#include "Teacher.h"

void Teacher::free() 
{

	for (int i = 0; i < countOfSubjects; i++)
	{

		delete[] subjects[i];
		subjects[i] = nullptr;

	}
	
	delete[] subjects;
	subjects = nullptr;
	countOfSubjects = 0;
	capacityForSubjects = 8;

}

void Teacher::copyFrom(const Teacher& other) 
{

	this->subjects = new char* [other.capacityForSubjects] {nullptr};
	this->countOfSubjects = other.countOfSubjects;
	this->capacityForSubjects = other.capacityForSubjects;

	for (int i = 0; i < countOfSubjects; i++)
	{

		this->subjects[i] = new char[strlen(other.subjects[i]) + 1];
		strncpy(this->subjects[i], other.subjects[i], strlen(other.subjects[i]));
		this->subjects[i][strlen(other.subjects[i])] = '\0';

	}

}

void Teacher::moveTo(Teacher&& other) 
{

	this->subjects = other.subjects;
	this->countOfSubjects = other.countOfSubjects;
	this->capacityForSubjects = other.capacityForSubjects;

	other.subjects = nullptr;
	other.countOfSubjects = 0;
	other.capacityForSubjects = 8;

}

void Teacher::resizeForSubjects(int newCapacity) 
{

	if (newCapacity <= capacityForSubjects) throw std::logic_error("Error");

	char** newData = new char* [newCapacity] {nullptr};

	for (int i = 0; i < countOfSubjects; i++)
	{

		newData[i] = subjects[i];

	}

	delete[] subjects;
	subjects = newData;
	capacityForSubjects = newCapacity;

}

Teacher::Teacher(const char* name, int age, const char* const* subjects, int countOfSubjects): Person(name, age)
{

	while (capacityForSubjects <= countOfSubjects) capacityForSubjects *= 2;

	this->subjects = new char* [capacityForSubjects] {nullptr};
	this->countOfSubjects = countOfSubjects;

	for (int i = 0; i < countOfSubjects; i++)
	{

		this->subjects[i] = new char[strlen(subjects[i]) + 1];
		strncpy(this->subjects[i], subjects[i], strlen(subjects[i]));
		this->subjects[i][strlen(subjects[i])] = '\0';

	}

}

Teacher::Teacher(const Teacher& other) 
{

	copyFrom(other);

}

Teacher::Teacher(Teacher&& other) noexcept 
{

	moveTo(std::move(other));

}

Teacher& Teacher::operator = (const Teacher& other) 
{

	if (this != &other) 
	{

		free();
		copyFrom(other);

	}

	return *this;

}

Teacher& Teacher::operator = (Teacher&& other) noexcept 
{

	if (this != &other)
	{

		free();
		moveTo(std::move(other));

	}

	return *this;

}

Teacher::~Teacher() 
{

	free();

}

const char* Teacher::getTeacherName() const 
{

	return getName();

}

int Teacher::getTeacherAge() const 
{

	return getAge();

}

const char* const* Teacher::getTeacherSubjects() const 
{

	return subjects;

}

int Teacher::getCountOfSubjects() const 
{

	return countOfSubjects;

}
