#include "Set.hpp"
#pragma once

template <class T>

class Range: public Set<T>
{
private:

	T left;
	T right;

public:

	Range(const T& left, const T& right);

	Set<T>* clone() const override;

	void serialize(std::ostream& os) const override;

	void deserialize(std::istream& is) override;

	bool member(const T& element) const override;

};

template <class T>

Range<T>::Range(const T& left, const T& right):
	left(left), right(right) {}

template <class T>

Set<T>* Range<T>::clone() const
{

	return new Range(*this);

}

template <class T>

bool Range<T>::member(const T& element) const
{

	return (left <= element) && (right >= element);

}

template <class T>

void Range<T>::serialize(std::ostream& os) const
{

	os << "{ ";

	T iter = left;

	while (iter != right) 
	{

		os << iter << " ";
		iter += 1;

	}

	os << "}";

}

template <class T>

void Range<T>::deserialize(std::istream& is) 
{

	is >> left;
	is >> right;

}
