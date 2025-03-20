#include "Student.h"

void Student::setName(const char* name)
{

	if (!name) return;

	delete[] this->name;
	this->name = new char[strlen(name) + 1];
	strncpy(this->name, name, strlen(name));
	this->name[strlen(name)] = '\0';

}

void Student::setQuote(const char* quote)
{

	if (!quote) return;

	strncpy(this->quote, quote, strlen(quote));
	this->quote[strlen(quote)] = '\0';

}

void Student::setGrades(const double* grades, int size)
{

	if (!grades || size <= 0) return;
	if (size > capacity) resize(size);

	for (int i = 0; i < size; i++)
	{

		this->grades[i] = grades[i];

	}

	this->size = size;

}

void Student::free()
{

	delete[] name;
	name = nullptr;

	delete[] grades;
	grades = nullptr;

	size = 0;
	capacity = 8;

}

void Student::copyFrom(const Student& other)
{

	this->capacity = other.capacity;
	this->grades = new double[other.capacity];
	setName(other.name);
	setQuote(other.quote);
	setGrades(other.grades, other.size);

}

void Student::resize(int newCapacity)
{

	if (newCapacity <= capacity) return;

	double* newGrades = new double[newCapacity];

	for (int i = 0; i < size; i++)
	{

		newGrades[i] = grades[i];

	}

	delete[] grades;
	grades = newGrades;
	capacity = newCapacity;

}

Student::Student()
{

	strncpy(quote, "DEFAULT", strlen("DEFAULT"));
	quote[strlen("DEFAULT")] = '\0';
	name = nullptr;
	capacity = 8;
	size = 0;

	grades = new double[capacity];

}

Student::Student(const char* name, const char* quote, const double* grades, int size)
{

	capacity = size > 8 ? size : 8;
	this->name = nullptr;
	this->grades = new double[capacity];

	setName(name);
	setQuote(quote);
	setGrades(grades, size);

}

Student::Student(const Student& other)
{

	copyFrom(other);

}

Student& Student::operator = (const Student& other)
{

	if (this != &other)
	{

		free();
		copyFrom(other);

	}

	return *this;

}

Student::~Student()
{

	free();

}

void Student::addGrade(double newGrade)
{

	if (newGrade < 2 || newGrade > 6) return;
	if (size >= capacity) resize(capacity * 2);

	grades[size] = newGrade;
	size += 1;

}

const char* Student::getName() const
{

	return name;

}

const char* Student::getQuote() const
{

	return quote;

}

const double* Student::getGrades() const
{

	return grades;

}

void Student::printStudent() const
{

	std::cout << name << " ";
	std::cout << "'" << quote << "'" << " ";

	std::cout << "{ ";

	for (int i = 0; i < size; i++)
	{

		std::cout << grades[i] << " ";

	}

	std::cout << "}" << std::endl;

}
