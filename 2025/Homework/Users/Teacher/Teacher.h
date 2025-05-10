#include "User.h"
#include "Course.h"
#include "Assignment.h"
#include "Submission.h"
#include "Grade.h"
#include "MyVector.hpp"
#include "MyString.h"
#include "DateTime.h"
#pragma once

class Student;  

class Teacher: public User
{
private:

    MyVector<Course*> courses;   

public:
    
    Teacher(const MyString& firstName, const MyString& lastName,
        const MyString& password);

    Course* createCourse(const MyString& code, const MyString& title,
        const MyString& password);
    
    void addAssignment(Course* course, const MyString& description,
        const DateTime& dueDate);

    void enrollStudent(Course* course, Student* student);

    void assignGrade(Submission* submission, double score, 
        const MyString& feedback, const DateTime& date);

    const MyVector<Course*>& getCourses() const;

};
