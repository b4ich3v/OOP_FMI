#pragma once
#include "CustomPair.hpp"

template <class K>

class StringPair: public CustomPair<K, MyString>
{
public:

	StringPair(const K& key, const MyString& value);

	CustomPair<K, MyString>* clone() const override;

	MyString getFormat() const override;

};

template <class K>

StringPair<K>::StringPair(const K& key, const MyString& value):
	CustomPair<K, MyString>(key, value) {}

template <class K>

CustomPair<K, MyString>* StringPair<K>::clone() const
{

	return new StringPair<K>(*this);

}

template <class K>

MyString StringPair<K>::getFormat() const 
{

	return MyString((std::to_string(this->key) + ":" + this->value.getData()).c_str());

}


