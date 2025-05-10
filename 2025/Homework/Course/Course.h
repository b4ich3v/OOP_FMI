#include "IEntity.h"
#include "MyString.h"
#include "MyVector.hpp"
#pragma once

class Teacher;
class Student;
class Assignment;

class Course: public IEntity 
{
private:

    int id = 0;

    MyString code;                          
    MyString title;                         
    MyString password; 
    
    Teacher* teacher = nullptr;                
    MyVector<Student*> students;           
    MyVector<Assignment*> assignments;     

public:

    Course(const MyString& code, const MyString& title,
        const MyString& password, Teacher* teacher);

    int getId() const override;

    void setId(int newId) override;

    const MyString& getCode() const;

    void setCode(const MyString& newCode);

    const MyString& getTitle() const;

    void setTitle(const MyString& newTitle);

    const MyString& getPassword() const;

    void setPassword(const MyString& newPassword);

    Teacher* getTeacher() const;

    void setTeacher(Teacher* newTeacher);

    const MyVector<Student*>& getStudents() const;

    const MyVector<Assignment*>& getAssignments() const;

    void addStudent(Student* student);

    void removeStudent(Student* student);

    void addAssignment(Assignment* assignment);

    void removeAssignment(Assignment* assignment);

};
