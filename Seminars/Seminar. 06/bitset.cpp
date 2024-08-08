#include <iostream>
#include "bitset.h"

Bitset::Bitset() : data(nullptr), buckets(0), capacity(8)
{

    data = new char[capacity](); 

}

Bitset::~Bitset()
{

    free();

}

int Bitset::getBucket(int number) const
{

    return number / 8;

}

int Bitset::getIndex(int number) const
{

    return number % 8;

}

Bitset::Bitset(int number) : capacity(8)
{

    buckets = getBucket(number) + 1;
    data = new char[buckets](); 

}

Bitset::Bitset(const Bitset& other)
{

    copyFrom(other);

}

void Bitset::copyFrom(const Bitset& other)
{

    data = new char[other.buckets];
    std::memcpy(data, other.data, other.buckets);
    buckets = other.buckets;
    capacity = other.capacity;

}

Bitset& Bitset::operator=(const Bitset& other)
{

    if (this != &other)
    {

        free();
        copyFrom(other);

    }

    return *this;

}

void Bitset::free()
{

    delete[] data;
    data = nullptr;
    buckets = 0;

}

void Bitset::resize()
{

    int newCapacity = buckets * 2;
    char* newData = new char[newCapacity](); 

    std::memcpy(newData, data, buckets);
    delete[] data;
    data = newData;
    buckets = newCapacity;

}

void Bitset::addNumber(int number)
{

    int bucketForNumber = getBucket(number);

    if (bucketForNumber >= buckets)
    {
        
        while (bucketForNumber >= buckets)
        {

            resize();

        }

    }

    int indexForNumber = getIndex(number);
    data[bucketForNumber] |= (1 << indexForNumber);

}

bool Bitset::hasNumber(int number) const
{

    int bucketForNumber = getBucket(number);

    if (bucketForNumber >= buckets)
    {

        return false; 

    }

    int indexForNumber = getIndex(number);
    return (data[bucketForNumber] & (1 << indexForNumber)) != 0;

}

void Bitset::removeNumber(int number)
{

    if (!hasNumber(number))
    {

        std::cout << "Number already removed or not present in the bitset." << std::endl;
        return;

    }

    int bucketForNumber = getBucket(number);

    if (bucketForNumber >= buckets)
    {

        std::cout << "Number out of range." << std::endl;
        return;

    }

    int indexForNumber = getIndex(number);
    data[bucketForNumber] &= ~(1 << indexForNumber);

}

void Bitset::print() const
{

    for (int i = 0; i < buckets * 8; ++i)
    {

        if (hasNumber(i))
        {

            std::cout << i << " ";

        }

    }

    std::cout << std::endl;

}

Bitset Union(const Bitset& lhs, const Bitset& rhs)
{

    int newBuckets = std::max(lhs.buckets, rhs.buckets);
    Bitset toReturn(newBuckets * 8);

    for (int i = 0; i < newBuckets; ++i)
    {

        char lhsData = i < lhs.buckets ? lhs.data[i] : 0;
        char rhsData = i < rhs.buckets ? rhs.data[i] : 0;
        toReturn.data[i] = lhsData | rhsData;

    }

    return toReturn;

}

Bitset Intersect(const Bitset& lhs, const Bitset& rhs)
{

    int newBuckets = std::min(lhs.buckets, rhs.buckets);
    Bitset toReturn(newBuckets * 8);

    for (int i = 0; i < newBuckets; ++i)
    {

        toReturn.data[i] = lhs.data[i] & rhs.data[i];

    }

    return toReturn;

}
