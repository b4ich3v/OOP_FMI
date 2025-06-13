#include "Time.h"

Time::Time(int hours, int minutes, int seconds):
	hours(hours), minutes(minutes), seconds(seconds) {}

int HELPERS1::getDigitCount(size_t number)
{

	int counter = 0;

	while (number != 0)
	{

		number /= 10;
		counter += 1;

	}

	return counter;

}

char HELPERS1::digitToChar(int digit)
{

	return digit + '0';

}

int Time::getHours() const 
{

	return hours;

}

int Time::getMinutes() const 
{

	return minutes;

}

int Time::getSeconds() const 
{

	return seconds;

}

MyString Time::hoursToStr() const 
{

	if (hours == 0) return MyString("0");

	char* number = new char[HELPERS1::getDigitCount(hours) + 1];
	int copyOfHours = hours;
	size_t index = HELPERS1::getDigitCount(hours) - 1;

	while (copyOfHours != 0)
	{
		char currentDigit = HELPERS1::digitToChar(copyOfHours % 10);
		number[index] = currentDigit;
		index -= 1;
		copyOfHours /= 10;

	}

	number[HELPERS1::getDigitCount(hours)] = '\0';
	MyString result(number);
	delete[] number;
	number = nullptr;

	return result;

}

MyString Time::minutesToStr() const
{

	if (minutes == 0) return MyString("0");

	char* number = new char[HELPERS1::getDigitCount(minutes) + 1];
	int copyOfMinutes = minutes;
	size_t index = HELPERS1::getDigitCount(minutes) - 1;

	while (copyOfMinutes != 0)
	{
		char currentDigit = HELPERS1::digitToChar(copyOfMinutes % 10);
		number[index] = currentDigit;
		index -= 1;
		copyOfMinutes /= 10;

	}

	number[HELPERS1::getDigitCount(minutes)] = '\0';
	MyString result(number);
	delete[] number;
	number = nullptr;

	return result;

}

MyString Time::secondsToStr() const 
{

	if (seconds == 0) return MyString("0");

	char* number = new char[HELPERS1::getDigitCount(seconds) + 1];
	int copyOfSeconds = seconds;
	size_t index = HELPERS1::getDigitCount(seconds) - 1;

	while (copyOfSeconds != 0)
	{
		char currentDigit = HELPERS1::digitToChar(copyOfSeconds % 10);
		number[index] = currentDigit;
		index -= 1;
		copyOfSeconds /= 10;

	}

	number[HELPERS1::getDigitCount(seconds)] = '\0';
	MyString result(number);
	delete[] number;
	number = nullptr;

	return result;

}

MyString Time::getTimeFormat() const
{

	return MyString(hoursToStr() + ":" + minutesToStr() + ":" + secondsToStr());

}
