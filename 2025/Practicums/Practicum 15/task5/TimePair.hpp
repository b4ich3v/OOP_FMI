#pragma once
#include "CustomPair.hpp"
#include "Time.h"

template <class K>

class TimePair: public CustomPair<K, Time> 
{
public:

	TimePair(const K& key, const Time& value);

	CustomPair<K, Time>* clone() const override;

	MyString getFormat() const override;

};

template <class K>

TimePair<K>::TimePair(const K& key, const Time& value):
	CustomPair<K, Time>(key, value) {}

template <class K>

CustomPair<K, Time>* TimePair<K>::clone() const 
{

	return new TimePair<K>(*this);

}

template <class K>

MyString TimePair<K>::getFormat() const
{

	return MyString((std::to_string(this->key) + ":" + this->value.getTimeFormat().getData()).c_str());

}
