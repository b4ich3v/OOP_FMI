#include "FJSON.hpp"
#include "DatePair.hpp"
#include "StringPair.hpp"
#include "TimePair.hpp"
#include "DateTimePair.hpp"

int main() 
{

	StringPair<int> stringPair(6, "Yoan Baychev");
	TimePair<int> timePair(111, Time(22, 15, 33));
	DatePair<int> datePair(7, Date(Day::Monday, Month::May, 2004));
	DateTimePair<int> dateTimePair(0, DateAndTime(Date(Day::Friday, Month::August, 2025), Time(17, 45, 11)));

	std::ofstream file("test1.txt", std::ios::app);

	FJSON<int, MyString> fjString;
	fjString.addPair(new StringPair<int>(stringPair));

	FJSON<int, Time> fjTime;
	fjTime.addPair(new TimePair<int>(timePair));

	FJSON<int, Date> fjDate;
	fjDate.addPair(new DatePair<int>(datePair));

	FJSON<int, DateAndTime> fjDateTime;
	fjDateTime.addPair(new DateTimePair<int>(dateTimePair));

	fjString.saveToFile(file);
	fjTime.saveToFile(file);
	fjDate.saveToFile(file);
	fjDateTime.saveToFile(file);

	file.close();

	return 0;

}
