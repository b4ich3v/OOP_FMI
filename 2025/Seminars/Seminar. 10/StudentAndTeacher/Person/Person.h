#include <cstring>
#include <utility>
#pragma once

class Person
{
private:

	char* name = nullptr;
	int age = 0;

	void free();

	void copyFrom(const Person& other);

	void moveTo(Person&& other);

public:

	Person() = default;

	Person(const Person& other);

	Person(const char* name, int age);

	Person(Person&& other) noexcept;

	Person& operator = (const Person& other);

	Person& operator = (Person&& other) noexcept;

	~Person();

	const char* getName() const;

	int getAge() const;

};


