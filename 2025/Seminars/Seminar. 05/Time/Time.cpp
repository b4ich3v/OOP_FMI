#include "Time.h"

bool HELPERS::isOneDigit(int number) 
{

	return number >= 0 && number <= 9;

}

void Time::setHours(int hours) 
{

	if (hours < 0 || hours > 24) return;

	this->hours = hours;

}

void Time::setMinutes(int minutes)
{

	if (minutes < 0 || minutes > 60) return;

	this->minutes = minutes;

}

void Time::setSeconds(int seconds)
{

	if (seconds < 0 || seconds > 60) return;

	this->seconds = seconds;

}

int Time::getSeconds() const 
{

	return seconds + minutes * 60 + hours * 3600;

}

Time::Time()
{

	setHours(0);
	setMinutes(0);
	setSeconds(0);

}

Time::Time(int hours, int minutes, int seconds)
{

	setHours(hours);
	setMinutes(minutes);
	setSeconds(seconds);

}

void Time::tick()
{

	int currentSeconds = getSeconds() + 1;

	this->hours = currentSeconds / HELPERS::SECONDS_IN_ONE_HOUR;
	this->minutes = currentSeconds / HELPERS::MINUTES_IN_ONE_HOUR;
	this->seconds = currentSeconds % HELPERS::SECONDS_IN_ONE_MINUTE;

}

bool Time::compareByCondition(const Time& other, uint8_t choice) const 
{

	if (!choice) 
	{

		return getSeconds() > other.getSeconds();

	}
	else
	{

		return !(getSeconds() > other.getSeconds());

	}

}

Time Time::differenceOfTwo(const Time& other) const
{

	int diff = std::abs(getSeconds() - other.getSeconds());

	int newHours = diff / HELPERS::SECONDS_IN_ONE_HOUR;
	int newMinutes = diff / HELPERS::SECONDS_IN_ONE_HOUR;
	int newSeconds = diff % HELPERS::SECONDS_IN_ONE_MINUTE;

	return Time(newHours, newMinutes, newSeconds);

}

Time Time::timeLeftToMidnight() const 
{

	Time midnight(0, 0, 0);
	return differenceOfTwo(midnight);

}

void Time::printHours() const 
{

	if (HELPERS::isOneDigit(hours)) 
	{

		std::cout << 0 << hours << HELPERS::SEPARATOR;

	}
	else
	{

		std::cout << hours << HELPERS::SEPARATOR;

	}

}

void Time::printMinutes() const
{

	if (HELPERS::isOneDigit(minutes))
	{

		std::cout << 0 << minutes << HELPERS::SEPARATOR;

	}
	else
	{

		std::cout << minutes << HELPERS::SEPARATOR;

	}

}

void Time::printSeconds() const
{

	if (HELPERS::isOneDigit(seconds))
	{

		std::cout << 0 << seconds << HELPERS::SEPARATOR;

	}
	else
	{

		std::cout << seconds << HELPERS::SEPARATOR;

	}

}

void Time::printTime() const
{

	printHours();
	printMinutes();
	printSeconds();
	std::cout << std::endl;

}

bool Time::isDinnerTime() const
{

	Time dinnerLower(HELPERS::DINNER_HOURS_LOWER, 
		HELPERS::DINNER_MINUTES_LOWER, HELPERS::DINNER_SECONDS_LOWER);

	Time dinnerUpper(HELPERS::DINNER_HOURS_UPPER,
		HELPERS::DINNER_MINUTES_UPPER, HELPERS::DINNER_SECONDS_UPPER);

	return compareByCondition(dinnerLower, 0) && compareByCondition(dinnerUpper, 1);

}

bool Time::isPartyTime() const
{
	
	Time partyLower(HELPERS::PARTY_HOURS_LOWER,
		HELPERS::PARTY_MINUTES_LOWER, HELPERS::PARTY_SECONDS_LOWER);

	Time partyUpper(HELPERS::PARTY_HOURS_UPPER,
		HELPERS::PARTY_MINUTES_UPPER, HELPERS::PARTY_SECONDS_UPPER);

	return compareByCondition(partyLower, 0) && compareByCondition(partyUpper, 1);

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
