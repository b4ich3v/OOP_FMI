#include "IEntity.h"
#include "MyString.h"
#include "DateTime.h"
#include "Submission.h"
#include "MyVector.hpp"
#pragma once

class Student;

class Assignment: public IEntity 
{
private:

    int id = 0;                        
    MyString description;              
    DateTime dueDate;                  
    MyVector<Submission> submissions;  

public:
    
    Assignment(const MyString& description, const DateTime& dueDate);

    int getId() const override;

    void setId(int newId) override;

    const MyString& getDescription() const;

    void setDescription(const MyString& newDescription);

    const DateTime& getDueDate() const;

    void setDueDate(const DateTime& newDate);

    void addSubmission(const Submission& submission);

    Submission* getSubmission(const Student* student);

    const MyVector<Submission>& getSubmissions() const;

};
