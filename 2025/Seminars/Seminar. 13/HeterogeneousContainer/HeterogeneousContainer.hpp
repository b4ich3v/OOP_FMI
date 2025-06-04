#include <iostream>
#define TT template<class T>
#pragma once

TT

class HeterogeneousContainer 
{
private:

	T** data = nullptr;
	size_t size = 0;
	size_t capacity = 8;

	void resize(size_t newSize);

	void free();

	void copyFrom(const HeterogeneousContainer& other);

	void moveTo(HeterogeneousContainer&& other);

public:

	HeterogeneousContainer();

	HeterogeneousContainer(const HeterogeneousContainer<T>& other);

	HeterogeneousContainer(HeterogeneousContainer&& other) noexcept;

	HeterogeneousContainer& operator = (const HeterogeneousContainer& other);

	HeterogeneousContainer& operator = (HeterogeneousContainer&& other) noexcept;

	~HeterogeneousContainer();

	void addElement(const T& element);

	void addElement(T* element);

	void removeElement(size_t index);

	size_t getSize() const;

	T* operator [] (size_t index);

	const T* operator [] (size_t index) const;

};

TT

HeterogeneousContainer<T>::HeterogeneousContainer() 
{

	this->size = 0;
	this->capacity = 8;
	this->data = new T*[capacity]{};

}

TT

HeterogeneousContainer<T>::HeterogeneousContainer(const HeterogeneousContainer<T>& other)
{

	copyFrom(other);

}

TT

HeterogeneousContainer<T>::HeterogeneousContainer(HeterogeneousContainer<T>&& other) noexcept
{

	moveTo(std::move(other));

}

TT

HeterogeneousContainer<T>& HeterogeneousContainer<T>::operator = (const HeterogeneousContainer<T>& other)
{

	if(this != &other)
	{

		free();
		copyFrom(other);

	}

	return *this;

}

TT

HeterogeneousContainer<T>& HeterogeneousContainer<T>::operator = (HeterogeneousContainer<T>&& other) noexcept
{

	if (this != &other)
	{

		free();
		moveTo(std::move(other));

	}

	return *this;

}

TT

HeterogeneousContainer<T>::~HeterogeneousContainer() 
{

	free();

}

TT

void HeterogeneousContainer<T>::resize(size_t newCapacity) 
{

	if (newCapacity <= capacity) return;

	T** newData = new T*[newCapacity]{ nullptr };

	for (int i = 0; i < newCapacity; i++)
	{

		newData[i] = data[i];

	}

	delete[] data;
	data = newData;
	capacity = newCapacity;

}

TT

void HeterogeneousContainer<T>::free() 
{

	for (int i = 0; i < capacity; i++)
	{

		delete data[i];
		data[i] = nullptr;

	}

	delete[] data;
	data = nullptr;
	size = 0;
	capacity = 8;

}

TT

void HeterogeneousContainer<T>::copyFrom(const HeterogeneousContainer<T>& other) 
{

	this->data = new T*[other.capacity]{ nullptr };
	this->size = other.size;
	this->capacity = other.capacity;

	for (int i = 0; i < other.capacity; i++)
	{

		this->data[i] = other.data[i]->clone();

	}

}

TT

void HeterogeneousContainer<T>::moveTo(HeterogeneousContainer<T>&& other) 
{

	data = other.data;
	size = other.size;
	capacity = other.capacity;

	other.data = nullptr;
	other.size = 0;
	other.capacity = 0;

}

TT

void HeterogeneousContainer<T>::addElement(const T& element) 
{

	if (size == capacity) resize(capacity * 2);

	data[size] = element.clone();
	size += 1;

}

TT

void HeterogeneousContainer<T>::addElement(T* element) 
{

	if (!element) throw std::logic_error("Error");
	if (size == capacity) resize(capacity * 2);

	data[size] = element->clone();
	size += 1;

}

TT

void HeterogeneousContainer<T>::removeElement(size_t index) 
{

	if (index < 0 || index >= capacity) 
	{

		throw std::logic_error("Error");

	}

	delete data[index];
	data[index] = nullptr;
	size -= 1;

}

TT

size_t HeterogeneousContainer<T>::getSize() const 
{

	return size;

}

TT

T* HeterogeneousContainer<T>::operator [] (size_t index) 
{

	if (index < 0 || index >= capacity) throw std::logic_error("Error");
	return data[index];

}

TT

const T* HeterogeneousContainer<T>::operator [] (size_t index) const
{

	if (index < 0 || index >= capacity) throw std::logic_error("Error");
	return data[index];

}
