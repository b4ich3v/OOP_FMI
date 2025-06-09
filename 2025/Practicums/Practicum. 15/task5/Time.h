#pragma once
#include "MyString.h"

namespace HELPERS1
{

	int getDigitCount(size_t number);

	char digitToChar(int digit);

}

class Time
{
private:

	int hours = 0;
	int minutes = 0;
	int seconds = 0;

	MyString hoursToStr() const;

	MyString minutesToStr() const;

	MyString secondsToStr() const;

public:

	Time(int hours, int minutes, int seconds);

	int getHours() const;

	int getMinutes() const;

	int getSeconds() const;

	MyString getTimeFormat() const;

};

