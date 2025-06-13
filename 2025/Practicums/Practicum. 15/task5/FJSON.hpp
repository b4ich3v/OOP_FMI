#pragma once
#include "CustomPair.hpp"
#include "Vector.hpp"
#include <fstream>

template <class K, class V>

class FJSON
{
private:

	CustomPair<K, V>** pairs;
	size_t size = 0;
	size_t capacity = 8;

	void free();

	void copyFrom(const FJSON& other);

	void moveTo(FJSON&& other);

	void resize(size_t newCapacity);

public:

	FJSON();

	FJSON(const FJSON& other);

	FJSON(FJSON&& other) noexcept;

	FJSON& operator = (const FJSON& other);

	FJSON& operator = (FJSON&& other) noexcept;

	~FJSON();

	void addPair(CustomPair<K,V>* pair);

	void removePair(size_t index);

	void saveToFile(std::ofstream& file) const;

};

template <class K, class V>

void FJSON<K, V>::free() 
{

	for (int i = 0; i < capacity; i++)
	{

		if (pairs[i] != nullptr)
			delete pairs[i];

		pairs[i] = nullptr;

	}

	delete[] pairs;
	pairs = nullptr;
	capacity = 8;
	size = 0;

}

template <class K, class V>

void FJSON<K, V>::copyFrom(const FJSON& other) 
{

	size = other.size;
	capacity = other.capacity;
	pairs = new CustomPair<K, V>* [capacity] {nullptr};

	for (int i = 0; i < capacity; i++)
	{

		if (other.pairs[i] != nullptr)
			pairs[i] = other.pairs[i]->clone();

	}

}

template <class K, class V>

void FJSON<K, V>::moveTo(FJSON<K, V>&& other) 
{

	pairs = other.pairs;
	size = other.size;
	capacity = other.capacity;

	other.pairs = nullptr;
	other.size = 0;
	other.capacity = 0;

}

template <class K, class V>

void FJSON<K, V>::resize(size_t newCapacity) 
{

	if (newCapacity <= capacity) return;

	CustomPair<K, V>** newPairs = new CustomPair<K, V>* [newCapacity] {nullptr};

	for (int i = 0; i < capacity; i++)
	{
		newPairs[i] = pairs[i];

	}

	delete[] pairs;
	pairs = newPairs;
	capacity = newCapacity;

}

template <class K, class V>

FJSON<K, V>::FJSON() 
{

	capacity = 8;
	size = 0;
	pairs = new CustomPair<K, V>* [capacity] {nullptr};

}

template <class K, class V>

FJSON<K, V>::FJSON(const FJSON& other) 
{

	copyFrom(other);

}

template <class K, class V>

FJSON<K, V>::FJSON(FJSON&& other) noexcept 
{

	moveTo(std::move(other));

}

template <class K, class V>

FJSON<K, V>& FJSON<K, V>::operator = (const FJSON& other) 
{

	if (this != &other) 
	{

		free();
		copyFrom(other);

	}

	return *this;

}

template <class K, class V>

FJSON<K, V>& FJSON<K, V>::operator = (FJSON&& other) noexcept 
{

	if (this != &other)
	{

		free();
		moveTo(std::move(other));

	}

	return *this;

}

template <class K, class V>

FJSON<K, V>::~FJSON() 
{

	free();

}

template <class K, class V>

void FJSON<K, V>::addPair(CustomPair<K, V>* pair) 
{

	if (size == capacity) resize(capacity * 2);
	pairs[size++] = pair->clone();

}

template <class K, class V>

void FJSON<K, V>::removePair(size_t index) 
{

	if (index > capacity || pairs[index] == nullptr || size == 0) throw std::logic_error("Error");

	delete pairs[index];
	pairs[index] = nullptr;
	size -= 1;

}

template <class K, class V>

void FJSON<K, V>::saveToFile(std::ofstream& file) const
{

	if (!file.is_open()) return;

	for (int i = 0; i < capacity; i++)
	{

		if (pairs[i] != nullptr)
		{

			file << "{";
			file << (pairs[i]->getFormat());
			file << "}\n";

		}

	}

}
