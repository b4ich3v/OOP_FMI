#include "User.h"
#include "Course.h"
#include "Assignment.h"
#include "Submission.h"
#include "Grade.h"
#include "DateTime.h"
#pragma once

class Student: public User 
{
private:

    MyVector<Course*> enrolledCourses;

public:
   
    Student(const MyString& firstName,
        const MyString& lastName, const MyString& password);
      
    void enroll(Course& course);

    void submitHomework(Assignment& assignment, const MyString& content, const DateTime& date);

    MyVector<Grade> viewGrades() const;

    const MyVector<Course*>& getEnrolledCourses() const;

};
