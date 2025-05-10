#include "Time.h"

bool HELPERS::isOneDigit(int number)
{

    return (number >= 0 && number <= 9);

}

void Time::setHours(int hours)
{

    if (hours < 0 || hours > 23) return;
    this->hours = hours;

}

void Time::setMinutes(int minutes)
{

    if (minutes < 0 || minutes > 59) return;
    this->minutes = minutes;

}

void Time::setSeconds(int seconds)
{

    if (seconds < 0 || seconds > 59) return;
    this->seconds = seconds;

}

int Time::getAllDaySeconds() const
{

    return seconds
        + (minutes * HELPERS::SECONDS_IN_ONE_MINUTE)
        + (hours * HELPERS::SECONDS_IN_ONE_HOUR);

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

    int currentSeconds = getAllDaySeconds() + 1;

    if (currentSeconds >= 24 * HELPERS::SECONDS_IN_ONE_HOUR) currentSeconds = 0;

    hours = currentSeconds / HELPERS::SECONDS_IN_ONE_HOUR;
    int remainder = currentSeconds % HELPERS::SECONDS_IN_ONE_HOUR;
    minutes = remainder / HELPERS::MINUTES_IN_ONE_HOUR;
    seconds = remainder % HELPERS::SECONDS_IN_ONE_MINUTE;

}

bool Time::compareByCondition(const Time& other, uint8_t choice) const
{

    if (choice == 0)
    {

        return (getAllDaySeconds() > other.getAllDaySeconds());

    }
    else
    {

        return (getAllDaySeconds() < other.getAllDaySeconds());

    }

}

Time Time::differenceOfTwo(const Time& other) const
{

    int diff = std::abs(getAllDaySeconds() - other.getAllDaySeconds());

    int newHours = diff / HELPERS::SECONDS_IN_ONE_HOUR;
    int remainder = diff % HELPERS::SECONDS_IN_ONE_HOUR;
    int newMinutes = remainder / HELPERS::MINUTES_IN_ONE_HOUR;
    int newSeconds = remainder % HELPERS::SECONDS_IN_ONE_MINUTE;

    return Time(newHours, newMinutes, newSeconds);

}

Time Time::timeLeftToMidnight() const
{

    int diffToMidnight = (24 * HELPERS::SECONDS_IN_ONE_HOUR) - getAllDaySeconds();

    if (diffToMidnight == 24 * HELPERS::SECONDS_IN_ONE_HOUR)  diffToMidnight = 0;

    int newHours = diffToMidnight / HELPERS::SECONDS_IN_ONE_HOUR;
    int remainder = diffToMidnight % HELPERS::SECONDS_IN_ONE_HOUR;
    int newMinutes = remainder / HELPERS::MINUTES_IN_ONE_HOUR;
    int newSeconds = remainder % HELPERS::SECONDS_IN_ONE_MINUTE;

    return Time(newHours, newMinutes, newSeconds);

}

void Time::printHours() const
{

    if (HELPERS::isOneDigit(hours)) std::cout << 0 << hours << HELPERS::SEPARATOR;
    else std::cout << hours << HELPERS::SEPARATOR;

}

void Time::printMinutes() const
{

    if (HELPERS::isOneDigit(minutes)) std::cout << 0 << minutes << HELPERS::SEPARATOR;
    else std::cout << minutes << HELPERS::SEPARATOR;

}

void Time::printSeconds() const
{

    if (HELPERS::isOneDigit(seconds)) std::cout << 0 << seconds;
    else std::cout << seconds;

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

    int current = getAllDaySeconds();

    int lower = HELPERS::DINNER_HOURS_LOWER * 3600
        + HELPERS::DINNER_MINUTES_LOWER * 60
        + HELPERS::DINNER_SECONDS_LOWER;

    int upper = HELPERS::DINNER_HOURS_UPPER * 3600
        + HELPERS::DINNER_MINUTES_UPPER * 60
        + HELPERS::DINNER_SECONDS_UPPER;

    return (current >= lower && current <= upper);

}

bool Time::isPartyTime() const
{

    int current = getAllDaySeconds();

    int partyLower = HELPERS::PARTY_HOURS_LOWER * 3600
        + HELPERS::PARTY_MINUTES_LOWER * 60
        + HELPERS::PARTY_SECONDS_LOWER;

    int partyUpper = HELPERS::PARTY_HOURS_UPPER * 3600
        + HELPERS::PARTY_MINUTES_UPPER * 60
        + HELPERS::PARTY_SECONDS_UPPER;


    if (current >= partyLower || current < partyUpper)  return true;
    else  return false;

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
