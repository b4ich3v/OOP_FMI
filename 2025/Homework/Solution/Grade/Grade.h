#include "MyString.h"
#include "DateTime.h"
#pragma once

class Grade 
{
private:

    double score;           
    MyString feedback;       
    DateTime date;      

public:
    
    Grade();

    Grade(double score, const MyString& feedback, const DateTime& date);

    double getScore() const;

    const MyString& getFeedback() const;

    const DateTime& getDate() const;

};


