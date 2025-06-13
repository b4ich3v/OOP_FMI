#pragma once
#include "CustomPair.hpp"
#include "Time.h"
#include "Date.h"

struct DateAndTime 
{
public:

	Date date;
	Time time;

	DateAndTime(const Date& date, const Time& time);

	MyString getFormat() const;

};

DateAndTime::DateAndTime(const Date& date, const Time& time):
	date(date), time(time) {}

MyString DateAndTime::getFormat() const 
{

	return MyString(std::move(date.getDateFormat() + " " + time.getTimeFormat()));

}

template <class K>

class DateTimePair: public CustomPair<K, DateAndTime> 
{
public:

	DateTimePair(const K& key, const DateAndTime& dt);

	CustomPair<K, DateAndTime>* clone() const override;

	MyString getFormat() const override;

};

template <class K>

DateTimePair<K>::DateTimePair(const K& key, const DateAndTime& dt):
	CustomPair<K, DateAndTime>(key, dt) {}

template <class K>

CustomPair<K, DateAndTime>* DateTimePair<K>::clone() const
{

	return new DateTimePair<K>(*this);

}

template <class K>

MyString DateTimePair<K>::getFormat() const
{

	return MyString((std::to_string(this->key) + ":" + this->value.getFormat().getData()).c_str());

}
