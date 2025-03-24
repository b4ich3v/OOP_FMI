#include <iostream>
#include <stdexcept>
#include <climits>

namespace HELPERS 
{
    
    int powerOfTwo(int number) 
    {

        return number * number;

    }

    int customFunction1(int number)
    {

        return number * 2 + 1;

    }

    int customFunction2(int number)
    {

        return number % 5 + 1;

    }

}

typedef int (*predicate)(int);

class NumberSeries 
{
private:

    int first = 0;          
    predicate function = nullptr; 
    int* hashTable = nullptr;        
    int countedIndexes = 0;         
    int capacity = 0;       

    void setCashedValues() 
    {

        capacity = 8;             
        hashTable = new int[capacity];
        hashTable[0] = first;        
        countedIndexes = 1;

    }

    void resize(int newCapacity) 
    {

        if (newCapacity <= capacity) return;

        int* newHashTable = new int[newCapacity];

        for (int i = 0; i < countedIndexes; i++) 
        {

            newHashTable[i] = hashTable[i];

        }

        delete[] hashTable;
        hashTable = newHashTable;
        capacity = newCapacity;

    }

    void generateUpTo(int index) 
    {

        if (index < 0) throw std::logic_error("Error");
            
        while (countedIndexes <= index) 
        {

            if (countedIndexes == capacity) resize(capacity * 2);
            
            hashTable[countedIndexes] = function(hashTable[countedIndexes - 1]);
            countedIndexes += 1;

        }

    }

    void copyFrom(const NumberSeries& other) 
    {

        first = other.first;
        function = other.function;
        countedIndexes = other.countedIndexes;
        capacity = other.capacity;

        hashTable = new int[capacity];

        for (int i = 0; i < countedIndexes; i++)
        {

            hashTable[i] = other.hashTable[i];

        }

    }

    void free()
    {

        delete[] hashTable;
        hashTable = nullptr;
        function = nullptr;
        countedIndexes = 0;
        capacity = 0;

    }

public:
    
    NumberSeries(int first, predicate function)
        : first(first), function(function), hashTable(nullptr), countedIndexes(0), capacity(0) 
    {

        if (!function) throw std::invalid_argument("Error");
        setCashedValues();

    }

    NumberSeries() : NumberSeries(0, HELPERS::powerOfTwo) {}

    NumberSeries(const NumberSeries& other)
    {

        copyFrom(other);

    }

    NumberSeries& operator = (const NumberSeries& other) 
    {

        if (this != &other) 
        {

            free();
            copyFrom(other);

        }

        return *this;

    }

    ~NumberSeries() 
    {
       
        free();

    }

    int getNumber(int index) 
    {

        generateUpTo(index);
        return hashTable[index];

    }

    bool contains(int value)
    {
        
        for (int i = 0; i < countedIndexes; i++) 
        {

            if (hashTable[i] == value)  return true;
               
        }
 
        while (hashTable[countedIndexes - 1] < value)
        {
            generateUpTo(countedIndexes);

            if (hashTable[countedIndexes - 1] == value) return true;
                
        }

        return false;

    }

    void setSeriesByFirstTerm(int newFirst) 
    {

        free();
        first = newFirst;
        setCashedValues();

    }

    void setSeriresByFunction(predicate newFunction) 
    {

        if (!newFunction)  throw std::invalid_argument("Error");
           
        free();
        function = newFunction;
        setCashedValues();

    }

};

void testingPrint(NumberSeries& ns)
{

    for (int i = 0; i < 10; i++)
    {

        std::cout << "a[" << i << "] = " << ns.getNumber(i) << std::endl;

    }

    std::cout << std::endl;

}

int main() 
{

    NumberSeries ns(0, HELPERS::customFunction1);
    testingPrint(ns);

    ns.setSeriresByFunction(HELPERS::customFunction2);
    testingPrint(ns);

    ns.setSeriesByFirstTerm(7);
    ns.setSeriresByFunction(HELPERS::customFunction1);
    testingPrint(ns);

    std::cout << ns.contains(15) << std::endl;
    std::cout << ns.contains(16) << std::endl;

    return 0;

}
