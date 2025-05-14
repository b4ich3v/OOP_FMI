#include <iostream>
#include "MyString.h"

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

int main() 
{
 
    MyPair<int, int> p1{ 1, 2 };
    MyPair<int, int> p2{ 1, 2 };
    MyPair<int ,int> p3{ 2, 1 };      

    std::cout << "p1 = (" << p1.first << ", " << p1.second << ")" << std::end;
    std::cout << "p2 = (" << p2.first << ", " << p2.second << ")" << std::end;
    std::cout << "p3 = (" << p3.first << ", " << p3.second << ")" << std::end;

    std::cout << "p1 == p2? " << (p1 == p2) << std::end;
    std::cout << "p1 != p3? " << (p1 != p3) << std::end;

    std::cout << "p1 <  p3? " << (p1 < p3) << std::end;
    std::cout << "p3 >  p2? " << (p3 > p2) << std::end;
    std::cout << "p1 <= p2? " << (p1 <= p2) << std::end;
    std::cout << "p3 >= p1? " << (p3 >= p1) << std::end;

    MyPair<MyString, double> ps1{ "Alice", 3.14 };
    MyPair<MyString, double> ps2{ "Bob",   2.71 };

    std::cout << "ps1 = (" << ps1.first << ", " << ps1.second << ")" << std::endl;
    std::cout << "ps2 = (" << ps2.first << ", " << ps2.second << ")" << std::endl;

    std::cout << "ps1 < ps2?  " << (ps1 < ps2) << std::endl;
    std::cout << "ps1 >= ps2? " << (ps1 >= ps2) << std::endl;

    return 0;

}
