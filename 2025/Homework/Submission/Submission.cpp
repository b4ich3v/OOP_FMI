#include "Submission.h"

Submission::Submission(): 
    student(nullptr), content(""),
    date(), grade(nullptr) {}

Submission::Submission(Student* student, const MyString& content,
    const DateTime& date): 
    student(student), content(content), date(date),
    grade(nullptr) {}

Student* Submission::getStudent() const 
{

    return student;

}

const MyString& Submission::getContent() const 
{

    return content;

}

const DateTime& Submission::getDateTime() const
{

    return date;

}

Grade* Submission::getGrade() const
{

    return grade;

}

void Submission::attachGrade(Grade* grade) 
{

    this->grade = grade;

}
