#include <iostream>
#include <fstream>

namespace CONSTANTS
{

    const int DEFAULT_HOURS = 0;
    const int DEFAULT_MINUTES = 0;
    const int DEFAULT_SECONDS = 0;
    const int HOURS_IN_ONE_DAY = 24;
    const int MINUTES_IN_ONE_HOUR = 60;
    const int SECONDS_IN_ONE_MINUTE = 60;
    const int MAX_SIZE_FOR_PRINT = 8;
    const int LOWER_BOUND_DINNER_HOUR = 20;
    const int UPPER_BOUND_DINNER_HOUR = 22;
    const int LOWER_BOUND_DINNER_MINUTE = 30;
    const int SECONDS_IN_ONE_DAY = HOURS_IN_ONE_DAY * MINUTES_IN_ONE_HOUR * SECONDS_IN_ONE_MINUTE;

}

class Time
{
private:

    int hours;
    int minutes;
    int seconds;

    bool validateInputTime(int hours, int minutes, int seconds) const
    {

        if (hours < 0 || minutes < 0 || seconds < 0 ||
            hours >= 24 || minutes >= 60 || seconds >= 60)
        {

            return false;

        }

        return true;

    }

    bool isOneDigitNumber(int number) const
    {

        return number >= 0 && number <= 9;

    }

    char toChar(int number) const
    {

        return (number >= 0 && number <= 9) ? ('0' + number) : ' ';

    }

    void formatingConsoleTime(char* str, int model) const
    {

        if (isOneDigitNumber(model))
        {

            *str = '0';
            *(str + 1) = toChar(model);

        }
        else
        {

            *str = toChar(model / 10);
            *(str + 1) = toChar(model % 10);

        }

    }

public:

    Time() : hours(0), minutes(0), seconds(0) {}

    Time(int hours, int minutes, int seconds)
    {

        if (validateInputTime(hours, minutes, seconds))
        {

            setHours(hours);
            setMinutes(minutes);
            setSeconds(seconds);


        }
        else
        {

            setHours(CONSTANTS::DEFAULT_HOURS);
            setMinutes(CONSTANTS::DEFAULT_MINUTES);
            setSeconds(CONSTANTS::DEFAULT_SECONDS);

        }

    }

    Time(int seconds)
    {

        setHours((seconds / CONSTANTS::SECONDS_IN_ONE_MINUTE) / CONSTANTS::MINUTES_IN_ONE_HOUR);
        setMinutes((seconds / CONSTANTS::SECONDS_IN_ONE_MINUTE) % CONSTANTS::MINUTES_IN_ONE_HOUR);
        setSeconds(seconds % CONSTANTS::SECONDS_IN_ONE_MINUTE);

    }

    void setHours(int hours)
    {

        this->hours = hours;

    }

    void setMinutes(int minutes)
    {

        this->minutes = minutes;

    }

    void setSeconds(int seconds)
    {

        this->seconds = seconds;

    }

    Time timeLeftToMidnight() const
    {

        int newHours = CONSTANTS::HOURS_IN_ONE_DAY - hours - 1;
        int newMinutes = CONSTANTS::MINUTES_IN_ONE_HOUR - minutes - 1;
        int newSeconds = CONSTANTS::SECONDS_IN_ONE_MINUTE - seconds;

        if (newSeconds == 60)
        {

            newSeconds = 0;
            newMinutes += 1;

        }

        if (newMinutes == 60)
        {

            newMinutes = 0;
            newHours += 1;

        }

        return Time(newHours, newMinutes, newSeconds);

    }

    Time diffBewteenTwo(const Time& other) const
    {

        int s1 = toSeconds();
        int s2 = other.toSeconds();
        int diff = std::abs(s1 - s2);

        return Time(CONSTANTS::SECONDS_IN_ONE_DAY - diff);

    }

    void printTime() const
    {

        char consoleTime[CONSTANTS::MAX_SIZE_FOR_PRINT + 1];
        consoleTime[2] = ':';
        consoleTime[5] = ':';
        consoleTime[CONSTANTS::MAX_SIZE_FOR_PRINT] = '\0';

        formatingConsoleTime(consoleTime, hours);
        formatingConsoleTime(consoleTime + 3, minutes);
        formatingConsoleTime(consoleTime + 6, seconds);

        std::cout << consoleTime << std::endl;

    }

    void tick()
    {

        seconds += 1;

        if (seconds == CONSTANTS::SECONDS_IN_ONE_MINUTE)
        {

            seconds = 0;
            minutes += 1;

            if (minutes == CONSTANTS::MINUTES_IN_ONE_HOUR)
            {

                minutes = 0;
                hours += 1;

                if (hours == CONSTANTS::HOURS_IN_ONE_DAY) hours = 0;

            }

        }

    }

    bool isDinnerTime() const
    {

        if (hours < CONSTANTS::LOWER_BOUND_DINNER_HOUR ||
            hours > CONSTANTS::UPPER_BOUND_DINNER_HOUR)
        {

            return false;

        }

        if (hours == CONSTANTS::LOWER_BOUND_DINNER_HOUR &&
            minutes < CONSTANTS::LOWER_BOUND_DINNER_MINUTE)
        {

            return false;

        }

        if (hours == CONSTANTS::UPPER_BOUND_DINNER_HOUR &&
            (minutes > 0 || seconds > 0))
        {

            return false;

        }

        return true;

    }

    bool isPartyTime() const
    {

        return (hours >= CONSTANTS::HOURS_IN_ONE_DAY - 1 || hours < CONSTANTS::HOURS_IN_ONE_DAY - 18);

    }

    int toSeconds() const
    {

        return seconds +
            (hours * CONSTANTS::MINUTES_IN_ONE_HOUR * CONSTANTS::SECONDS_IN_ONE_MINUTE) +
            (minutes * CONSTANTS::SECONDS_IN_ONE_MINUTE);


    }

    bool isEarlier(const Time& other) const
    {

        return toSeconds() > other.toSeconds();

    }

};

void sortTimes(Time* times, int size)
{

    for (int i = 0; i < size - 1; i++)
    {

        for (int j = 0; j < size - i - 1; j++)
        {

            if (times[j].isEarlier(times[j + 1])) std::swap(times[j], times[j + 1]);

        }

    }

}

int main()
{

    Time time1 = { 21, 31, 57 };
    Time time3 = time1.timeLeftToMidnight();
    std::cout << time1.isDinnerTime() << std::endl;
    time3.printTime();
    std::cout << time3.isPartyTime() << std::endl;

    Time time2 = { 23, 59, 59 };
    time2.tick();
    time2.printTime();
    std::cout << std::endl;

    Time diff = time1.diffBewteenTwo(time3);
    diff.printTime();
    std::cout << std::endl;

    Time times[3] = { time1, time2, time3 };
    sortTimes(times, 3);

    for (int i = 0; i < 3; i++)
    {

        times[i].printTime();

    }

    return 0;

}
