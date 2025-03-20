#include <cstring>
#include <iostream>
#pragma once

namespace HELPERS
{

    const int MAX_SIZE_QUOTE = 30;

}

class Student
{
private:

    char* name = nullptr;
    char quote[HELPERS::MAX_SIZE_QUOTE + 1] = "DEFAULT";

    double* grades = nullptr;
    int size = 0;
    int capacity = 8;

    void setName(const char* name);

    void setQuote(const char* quote);

    void setGrades(const double* grades, int size);

    void free();

    void copyFrom(const Student& other);

    void resize(int newCapacity);

public:

    Student();

    Student(const char* name, const char* quote, const double* grades, int size);

    Student(const Student& other);

    Student& operator = (const Student& other);

    ~Student();

    void addGrade(double newGrade);

    const char* getName() const;

    const char* getQuote() const;

    const double* getGrades() const;

    void printStudent() const;

};
