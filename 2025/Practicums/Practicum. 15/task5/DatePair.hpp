#pragma once
#include "Date.h"
#include "CustomPair.hpp"

template <class K>

class DatePair: public CustomPair<K, Date>
{	
public:

	DatePair(const K& key, const Date& date);

	CustomPair<K, Date>* clone() const override;

	MyString getFormat() const override;

};

template <class K>

DatePair<K>::DatePair(const K& key, const Date& date):
	CustomPair<K, Date>(key, date) {}

template <class K>

CustomPair<K, Date>* DatePair<K>::clone() const 
{

	return new DatePair<K>(*this);

}

template <class K>

MyString DatePair<K>::getFormat() const
{

	return MyString((std::to_string(this->key) + ":" + this->value.getDateFormat().getData()).c_str());

}
