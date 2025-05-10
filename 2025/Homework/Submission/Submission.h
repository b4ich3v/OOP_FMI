#include "DateTime.h"
#include "Grade.h"
#include "MyString.h"
#pragma once

class Student;

class Submission
{
private:

    Student* student;          
    MyString content;          
    DateTime date;        
    Grade* grade = nullptr;    

public:
    
    Submission();

    Submission(Student* student, const MyString& content, 
        const DateTime& date);

    Student* getStudent() const;

    const MyString& getContent() const;

    const DateTime& getDateTime() const;

    Grade* getGrade() const;

    void attachGrade(Grade* grade);

};
