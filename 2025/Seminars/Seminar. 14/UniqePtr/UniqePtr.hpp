#include <iostream>
#pragma once

template <class T>

class UniqePtr 
{
private:

	T* data = nullptr;

	void moveTo(UniqePtr&& other);

	void free();

public:

	UniqePtr(T* data);

	UniqePtr(const UniqePtr& other) = delete;

	UniqePtr(UniqePtr&& other) noexcept;

	UniqePtr& operator = (const UniqePtr& other) = delete;

	UniqePtr& operator = (UniqePtr&& other) noexcept;

	~UniqePtr();

	const T& operator * () const;

	T& operator * ();

	const T* operator -> () const;

	T* operator -> ();

};

template <class T>

UniqePtr<T>::UniqePtr(T* data) 
{

	if (!data) throw std::logic_error("Error");
	this->data = data;

}

template <class T>

UniqePtr<T>::UniqePtr(UniqePtr&& other) noexcept 
{

	moveTo(std::move(other));

}

template <class T>

UniqePtr<T>& UniqePtr<T>::operator = (UniqePtr&& other) noexcept 
{

	if (this != &other) 
	{
		
		free();
		moveTo(std::move(other));

	}

	return *this;

}

template <class T>

UniqePtr<T>::~UniqePtr() 
{

	free();

}

template <class T>

const T& UniqePtr<T>::operator * () const 
{

	if (!data) throw std::logic_error("Error");
	return *data;

}

template <class T>

T& UniqePtr<T>::operator * ()
{

	if (!data) throw std::logic_error("Error");
	return *data;

}

template <class T>

const T* UniqePtr<T>::operator -> () const 
{

	if (!data) throw std::logic_error("Error");
	return data;

}

template <class T>

T* UniqePtr<T>::operator -> () 
{

	if (!data) throw std::logic_error("Error");
	return data;

}

template <class T>

void UniqePtr<T>::moveTo(UniqePtr&& other) 
{

	data = other.data;
	other.data = nullptr;

}

template <class T>

void UniqePtr<T>::free() 
{

	delete data;
	data = nullptr;

}
