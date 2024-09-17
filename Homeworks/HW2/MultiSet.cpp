#include "MultiSet.h"
#include <iostream>
#include <fstream>
#include <exception>

int MultiSet::getArrayIndex(int number) const
{

    if (number < 0 || number >= limit) // Validation
    {

        throw std::out_of_range("Number is out of range");

    }

    return (number * bitsForNumber) / 8;

}

int MultiSet::getBitPosition(int number) const
{

    if (number < 0 || number >= limit) // Validation
    {

        throw std::out_of_range("Number is out of range");

    }

    return (number * bitsForNumber) % 8;

}

void MultiSet::setCount(int number, int count)
{

    if (number < 0 || number >= limit) // Check if number is within range
    {

        throw std::out_of_range("Number is out of range");

    }

    if (count < 0 || count >= (1 << bitsForNumber)) // Check if count exceeds capacity of bits per number
    {

        throw std::out_of_range("Count exceeds the capacity of the specified bits per number");

    }

    int byteIndex = getArrayIndex(number);
    int bitPosition = getBitPosition(number);

    unsigned char mask = ((1 << bitsForNumber) - 1) << bitPosition; // Create mask to isolate bits for the specified number

    // Update the count for the specified number in the data array
    data[byteIndex] &= ~mask;
    data[byteIndex] |= (count << bitPosition) & mask;

    if (bitPosition + bitsForNumber > 8) // Handle overflow to the next byte
    {

        int nextByteIndex = byteIndex + 1;
        mask = ((1 << bitsForNumber) - 1) >> (8 - bitPosition); // Adjust mask for overflow
        data[nextByteIndex] &= ~mask; // Clear existing count bits
        data[nextByteIndex] |= (count >> (8 - bitPosition)) & mask; // Set new count bits in next byte

    }

}

int MultiSet::getCount(int number) const
{

    if (number < 0 || number >= limit) // Check if number is within range
    {

        throw std::out_of_range("Number is out of range");

    }

    int byteIndex = getArrayIndex(number);
    int bitPosition = getBitPosition(number);

    unsigned char mask = ((1 << bitsForNumber) - 1) << bitPosition; // Create mask to isolate bits for the specified number

    int count = (data[byteIndex] & mask) >> bitPosition; // Extract count for the specified number from the data array

    if (bitPosition + bitsForNumber > 8)  // Handle overflow from the next byte
    {

        int nextByteIndex = byteIndex + 1;
        mask = ((1 << bitsForNumber) - 1) >> (8 - bitPosition); // Adjust mask for overflow
        count |= (data[nextByteIndex] & mask) << (8 - bitPosition); // Add count from next byte

    }

    return count;

}

int MultiSet::min(int a, int b)
{

    return (a < b) ? a : b;

}

int MultiSet::max(int a, int b)
{

    return (a > b) ? a : b;

}

void MultiSet::swapForIntegers(int& a, int& b)
{

    int temp = a;
    a = b;
    b = temp;

}

void MultiSet::swapForStrings(char*& a, char*& b)
{

    char* temp = a;
    a = b;
    b = temp;

}

MultiSet::MultiSet() : limit(10), bitsForNumber(1)
{

    data = new char[(limit * bitsForNumber + 7) / 8]();

}

MultiSet::MultiSet(int n, int k) : limit(n), bitsForNumber(k)
{

    if (n <= 0 || k <= 0 || k > 8) // Validation
    {

        throw std::invalid_argument("Invalid parameters for MultiSet");

    }

    data = new char[(limit * bitsForNumber + 7) / 8]();

}

MultiSet::MultiSet(const MultiSet& other) : limit(other.limit), bitsForNumber(other.bitsForNumber)
{

    data = new char[(limit * bitsForNumber + 7) / 8];
    customMemcpy(data, other.data, (limit * bitsForNumber + 7) / 8);

}

MultiSet::~MultiSet()
{

    delete[] data;

}

MultiSet& MultiSet::operator = (const MultiSet& other)
{

    if (this != &other)
    {

        // Create a temporary copy of 'other'
        MultiSet temp(other);

        // Swap data and member variables with the temporary copy
        swapForStrings(data, temp.data);
        swapForIntegers(limit, temp.limit);
        swapForIntegers(bitsForNumber, temp.bitsForNumber);

    }

    return *this;

}

MultiSet MultiSet::operator & (const MultiSet& other) const
{

    // Determine the minimum size and bits for number between the two multisets
    // Create a result MultiSet with the minimum size and bits for number
    int minSize = min(limit, other.limit);
    MultiSet result(minSize, min(bitsForNumber, other.bitsForNumber));

    for (int i = 0; i < minSize; i++) // Iterate through each number in the multisets
    {

        // Get count for this MultiSet and the other MultiSet
        int thisCount = getCount(i);
        int otherCount = other.getCount(i);

        int minCount = min(thisCount, otherCount); // Determine the minimum count between the two multisets

        result.setCount(i, minCount);  // Set the count in the result MultiSet

    }

    return result;

}

MultiSet MultiSet::operator ~ () const
{

    // Create a result MultiSet with the same limit and bits for number
    MultiSet result(limit, bitsForNumber);

    // Calculate the maximum count based on the bits for number
    int maxCount = (1 << bitsForNumber) - 1;

    // Iterate through each number in the MultiSet
    for (int i = 0; i < limit; i++)
    {

        // Get count for this number
        int thisCount = getCount(i);

        // Calculate complement count
        int complementCount = maxCount - thisCount;

        // Set the complement count in the result MultiSet
        result.setCount(i, complementCount);

    }

    return result;

}

MultiSet MultiSet::operator - (const MultiSet& other) const
{

    // Create a result MultiSet with the same limit and bits for number
    MultiSet result(limit, bitsForNumber);

    // Iterate through each number in the MultiSet
    for (int i = 0; i < limit; i++)
    {

        // Get count for this number
        int thisCount = getCount(i);

        // Get count for the same number in the other MultiSet, or 0 if out of range
        int otherCount = i < other.limit ? other.getCount(i) : 0;

        // Calculate difference count, ensuring it's non-negative
        int diffCount = std::max(0, thisCount - otherCount);

        // Set the difference count in the result MultiSet
        result.setCount(i, diffCount);

    }

    return result;

}

void MultiSet::addNumber(int number)
{

    if (number < 0 || number >= limit) // Check if number is within range
    {

        throw std::out_of_range("Number is out of range");

    }

    int currentCount = getCount(number); // Get current count for the number

    if (currentCount < (1 << bitsForNumber) - 1) // Check if current count can be incremented without overflow
    {

        setCount(number, currentCount + 1);

    }
    else
    {

        throw std::runtime_error("Number count exceeds the maximum count that can be stored");

    }

}

int MultiSet::numberCount(int number) const
{

    if (number < 0 || number >= limit)
    {

        throw std::out_of_range("Number is out of range");

    }

    return getCount(number);

}

void MultiSet::customMemcpy(char* destination, const char* source, int count)
{

    while (count--) // Copy 'count' bytes from 'src' to 'dest'
    {

        *destination++ = *source++;

    }

}

void MultiSet::serialize(const char* fileName) const
{

    std::ofstream file(fileName, std::ios::binary);

    if (!file)
    {

        throw std::runtime_error("Cannot open file for writing");

    }

    try
    {

        // Write the limit and bitsForNumber to the file
        if (!file.write((const char*)&limit, sizeof(limit)) ||
            !file.write((const char*)&bitsForNumber, sizeof(bitsForNumber)) ||
            !file.write((const char*)data, (limit * bitsForNumber + 7) / 8))
        {

            throw std::runtime_error("Failed to write to file");

        }

    }
    catch (...)
    {

        // Close the file in case of an exception
        file.close();
        // Re-throw the caught exception
        throw;

    }

    file.close();

}

void MultiSet::deserialize(const char* fileName)
{

    std::ifstream file(fileName, std::ios::binary);

    if (!file)
    {

        throw std::runtime_error("Cannot open file for reading");

    }

    int newSize, newBitsPerNumber; // Declare variables to store metadata read from the file

    // Read size and bits per number metadata from the file
    if (!file.read((char*)&newSize, sizeof(newSize)) ||
        !file.read((char*)&newBitsPerNumber, sizeof(newBitsPerNumber)))
    {

        throw std::runtime_error("Failed to read metadata from file");

    }

    if (newSize <= 0 || newBitsPerNumber <= 0 || newBitsPerNumber > 8) // Check if metadata values are valid
    {

        throw std::runtime_error("File contains invalid metadata");

    }

    char* newData = new char[(newSize * newBitsPerNumber + 7) / 8]; // Allocate memory for the new data array based on the metadata

    if (!file.read((char*)newData, (newSize * newBitsPerNumber + 7) / 8)) // Read data from the file into the new data array
    {

        delete[] newData;
        throw std::runtime_error("Failed to load data from file");

    }

    delete[] data; // Deallocate memory for the current data array

    // Update limit, bits per number, and data pointer with new values
    limit = newSize;
    bitsForNumber = newBitsPerNumber;
    data = newData;

    file.close();

}

void MultiSet::printNumbers() const
{
     
    for (int i = 0; i < limit; i++) // Iterate through each number in the MultiSet
    {

        int count = getCount(i);  // Get count for the current number

        for (int j = 0; j < count; j++) // Print the current number 'count' times
        {

            std::cout << i << " ";

        }

    }

    std::cout << std::endl;

}

void MultiSet::printAsBits() const
{

    for (int i = 0; i < limit; i++) // Iterate through each number in the MultiSet
    {

        int count = getCount(i);  // Get count for the current number

        std::cout << "Number " << i << " is stored as " << count << " times (bits: ";

        for (int j = bitsForNumber - 1; j >= 0; j--) // Print the binary representation of the count
        {

            std::cout << ((count >> j) & 1);

        }

        std::cout << ")" << std::endl;

    }

}