#pragma once
#include <iostream>
#include <cstddef>
#include <cstdint>

typedef bool (*predicate)(int);

namespace HELPERS
{

    bool isPrime(int number);

    bool hasDiffDigits(int number);

    bool isPalindrome(int number);

    size_t getCountOfDigits(int number);

    size_t getCountByCondition(int start, int end, predicate func);

}

class Interval
{
private:

    int start;
    int end;

    void setStart(int start);

    void setEnd(int end);

public:

    Interval();

    Interval(int start, int end);

    size_t getLen() const;

    bool isInInterval(int number) const;

    size_t countOfPrimesInInterval() const;

    size_t countOfPalindromesInInterval() const;

    size_t countOfNumbersWDDInInterval() const;

    bool areStartAndEndAPOT() const;

    void intersection(const Interval& other);

    bool isSubinterval(const Interval& other) const;

    void print() const;

};
