#include "DateTime.h"

bool DateTime::isLeapYear(int year) const
{

    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));

}

int DateTime::daysInMonth(int month, int year) const
{


    if (month == 2 && isLeapYear(year)) return 29;
    if (month >= 1 && month <= 12) return monthDays[month - 1];
    return 30;

}

DateTime::DateTime(): 
    day(1), month(1), year(1970), time(Time()) {}

DateTime::DateTime(int day, int month, int year, const Time& time) 
{

    setDate(day, month, year);
    setTime(time);

}

void DateTime::setDate(int day, int month, int year) 
{

    if (year < 0) return;
    if (month < 1 || month > 12) return;

    int dim = daysInMonth(month, year);

    if (day < 1 || day > dim) return;

    this->day = day;
    this->month = month;
    this->year = year;

}

void DateTime::setTime(const Time& time)
{

    this->time = time;

}

int DateTime::getDay() const 
{

    return day; 

}

int DateTime::getMonth() const 
{

    return month;

}

int DateTime::getYear() const 
{

    return year; 

}

Time DateTime::getTime() const 
{

    return time; 

}

void DateTime::tick()
{

    int prevSeconds = time.getAllDaySeconds();
    time.tick();
    
    if (time.getAllDaySeconds() <= prevSeconds) 
    {
        
        day += 1;

        if (day > daysInMonth(month, year)) 
        {

            day = 1;
            month += 1;

            if (month > 12) 
            {

                month = 1;
                year++;

            }

        }

    }

}

bool operator == (const DateTime& left, const DateTime& right)
{

    return left.year == right.year
        && left.month == right.month
        && left.day == right.day
        && left.time.getAllDaySeconds() == right.time.getAllDaySeconds();

}

bool operator != (const DateTime& left, const DateTime& right)
{

    return !(left == right);

}

bool operator < (const DateTime& left, const DateTime& right)
{

    if (left.year != right.year) return left.year < right.year;
    if (left.month != right.month) return left.month < right.month;
    if (left.day != right.day) return left.day < right.day;

    return left.time.getAllDaySeconds() < right.time.getAllDaySeconds();

}

bool operator > (const DateTime& left, const DateTime& right)
{

    return right < left;

}

bool operator <= (const DateTime& left, const DateTime& right)
{

    return !(right < left);

}

bool operator >= (const DateTime& left, const DateTime& right)
{

    return !(left < right);

}

void DateTime::print() const
{

    std::cout << toString();

}

MyString DateTime::toString() const 
{

    auto format2 = [](int value)
    {

        char buffer[3] = { '0', '0', '0' };
        buffer[0] = char('0' + (value / 10) % 10);
        buffer[1] = char('0' + (value % 10));

        return MyString(buffer);

    };
    
    auto format4 = [](int value) 
    {

        char buffer[5] = { '0', '0', '0', '0', '0' };
        buffer[0] = char('0' + (value / 1000) % 10);
        buffer[1] = char('0' + (value / 100) % 10);
        buffer[2] = char('0' + (value / 10) % 10);
        buffer[3] = char('0' + (value % 10));

        return MyString(buffer);

    };

    MyString result;
    result = format2(day);
    result = result + ".";
    result = result + format2(month);
    result = result + ".";
    result = result + format4(year);
    result = result + " ";
    result = result + format2(time.getHours());
    result = result + ":";
    result = result + format2(time.getMinutes());
    result = result + ":";
    result = result + format2(time.getSeconds());

    return result;

}
