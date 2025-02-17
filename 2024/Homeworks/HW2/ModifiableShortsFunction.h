#pragma once

using FunctionPointer = short(*)(short);

const short SHORT_MIN = -32768;

class ModifiableShortsFunction
{
private:

    FunctionPointer function;
    short* specialResults;
    bool* hasSpecialResult;
    bool* isExcluded;
    int range;
    int offset;

    int index(short x) const;

    bool isPointExcluded(short x) const;

    void swap(ModifiableShortsFunction& other);


public:

    ModifiableShortsFunction(FunctionPointer f, int maxRange);

    ~ModifiableShortsFunction();

    ModifiableShortsFunction(const ModifiableShortsFunction& other);

    ModifiableShortsFunction& operator = (ModifiableShortsFunction other);

    ModifiableShortsFunction operator + (const ModifiableShortsFunction& other) const;

    ModifiableShortsFunction operator - (const ModifiableShortsFunction& other) const;

    ModifiableShortsFunction operator * (const ModifiableShortsFunction& other) const;

    ModifiableShortsFunction operator ^ (int k) const;

    ModifiableShortsFunction generateInverse() const;

    bool operator < (const ModifiableShortsFunction& other) const;

    bool operator == (const ModifiableShortsFunction& other) const;

    bool operator > (const ModifiableShortsFunction& other) const;

    bool operator <= (const ModifiableShortsFunction& other) const;

    bool operator >= (const ModifiableShortsFunction& other) const;

    short operator () (short x) const;

    short callFunction(short x) const;

    void setSpecialResult(short x, short result);

    void excludePoint(short x);

    void serialize(const char* fileName) const;

    void deserialize(const char* fileName);

    bool isInjection() const;

    bool isSurjection() const;

    bool isBijection() const;

    bool areFunctionsParallel(const ModifiableShortsFunction& other) const;

    void visualizeFunction(int startX, int endX, int startY, int endY) const;

};
