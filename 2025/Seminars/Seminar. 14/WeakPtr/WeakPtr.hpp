#include <iostream>
#pragma once

class CommunicationPipe
{
private:

    size_t countOfSharedPtrs = 0;
    size_t countOfWeakPtrs = 0;

public:

    void addSharedPtr()
    {

        countOfSharedPtrs += 1;
        if (countOfSharedPtrs == 1) countOfWeakPtrs += 1;

    }

    void removeSharedPtr()
    {

        countOfSharedPtrs -= 1;
        if (countOfSharedPtrs == 0) countOfWeakPtrs -= 1;

    }

    void addWeakPtr()
    {

        countOfWeakPtrs += 1;

    }

    void removeWeakPtr()
    {

        countOfWeakPtrs -= 1;

    }

    bool noOwners() const
    {

        return countOfSharedPtrs == 0;

    }

    bool noVisitors() const
    {

        return countOfWeakPtrs == 0;

    }

    size_t getCountOfSharedPtrs() const
    {

        return countOfSharedPtrs;

    }

    size_t getCountOfWeakPtrs() const
    {

        return countOfWeakPtrs;

    }

};

template <class T>

class SharedPtr;

template <class T>

class WeakPtr 
{
private:

    friend class SharedPtr;

    T* data = nullptr;
    CommunicationPipe* pipe = nullptr;

    void free();

    void copyFrom(const WeakPtr& other);

    void moveFrom(WeakPtr&& other);

public:

    WeakPtr();

    WeakPtr(const SharedPtr<T>& sharedPtr);

    WeakPtr(const WeakPtr& other);

    WeakPtr(WeakPtr&& other) noexcept;

    WeakPtr& operator = (const WeakPtr& other);

    WeakPtr& operator = (WeakPtr&& other) noexcept;

    ~WeakPtr();

    SharedPtr<T> lock() const;

    size_t use_count() const;

    bool expired() const;

};

template <class T>

WeakPtr<T>::WeakPtr(): 
    data(nullptr), pipe(nullptr) {}

template <class T>

WeakPtr<T>::WeakPtr(const SharedPtr<T>& sharedPtr): 
    data(sharedPtr.data), pipe(sharedPtr.pipe)
{

    if (pipe) pipe->addWeakPtr();

}

template <class T>

WeakPtr<T>::WeakPtr(const WeakPtr& other):
    data(other.data), pipe(other.pipe)
{

    if (pipe) pipe->addWeakPtr();

}

template <class T>

WeakPtr<T>::WeakPtr(WeakPtr&& other): 
    data(other.data), pipe(other.pipe)
{

    other.data = nullptr;
    other.pipe = nullptr;

}

template <class T>

WeakPtr<T>& WeakPtr<T>::operator = (const WeakPtr& other) 
{

    if (this != &other) 
    {

        free();
        copyFrom(other);

    }

    return *this;

}

template <class T>

WeakPtr<T>& WeakPtr<T>::operator = (WeakPtr&& other) noexcept 
{

    if (this != &other) 
    {

        free();
        moveFrom(std::move(other));

    }

    return *this;

}

template <class T>

WeakPtr<T>::~WeakPtr() 
{

    free();

}

template <class T>

SharedPtr<T> WeakPtr<T>::lock() const
{

    if (pipe && !pipe->noOwners()) 
    {

        SharedPtr<T> sharedPtr;
        sharedPtr.data = data;
        sharedPtr.pipe = pipe;
        pipe->addSharedPtr();

        return sharedPtr;

    }

    return SharedPtr<T>();

}

template <class T>

size_t WeakPtr<T>::use_count() const 
{

    return pipe ? pipe->getCountOfSharedPtrs() : 0;

}

template <class T>

bool WeakPtr<T>::expired() const noexcept 
{

    return !pipe || pipe->noOwners();

}

template <class T>

void WeakPtr<T>::free()  
{

    if (pipe) 
    {

        pipe->removeWeakPtr();

        if (pipe->noOwners() && pipe->noVisitors())
        {

            delete pipe;
            pipe = nullptr;

        }

        data = nullptr;

    }

}

template <class T>

void WeakPtr<T>::copyFrom(const WeakPtr& other)
{

    data = other.data;
    pipe = other.pipe;
    if (pipe) pipe->addWeakPtr();

}

template <class T>

void WeakPtr<T>::moveFrom(WeakPtr&& other)  
{

    data = other.data;
    pipe = other.pipe;

    other.data = nullptr;
    other.pipe = nullptr;

}

