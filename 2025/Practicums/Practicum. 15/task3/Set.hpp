#include <iostream>
#pragma once

template <class T>

class Set
{
public:

	virtual bool member(const T& element) const = 0;

	virtual Set<T>* clone() const = 0;

	virtual void serialize(std::ostream& os) const = 0;

	virtual void deserialize(std::istream& is) = 0;

	virtual ~Set() = default;

};
