#include <cstddef>
#include <utility>
#pragma once

template<typename T>

class MySharedPtr
{
private:

    T* ptr;
    size_t* count;

    void release();

public:

    MySharedPtr() noexcept;

    explicit MySharedPtr(T* p);

    MySharedPtr(const MySharedPtr& other) noexcept;

    MySharedPtr(MySharedPtr&& other) noexcept;

    MySharedPtr& operator = (const MySharedPtr& other) noexcept;

    MySharedPtr& operator = (MySharedPtr&& other) noexcept;

    ~MySharedPtr();

    T* get() const noexcept;

    T& operator * () const noexcept;

    T* operator -> () const noexcept;

    size_t use_count() const noexcept;

    explicit operator bool() const noexcept;

    void reset() noexcept;

    void reset(T* ptr);

    void swap(MySharedPtr& other) noexcept;

};

template<typename T>

void MySharedPtr<T>::release()
{

    if (count && --(*count) == 0)
    {

        delete ptr;
        delete count;

    }

    ptr = nullptr;
    count = nullptr;

}

template<typename T>

MySharedPtr<T>::MySharedPtr() noexcept :
    ptr(nullptr), count(nullptr) {}

template<typename T>

MySharedPtr<T>::MySharedPtr(T* ptr) :
    ptr(ptr), count(new size_t(1)) {}

template<typename T>

MySharedPtr<T>::MySharedPtr(const MySharedPtr& other) noexcept :
    ptr(other.ptr), count(other.count)
{

    if (count) ++(*count);

}

template<typename T>

MySharedPtr<T>::MySharedPtr(MySharedPtr&& other) noexcept :
    ptr(other.ptr), count(other.count)
{

    other.ptr = nullptr;
    other.count = nullptr;

}

template<typename T>

MySharedPtr<T>& MySharedPtr<T>::operator = (const MySharedPtr& other) noexcept
{

    if (this != &other)
    {

        release();
        ptr = other.ptr;
        count = other.count;

        if (count) ++(*count);

    }

    return *this;

}

template<typename T>

MySharedPtr<T>& MySharedPtr<T>::operator = (MySharedPtr&& other) noexcept
{

    if (this != &other)
    {

        release();
        ptr = other.ptr;
        count = other.count;
        other.ptr = nullptr;
        other.count = nullptr;

    }

    return *this;

}

template<typename T>

MySharedPtr<T>::~MySharedPtr()
{

    release();

}

template<typename T>

T* MySharedPtr<T>::get() const noexcept
{

    return ptr;

}

template<typename T>

T& MySharedPtr<T>::operator * () const noexcept
{

    return *ptr;

}

template<typename T>

T* MySharedPtr<T>::operator -> () const noexcept
{

    return ptr;

}

template<typename T>

size_t MySharedPtr<T>::use_count() const noexcept
{

    return count ? *count : 0;

}

template<typename T>

MySharedPtr<T>::operator bool() const noexcept
{

    return ptr != nullptr;

}

template<typename T>

void MySharedPtr<T>::reset() noexcept
{

    release();

}

template<typename T>

void MySharedPtr<T>::reset(T* ptr)
{

    release();
    this->ptr = ptr;
    count = new size_t(1);

}

template<typename T>

void MySharedPtr<T>::swap(MySharedPtr& other) noexcept
{

    using std::swap;
    swap(ptr, other.ptr);
    swap(count, other.count);

}

template<typename T>

void swap(MySharedPtr<T>& left, MySharedPtr<T>& right) noexcept
{

    left.swap(right);

}
