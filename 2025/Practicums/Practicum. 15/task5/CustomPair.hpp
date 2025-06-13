#include "MyString.h"
#pragma once

template <class K, class V>

class CustomPair 
{
protected:
	
	K key;
	V value;

public:

	CustomPair(const K& key, const V& value);

	virtual CustomPair<K, V>* clone() const = 0;

	virtual MyString getFormat() const = 0;

	virtual ~CustomPair() = default;

};

template <class K, class V>

CustomPair<K,V>::CustomPair(const K& key, const V& value):
	key(key), value(value) {}
