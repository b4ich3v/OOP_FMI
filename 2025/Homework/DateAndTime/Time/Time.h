#pragma once
#include <iostream>
#include <cstddef>
#include <cstdint>
#include <cmath>

namespace HELPERS
{

    const char SEPARATOR[2] = ":";
    const int SECONDS_IN_ONE_HOUR = 3600;
    const int MINUTES_IN_ONE_HOUR = 60;
    const int SECONDS_IN_ONE_MINUTE = 60;

    const int DINNER_HOURS_LOWER = 20;
    const int DINNER_MINUTES_LOWER = 30;
    const int DINNER_SECONDS_LOWER = 0;
    const int DINNER_HOURS_UPPER = 22;
    const int DINNER_MINUTES_UPPER = 0;
    const int DINNER_SECONDS_UPPER = 0;

    const int PARTY_HOURS_LOWER = 23;
    const int PARTY_MINUTES_LOWER = 30;
    const int PARTY_SECONDS_LOWER = 0;
    const int PARTY_HOURS_UPPER = 6;
    const int PARTY_MINUTES_UPPER = 0;
    const int PARTY_SECONDS_UPPER = 0;

    bool isOneDigit(int number);

}

class Time
{
private:

    int hours;
    int minutes;
    int seconds;

    void setHours(int hours);

    void setMinutes(int minutes);

    void setSeconds(int seconds);

    void printHours() const;

    void printMinutes() const;

    void printSeconds() const;

public:

    Time();

    Time(int hours, int minutes, int seconds);

    void tick();

    bool compareByCondition(const Time& other, uint8_t choice) const;

    Time differenceOfTwo(const Time& other) const;

    Time timeLeftToMidnight() const;

    void printTime() const;

    bool isDinnerTime() const;

    bool isPartyTime() const;

    int getHours() const;

    int getMinutes() const;

    int getSeconds() const;

    int getAllDaySeconds() const;

};
