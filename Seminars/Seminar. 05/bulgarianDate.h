#pragma once

class BulgarianDate
{

	int MAX_DAYS[12] =
	{

		31,28,31,30,31, 30, 31, 31, 30, 31, 30, 31

	};

	int day = 1;
	int month = 1;
	int year = 1;

	bool isLeapYear() const;
	void validateDate();

	bool isDateInValidState = true;
	mutable bool isModified = true;
	mutable int dayOfWeek = -1;

public:

	BulgarianDate() = default;

	BulgarianDate(int day, int month, int year);

	int getDay() const;

	int getMonth() const;

	int getYear() const;

	void setDay(int day);

	void setMonth(int month);

	void setYear(int year);

	void print() const;

	void goToNextDay();

	int getDayOfWeek() const;

	bool good() const;

	void clear();

};

int compareBulgarianDates(const BulgarianDate& lhs, const BulgarianDate& rhs);
