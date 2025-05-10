#include "Time.h"
#include "MyString.h"
#include <iostream>
#include <sstream>
#pragma once

static const int monthDays[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

class DateTime
{
private:

    int day;
    int month;
    int year;
    Time time;

    bool isLeapYear(int year) const;

    int daysInMonth(int month, int year) const;

public:

    DateTime();

    DateTime(int day, int month, int year, const Time& time);

    void setDate(int day, int month, int year);

    void setTime(const Time& time);

    int getDay() const;

    int getMonth() const;

    int getYear() const;

    Time getTime() const;

    void tick();

    friend bool operator == (const DateTime& left, const DateTime& right);

    friend bool operator != (const DateTime& left, const DateTime& right);

    friend bool operator < (const DateTime& left, const DateTime& right);

    friend bool operator <= (const DateTime& left, const DateTime& right);

    friend bool operator > (const DateTime& left, const DateTime& right);

    friend bool operator >= (const DateTime& left, const DateTime& right);

    void print() const;

    MyString toString() const;

};
