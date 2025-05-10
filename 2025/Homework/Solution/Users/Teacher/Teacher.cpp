#include "Teacher.h"

Teacher::Teacher(const MyString& firstName,const MyString& lastName,
    const MyString& password)
    : User(firstName, lastName, password, Type::TEACHER) {}

Course* Teacher::createCourse(const MyString& code,
    const MyString& title, const MyString& password)
{

    auto* course = new Course(code, title, password, this);
    courses.push_back(course);

    return course;

}

void Teacher::addAssignment(Course* course, const MyString& description,
    const DateTime& dueDate)
{

    auto* assignment = new Assignment(description, dueDate);
    course->addAssignment(assignment);

}

void Teacher::enrollStudent(Course* course, Student* student) 
{

    course->addStudent(student);

}

void Teacher::assignGrade(Submission* submission, double score,
    const MyString& feedback, const DateTime& date)
{
    
    auto* grade = new Grade(score, feedback, date);
    submission->attachGrade(grade);

}

const MyVector<Course*>& Teacher::getCourses() const 
{

    return courses;

}
