#include <iostream>
#pragma once

template <class T>

class MyVector 
{
private:

public:

	T* data = nullptr;
	size_t sizeOfData = 0;
	size_t capacity = 8;

	void free();

	void copyFrom(const MyVector& other);

	void moveTo(MyVector&& other);

	void resize(size_t newCapacity);

public:

	MyVector();

	MyVector(const T* data, size_t sizeOfData);

	MyVector(const MyVector& other);

	MyVector(MyVector&& other) noexcept;

	MyVector& operator = (const MyVector& other);

	MyVector& operator = (MyVector&& other) noexcept;

	~MyVector();

	const T& operator [] (size_t index) const;

	T& operator [] (size_t index);

    template<class U>

	friend std::ostream& operator << (std::ostream& os, const MyVector<U>& v);

    template<class U>

	friend std::istream& operator >> (std::istream& is, MyVector<U>& v);

	void pop_back();

	void push_back(const T& element);

    void clear();

	bool empty() const;

	size_t size() const;

};

template <class T>

void MyVector<T>::free()
{

    delete[] data;
    data = nullptr;
    sizeOfData = 0;
    capacity = 8;

}

template <class T>

void MyVector<T>::copyFrom(const MyVector& other)
{

    data = new T[other.capacity];
    sizeOfData = other.sizeOfData;
    capacity = other.capacity;

    for (size_t i = 0; i < sizeOfData; i++) data[i] = other.data[i];
        
}

template <class T>

void MyVector<T>::moveTo(MyVector&& other)
{

    data = other.data;
    sizeOfData = other.sizeOfData;
    capacity = other.capacity;

    other.data = nullptr;
    other.sizeOfData = 0;
    other.capacity = 8;

}

template <class T>

void MyVector<T>::resize(size_t newCapacity) 
{

    if (newCapacity <= capacity) return;
    if (newCapacity < 1) newCapacity = 1;

    T* newData = new T[newCapacity] {};

    for (size_t i = 0; i < sizeOfData; i++) newData[i] = data[i];

    delete[] data;
    data = newData;
    capacity = newCapacity;

}

template <class T>

MyVector<T>::MyVector() 
{

    capacity = 8;
    sizeOfData = 0;
    data = new T[capacity]{};

}

template <class T>

MyVector<T>::MyVector(const T* arr, size_t size)
    : data(nullptr), sizeOfData(size), capacity(size > 8 ? size : 8) 
{

    data = new T[capacity];
    for (size_t i = 0; i < sizeOfData; i++) data[i] = arr[i];
        
}

template <class T>

MyVector<T>::MyVector(const MyVector& other) 
{

    copyFrom(other);

}

template <class T>

MyVector<T>::MyVector(MyVector&& other) noexcept
{

    moveTo(std::move(other));

}

template <class T>

MyVector<T>& MyVector<T>::operator = (const MyVector& other)
{

    if (this != &other) 
    {

        free();
        copyFrom(other);

    }

    return *this;

}

template <class T>

MyVector<T>& MyVector<T>::operator = (MyVector&& other) noexcept 
{

    if (this != &other) 
    {

        free();
        moveTo(std::move(other));

    }

    return *this;

}

template <class T>

MyVector<T>::~MyVector()
{

    delete[] data;

}

template <class T>

const T& MyVector<T>::operator[](size_t index) const 
{

    if (index < 0 || index >= sizeOfData) throw std::out_of_range("Vector index out of range");
    return data[index];

}

template <class T>

T& MyVector<T>::operator[](size_t index)
{

    if (index < 0 || index >= sizeOfData) throw std::out_of_range("Vector index out of range");
    return data[index];

}

template <class T>

void MyVector<T>::pop_back() 
{

    if (empty()) throw std::out_of_range("pop_back() on empty Vector");
    sizeOfData -= 1;
    
}

template <class T>

void MyVector<T>::push_back(const T& element)
{

    if (sizeOfData >= capacity) resize(capacity * 2);
    data[sizeOfData++] = element;

}

template <class T>

bool MyVector<T>::empty() const 
{

    return sizeOfData == 0;

}

template <class T>

void MyVector<T>::clear() 
{

    sizeOfData = 0;

}

template <class T>

size_t MyVector<T>::size() const 
{

    return sizeOfData;

}

template <class T>

std::ostream& operator << (std::ostream& os, const MyVector<T>& v) 
{

    os << '[';

    for (size_t i = 0; i < v.sizeOfData; i++)
    {

        os << v.data[i];
        if (i + 1 < v.sizeOfData) os << ", ";

    }

    os << ']';

    return os;

}

template <class T>

std::istream& operator >> (std::istream& is, MyVector<T>& v)
{

    size_t newSize;
    if (!(is >> newSize)) return is;

    v.free();
    v.capacity = 8;
    v.data = new T[v.capacity]{};

    while (newSize > v.capacity) v.resize(v.capacity * 2);
    v.sizeOfData = newSize;

    for (size_t i = 0; i < newSize; i++) is >> v.data[i];
     
    return is;

}
