#include "Date.h"

Date::Date(Day day, Month month, size_t year) 
{

	this->day = day;
	this->month = month;
	this->year = year;

}

int HELPERS2::getDigitCount(size_t number)
{

	int counter = 0;

	while (number != 0) 
	{

		number /= 10;
		counter += 1;

	}

	return counter;

}

char HELPERS2::digitToChar(int digit)
{

	return digit + '0';

}

MyString Date::dayToStr() const 
{

	switch (day)
	{

	case Day::Monday: return MyString("Monday"); break;
	case Day::Tuesday: return MyString("Tuesday"); break;
	case Day::Wednesday: return MyString("Wednesday"); break;
	case Day::Thursday: return MyString("Thursday"); break;
	case Day::Friday: return MyString("Friday"); break;
	case Day::Saturday: return MyString("Saturday"); break;
	case Day::Sunday: return MyString("Sunday"); break;
	default: return MyString(""); break;
		
	};

}

MyString Date::monthToStr() const 
{

	switch (month)
	{

	case Month::January: return MyString("January"); break;
	case Month::February: return MyString("February"); break;
	case Month::March: return MyString("March"); break;
	case Month::April: return MyString("April"); break;
	case Month::May: return MyString("May"); break;
	case Month::June: return MyString("June"); break;
	case Month::July: return MyString("July"); break;
	case Month::August: return MyString("August"); break;
	case Month::September: return MyString("September"); break;
	case Month::October: return MyString("October"); break;
	case Month::November: return MyString("November"); break;
	case Month::December: return MyString("December"); break;
	default: return MyString(""); break;

	}

}

MyString Date::yearToStr() const 
{

	char* number = new char[HELPERS2::getDigitCount(year) + 1];
	size_t copyOfYear = year;
	size_t index = HELPERS2::getDigitCount(year) - 1;

	while (copyOfYear != 0) 
	{
		char currentDigit = HELPERS2::digitToChar(copyOfYear % 10);
		number[index] = currentDigit;
		index -= 1;
		copyOfYear /= 10;

	}

	number[HELPERS2::getDigitCount(year)] = '\0';
	MyString result(number);
	delete[] number;
	number = nullptr;

	return result;

}

Day Date::getDay() const 
{

	return day;

}

Month Date::getMonth() const 
{

	return month;

}

size_t Date::getYear() const 
{

	return year;

}

MyString Date::getDateFormat() const
{

	return MyString(dayToStr() + "." + monthToStr() + "." + yearToStr());

}
