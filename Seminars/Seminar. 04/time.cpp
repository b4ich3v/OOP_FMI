#include <iostream>

const int SECONDS_IN_ONE_DAY = 86400;

class Time
{
private:

    int secondsFromMidnight;

public:

    Time() : secondsFromMidnight(0) {}

    Time(int hours, int mins, int seconds)
    {

        if (hours < 0 || hours >= 24 || mins < 0 || mins >= 60 || seconds < 0 || seconds >= 60)
        {

            this->secondsFromMidnight = 0;
            return;

        }

        this->secondsFromMidnight = hours * 3600;
        this->secondsFromMidnight += mins * 60;
        this->secondsFromMidnight += seconds;

    }

    int getTotalSeconds() const
    {

        return this->secondsFromMidnight;

    }

    int getHours() const
    {

        return secondsFromMidnight / 3600;

    }

    int getMinutes() const
    {

        return (secondsFromMidnight / 60) % 60;

    }

    int getSeconds() const
    {

        return secondsFromMidnight % 60;

    }

    int timeLeftToMidnight() const
    {

        int secondsLeft = SECONDS_IN_ONE_DAY - secondsFromMidnight;
        return secondsLeft;

    }

    void addingOneSecond()
    {

        ++secondsFromMidnight %= SECONDS_IN_ONE_DAY;

    }

    bool isDinnerTime() const
    {

        int hours = getHours();
        int mins = getMinutes();
        int seconds = getSeconds();

        if ((hours == 20 && mins >= 30) ||
            (hours == 21) ||
            (hours == 22 && mins == 0 && seconds == 0))
        {

            return true;

        }

        return false;

    }

    bool isPartyTime() const
    {
        int hours = getHours();


        if (hours >= 23 || hours < 6)
        {

            return true;

        }

        return false;

    }

    Time diff(const Time& other) const
    {

        int thisTotalSeconds = this->secondsFromMidnight;
        int otherTotalSeconds = other.secondsFromMidnight;

        int diffSeconds = std::abs(thisTotalSeconds - otherTotalSeconds);

        int newHours = diffSeconds / 3600;
        diffSeconds %= 3600;
        int newMins = diffSeconds / 60;
        int newSeconds = diffSeconds % 60;

        return Time(newHours, newMins, newSeconds);

    }

    bool compareWithOther(const Time& other) const
    {

        int thisTotalSeconds = this->secondsFromMidnight;
        int otherTotalSeconds = other.secondsFromMidnight;

        return thisTotalSeconds < otherTotalSeconds;

    }

    void displayTime() const
    {

        int hours = getHours();
        int mins = getMinutes();
        int seconds = getSeconds();
        std::cout << "Time: " << hours << "h " << mins << "m " << seconds << "s" << std::endl;

    }

};

int main()
{

    Time t1(21, 45, 30);
    Time t2(22, 30, 15);

    t1.displayTime();
    t2.displayTime();

    if (t1.isDinnerTime())
    {

        std::cout << "t1 is dinner time" << std::endl;

    }

    if (t2.isPartyTime())
    {

        std::cout << "t2 is party time" << std::endl;

    }

    Time diff = t1.diff(t2);
    std::cout << "The diff is: ";
    diff.displayTime();

    if (t1.compareWithOther(t2))
    {

        std::cout << "later" << std::endl;

    }
    else
    {

        std::cout << "sooner" << std::endl;

    }

    t1.addingOneSecond();
    t1.displayTime();

    return 0;

}
