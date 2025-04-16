#include "Person.h"
#include <iostream>
#pragma once

class Teacher: public Person
{
private:

	char** subjects = nullptr;
	int countOfSubjects = 0;
	int capacityForSubjects = 8;

	void free();

	void copyFrom(const Teacher& other);

	void moveTo(Teacher&& other);

	void resizeForSubjects(int newCapacity);

public:

	Teacher() = default;

	Teacher(const char* name, int age, const char* const* subjects, int countOfSubjects);

	Teacher(const Teacher& other);

	Teacher(Teacher&& other) noexcept;

	Teacher& operator = (const Teacher& other);

	Teacher& operator = (Teacher&& other) noexcept;

	~Teacher();

	const char* getTeacherName() const;

	int getTeacherAge() const;

	int getCountOfSubjects() const;

	const char* const* getTeacherSubjects() const;

};


