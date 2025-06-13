#include "Set.hpp"
#pragma once

template <class T>

class ManySets 
{
private:

	Set<T>** sets = nullptr;
	size_t size = 0;
	size_t capacity = 0;

	void free();

	void copyFrom(const ManySets& other);

	void moveTo(ManySets&& other);

	void resize(size_t newCapacity);

public:

	ManySets();

	ManySets(const ManySets& other);

	ManySets(ManySets&& other) noexcept;

	ManySets& operator = (const ManySets& other);

	ManySets& operator = (ManySets&& other) noexcept;

	~ManySets();

	void addElement(Set<T>* elemenet);

	void removeElement(size_t index);

	Set<T>* operator [] (size_t index) const;

	template <class V>

	friend std::ostream& operator << (std::ostream& os, const ManySets<V>& manySets);

	template <class V>

	friend std::istream& operator >> (std::istream& is, ManySets<V>& manySets);

};

template <class T>

void ManySets<T>::free() 
{

	for (int i = 0; i < capacity; i++)
	{

		delete sets[i];
		sets[i] = nullptr;

	}

	delete[] sets;
	sets = nullptr;
	size = 0;
	capacity = 0;

}

template <class T>

void ManySets<T>::copyFrom(const ManySets& other) 
{

	capacity = other.capacity;
	size = other.size;

	for (int i = 0; i < capacity; i++)
	{

		sets[i] = other.sets[i]->clone();

	}

}

template <class T>

void ManySets<T>::moveTo(ManySets&& other) 
{

	sets = other.sets;
	capacity = other.capacity;
	size = other.size;

	other.sets = nullptr;
	other.capacity = 0;
	other.size = 0;

}

template <class T>

void ManySets<T>::resize(size_t newCapacity) 
{

	if (newCapacity <= capacity) return;

	Set<T>** newSets = new Set<T>*[newCapacity]{ nullptr };

	for (int i = 0; i < capacity; i++)
	{

		newSets[i] = sets[i];

	}

	delete[] sets;
	sets = newSets;
	capacity = newCapacity;

}

template <class T>

ManySets<T>::ManySets() 
{

	capacity = 8;
	sets = new Set<T>*[capacity] { nullptr };
	size = 0;

}

template <class T>

ManySets<T>::ManySets(const ManySets& other) 
{

	copyFrom(other);

}

template <class T>

ManySets<T>::ManySets(ManySets&& other) noexcept 
{

	moveTo(std::move(other));

}

template <class T>

ManySets<T>& ManySets<T>::operator = (const ManySets& other) 
{

	if (this != &other) 
	{

		free();
		copyFrom(other);

	}

	return *this;

}

template <class T>

ManySets<T>& ManySets<T>::operator = (ManySets&& other) noexcept 
{

	if (this != &other)
	{

		free();
		moveTo(std::move(other));

	}

	return *this;


}

template <class T>

ManySets<T>::~ManySets() 
{

	free();

}

template <class T>

void ManySets<T>::addElement(Set<T>* elemenet)  
{

	if (size == capacity) resize(capacity * 2);

	sets[size++] = elemenet->clone();

}

template <class T>

void ManySets<T>::removeElement(size_t index)
{

	if (index >= size) throw std::logic_error("Error");

	delete sets[index];
	sets[index] = nullptr;
	size -= 1;

}

template <class T>

std::ostream& operator << (std::ostream& os, const ManySets<T>& manySets)
{

	for (int i = 0; i < manySets.capacity; i++)
	{

		if (manySets.sets[i] != nullptr) 
		{

			manySets.sets[i]->serialize(os);
			os << " ";

		}

	}

	return os;

}

template <class T>

std::istream& operator >> (std::istream& is, ManySets<T>& manySets) 
{

	for (int i = 0; i < manySets.size; i++) 
	{

		if (manySets.sets[i] != nullptr)
		{

			manySets.sets[i]->deserialize(is);

		}

	}

	return is;

}

template <class T>

Set<T>* ManySets<T>::operator [] (size_t index) const 
{

	if (index >= size) throw std::out_of_range("Error");
	return sets[index];

}
