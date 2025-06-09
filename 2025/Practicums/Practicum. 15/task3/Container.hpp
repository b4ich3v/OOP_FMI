#include "Set.hpp"
#include "Vector.hpp"
#pragma once

template <class T>

class Container: public Set<T>
{
private:

	Vector<T> array;

public:

	void add(const T& element);

	void add(T&& element);

	void serialize(std::ostream& os) const override;

	void deserialize(std::istream& is) override;

	Container& operator += (const Container& other);

	friend Container operator + (const Container& left, const Container& right);

	bool member(const T& element) const override;

	Set<T>* clone() const override;

};

template <class T>

void Container<T>::add(const T& element) 
{

	array.push_back(element);

}

template <class T>

void Container<T>::add(T&& element) 
{

	array.push_back(std::move(element));

}

template <class T>

Container<T>& Container<T>::operator += (const Container& other) 
{

	for (int i = 0; i < other.array.getSize(); i++)
	{

		array.push_back(other.array[i]);

	}

	return *this;

}

template <class T>

Container<T> operator + (const Container<T>& left, const Container<T>& right)
{

	Container<T> result(left);
	result += right;

	return result;

}

template <class T>

bool Container<T>::member(const T& element) const 
{

	for (int i = 0; i < array.getSize(); i++)
	{

		if (array[i] == element) return true;

	}

	return false;

}

template <class T>

Set<T>* Container<T>::clone() const  
{

	return new Container(*this);

}

template <class T>

void Container<T>::serialize(std::ostream& os) const 
{

	os << "(";
	os << array.getSize();
	os << ")";

	os << "{";

	for (int i = 0; i < array.getSize(); i++)
	{

		os << array[i];
		if (i != array.getSize() - 1) os << " ";

	}

	os << "}";

}

template <class T>

void Container<T>::deserialize(std::istream& is) 
{

	Vector<T> newArray;
	int size = 0;

	is.ignore(1);
	is >> size;
	is.ignore(1);
	is.ignore(1);

	T currentElement;

	for (int i = 0; i < size; i++)
	{

		is >> currentElement;
		newArray.push_back(currentElement);

	}

	array = newArray;

}
