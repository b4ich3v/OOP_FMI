#pragma once

class MultiSet
{
private:

    char* data;
    int limit;
    int bitsForNumber;

    int getArrayIndex(int number) const;

    int getBitPosition(int number) const;

    void setCount(int number, int count);

    int getCount(int number) const;

    static int min(int a, int b);

    static int max(int a, int b);

    static void swapForIntegers(int& a, int& b);

    static void swapForStrings(char*& a, char*& b);

public:

    MultiSet();

    MultiSet(int n, int k);

    MultiSet(const MultiSet& other);

    ~MultiSet();

    MultiSet& operator = (const MultiSet& other);

    MultiSet operator & (const MultiSet& other) const;

    MultiSet operator ~ () const;

    MultiSet operator - (const MultiSet& other) const;

    void addNumber(int number);

    int numberCount(int number) const;

    void customMemcpy(char* destination, const char* source, int count);

    void serialize(const char* fileName) const;

    void deserialize(const char* fileName);

    void printNumbers() const;

    void printAsBits() const;

};