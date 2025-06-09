#pragma once
#include "MyString.h"

enum class Month
{

	January, 
	February, 
	March, 
	April, 
	May, 
	June, 
	July, 
	August, 
	September, 
	October, 
	November, 
	December
};

enum class Day
{

	Monday,
	Tuesday,
	Wednesday,
	Thursday,
	Friday,
	Saturday,
	Sunday

};

namespace HELPERS2 
{

	int getDigitCount(size_t number);

	char digitToChar(int digit);

}

class Date
{
private:

	Day day;
	Month month;
	size_t year;

	MyString dayToStr() const;

	MyString monthToStr() const;

	MyString yearToStr() const;

public:

	Date(Day day, Month month, size_t year);

	Day getDay() const;

	Month getMonth() const;

	size_t getYear() const;

	MyString getDateFormat() const;

};

