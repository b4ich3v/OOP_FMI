#include <iostream>
#pragma once

template <class T>

class Vector 
{
private:

	T* data = nullptr;
	size_t size = 0;
	size_t capacity = 8;

	void free();

	void copyFrom(const Vector& other);

	void moveTo(Vector&& other);

	void resize(size_t newCapacity);

public:

	Vector();

	Vector(const Vector& other);

	Vector(Vector&& other) noexcept;

	Vector& operator = (const Vector& other);

	Vector& operator = (Vector&& other) noexcept;

	~Vector();

	void push_back(const T& element);

	void push_back(T&& element);

	void pop_back();

	bool isEmpty() const;

	size_t getSize() const;

	size_t getCapacity() const;

	const T& operator [] (size_t index) const;

	T& operator [] (size_t index);

};

template <class T>

void Vector<T>::free() 
{

	delete[] data;
	data = nullptr;
	size = 0;
	capacity = 0;

}

template <class T>

void Vector<T>::copyFrom(const Vector<T>& other) 
{

	data = new T[other.capacity]{};
	size = other.size;
	capacity = other.capacity;

	for (int i = 0; i < size; i++)
	{

		data[i] = other.data[i];

	}

}

template <class T>

void Vector<T>::moveTo(Vector<T>&& other) 
{

	data = other.data;
	size = other.size;
	capacity = other.capacity;

	other.data = nullptr;
	other.size = 0;
	other.capacity = 8;

}

template <class T>

void Vector<T>::resize(size_t newCapacity) 
{

	if (newCapacity <= capacity) return;

	T* newData = new T[newCapacity]{};

	for (int i = 0; i < size; i++)
	{

		newData[i] = data[i];

	}

	delete[] data;
	data = newData;
	capacity = newCapacity;

}

template <class T>

Vector<T>::Vector() 
{

	capacity = 8;
	size = 0;
	data = new T[capacity]{};

}

template <class T>

Vector<T>::Vector(const Vector<T>& other) 
{

	copyFrom(other);

}

template <class T>

Vector<T>::Vector(Vector<T>&& other) noexcept 
{

	moveTo(std::move(other));

}

template <class T>

Vector<T>& Vector<T>::operator = (const Vector<T>& other) 
{

	if (this != &other) 
	{

		free();
		copyFrom(other);

	}

	return *this;

}

template <class T>

Vector<T>& Vector<T>::operator = (Vector<T>&& other) noexcept
{

	if (this != &other)
	{

		free();
		moveTo(std::move(other));

	}

	return *this;

}

template <class T>

Vector<T>::~Vector() 
{

	free();

}

template <class T>

void Vector<T>::push_back(const T& element) 
{

	if (size == capacity) resize(capacity * 2);

	data[size++] = element;

}

template <class T>

void Vector<T>::push_back(T&& element) 
{

	if (size == capacity) resize(capacity * 2);

	data[size++] = std::move(element);

}

template <class T>

void Vector<T>::pop_back() 
{

	if (size == 0) throw std::logic_error("Error");

	size -= 1;

}

template <class T>

bool Vector<T>::isEmpty() const 
{

	return size == 0;

}

template <class T>

size_t Vector<T>::getSize() const 
{

	return size;

}

template <class T>

size_t Vector<T>::getCapacity() const 
{

	return capacity;

}

template <class T>

const T& Vector<T>::operator [] (size_t index) const 
{

	if (index >= size) throw std::logic_error("Error");

	return data[index];

}

template <class T>

T& Vector<T>::operator [] (size_t index)
{

	if (index >= size) throw std::logic_error("Error");

	return data[index];

}

