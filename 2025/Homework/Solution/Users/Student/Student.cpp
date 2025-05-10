#include "Student.h"

Student::Student(const MyString& firstName,
    const MyString& lastName, const MyString& password):
    User(firstName, lastName, password, Type::STUDENT) {}

MyVector<Grade> Student::viewGrades() const 
{

    MyVector<Grade> grades;

    for (int i = 0; i < enrolledCourses.size(); i++) 
    {

        Course* coursePtr = enrolledCourses[i];
        MyVector<Assignment*> assignments = coursePtr->getAssignments();

        for (int j = 0; j < assignments.size(); j++)
        {

            Assignment* currentAssignment = assignments[j];
            Submission* currentSubmission = currentAssignment->getSubmission(this);

            if (currentSubmission && currentSubmission->getGrade()) 
            {

                grades.push_back(*currentSubmission->getGrade());

            }

        }

    }

    return grades;

}

void Student::enroll(Course& course) 
{

    course.addStudent(this);
    enrolledCourses.push_back(&course);

}

void Student::submitHomework(Assignment& assignment, const MyString& content, const DateTime& date)
{
    
    Submission submission(this, content, date);
    assignment.addSubmission(submission);

}

const MyVector<Course*>& Student::getEnrolledCourses() const 
{

    return enrolledCourses;

}
