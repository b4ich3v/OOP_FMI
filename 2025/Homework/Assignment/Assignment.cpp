#include "Assignment.h"
#include "Student.h"

Assignment::Assignment(const MyString& description, const DateTime& dueDate): 
    description(description), dueDate(dueDate) {}

int Assignment::getId() const 
{

    return id;

}

void Assignment::setId(int newId)
{

    id = newId;

}

const MyString& Assignment::getDescription() const 
{

    return description;

}

void Assignment::setDescription(const MyString& newDescription) 
{

    description = newDescription;

}

const DateTime& Assignment::getDueDate() const 
{

    return dueDate;

}

void Assignment::setDueDate(const DateTime& newDate) 
{

    dueDate = newDate;

}

void Assignment::addSubmission(const Submission& submission) 
{

    submissions.push_back(submission);

}

Submission* Assignment::getSubmission(const Student* student)
{

    for (size_t i = 0; i < submissions.size(); i++)
    {

        if (submissions[i].getStudent() == student) 
        {

            return &submissions[i];

        }

    }

    return nullptr;

}

const MyVector<Submission>& Assignment::getSubmissions() const
{

    return submissions;

}
