#include <iostream>
#pragma once

template <class T>

class PolymorphicPtr
{
private:

	T* data = nullptr;

	void moveTo(PolymorphicPtr&& other);

	void copyFrom(const PolymorphicPtr& other);

	void free();

public:

	PolymorphicPtr(T* data);

	PolymorphicPtr(const PolymorphicPtr& other);

	PolymorphicPtr(PolymorphicPtr&& other) noexcept;

	PolymorphicPtr& operator = (const PolymorphicPtr& other);

	PolymorphicPtr& operator = (PolymorphicPtr&& other) noexcept;

	~PolymorphicPtr();

	const T& operator * () const;

	T& operator * ();

	const T* operator -> () const;

	T* operator -> ();

};

template <class T>

PolymorphicPtr<T>::PolymorphicPtr(T* data)
{

	if (!data) throw std::logic_error("Error");
	this->data = data;

}

template <class T>

PolymorphicPtr<T>::PolymorphicPtr(PolymorphicPtr&& other) noexcept
{

	moveTo(std::move(other));

}

template <class T>

PolymorphicPtr<T>::PolymorphicPtr(const PolymorphicPtr& other) 
{

	copyFrom(other);

}

template <class T>

PolymorphicPtr<T>& PolymorphicPtr<T>::operator = (PolymorphicPtr&& other) noexcept
{

	if (this != &other)
	{

		free();
		moveTo(std::move(other));

	}

	return *this;

}

template <class T>

PolymorphicPtr<T>& PolymorphicPtr<T>::operator = (const PolymorphicPtr& other)
{

	if (this != &other)
	{

		free();
		copyFrom(other);

	}

	return *this;

}

template <class T>

PolymorphicPtr<T>::~PolymorphicPtr()
{

	free();

}

template <class T>

const T& PolymorphicPtr<T>::operator * () const
{

	if (!data) throw std::logic_error("Error");
	return *data;

}

template <class T>

T& PolymorphicPtr<T>::operator * ()
{

	if (!data) throw std::logic_error("Error");
	return *data;

}

template <class T>

const T* PolymorphicPtr<T>::operator -> () const
{

	if (!data) throw std::logic_error("Error");
	return data;

}

template <class T>

T* PolymorphicPtr<T>::operator -> ()
{

	if (!data) throw std::logic_error("Error");
	return data;

}

template <class T>

void PolymorphicPtr<T>::moveTo(PolymorphicPtr&& other)
{

	data = other.data;
	other.data = nullptr;

}

template <class T>

void PolymorphicPtr<T>::free()
{

	delete data;
	data = nullptr;

}

template <class T>

void PolymorphicPtr<T>::copyFrom(const PolymorphicPtr& other) 
{

	data = other.data->clone();

}

