#include "Grade.h"

Grade::Grade():
    score(0), feedback(""), date() {}

Grade::Grade(double score, const MyString& feedback, const DateTime& date): 
    score(score), feedback(feedback), date(date) {}

double Grade::getScore() const 
{

    return score;

}

const MyString& Grade::getFeedback() const 
{

    return feedback;

}

const DateTime& Grade::getDate() const 
{

    return date;

}
