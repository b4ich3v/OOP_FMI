#include "Student.h"

Student::Student(const char* name, int age, const char* id): Person(name, age)
{

    strncpy(this->id, id, strlen(id));

}

const char* Student::getStudentName() const
{

    return getName();

}

int Student::getStudentAge() const
{

    return getAge();

}

const char* Student::getStudentId() const
{

    return id;

}

