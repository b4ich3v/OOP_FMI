#pragma once

template<class T1 = int, class T2 = int>

struct MyPair
{
public:

    T1 first;
    T2 second;

    MyPair() = default;

    MyPair(const T1& a, const T2& b);

    bool operator == (const MyPair& other) const;

    bool operator != (const MyPair& other) const;

    bool operator < (const MyPair& other) const;

    bool operator <=(const MyPair& other) const;

    bool operator > (const MyPair& other) const;

    bool operator >= (const MyPair& other) const;

};

template<class T1, class T2>

MyPair<T1, T2>::MyPair(const T1& a, const T2& b):
    first(a), second(b) {}

template<class T1, class T2>

bool MyPair<T1, T2>::operator == (const MyPair& other) const
{

    return first == other.first && second == other.second;

}

template<class T1, class T2>

bool MyPair<T1, T2>::operator != (const MyPair& other) const
{

    return !(*this == other);

}

template<class T1, class T2>

bool MyPair<T1, T2>::operator < (const MyPair& other) const
{

    if (first < other.first) return true;
    if (other.first < first) return false;

    return second < other.second;

}

template<class T1, class T2>

bool MyPair<T1, T2>::operator <= (const MyPair& other) const
{

    return !(other < *this);

}

template<class T1, class T2>

bool MyPair<T1, T2>::operator > (const MyPair& other) const
{

    return other < *this;

}

template<class T1, class T2>

bool MyPair<T1, T2>::operator >= (const MyPair& other) const
{

    return !(*this < other);

}
