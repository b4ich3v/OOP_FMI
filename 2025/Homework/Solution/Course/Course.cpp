#include "Course.h"
#include "Student.h"
#include "Assignment.h"

Course::Course(const MyString& code, const MyString& title, 
    const MyString& password, Teacher* teacher): code(code),
    title(title), password(password), teacher(teacher) {}

int Course::getId() const 
{

    return id;

}

void Course::setId(int newId) 
{

    id = newId;

}

const MyString& Course::getCode() const 
{

    return code;

}

void Course::setCode(const MyString& newCode) 
{

    code = newCode;

}

const MyString& Course::getTitle() const 
{

    return title;

}

void Course::setTitle(const MyString& newTitle) 
{

    title = newTitle;

}

const MyString& Course::getPassword() const 
{

    return password;

}

void Course::setPassword(const MyString& newPassword)
{

    password = newPassword;

}

Teacher* Course::getTeacher() const 
{

    return teacher;

}

void Course::setTeacher(Teacher* newTeacher) 
{

    teacher = newTeacher;

}

const MyVector<Student*>& Course::getStudents() const 
{

    return students;

}

const MyVector<Assignment*>& Course::getAssignments() const 
{

    return assignments;

}

void Course::addStudent(Student* student) 
{

    students.push_back(student);

}

void Course::removeStudent(Student* student) 
{

    bool shifted = false;

    for (size_t i = 0; i < students.size(); i++)
    {

        if (!shifted) 
        {

            if (students[i] == student)
            {

                shifted = true;

            }

        }

        if (shifted && i + 1 < students.size()) 
        {

            students[i] = students[i + 1];

        }

    }

    if (shifted) students.pop_back();

}

void Course::addAssignment(Assignment* assignment) 
{

    assignments.push_back(assignment);

}

void Course::removeAssignment(Assignment* assignment) 
{

    bool shifted = false;

    for (size_t i = 0; i < assignments.size(); i++) 
    {

        if (!shifted) 
        {

            if (assignments[i] == assignment)
            {

                shifted = true;

            }

        }

        if (shifted && i + 1 < assignments.size()) 
        {

            assignments[i] = assignments[i + 1];

        }

    }

    if (shifted) assignments.pop_back();

}
