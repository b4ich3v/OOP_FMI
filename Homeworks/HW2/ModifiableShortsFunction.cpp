#include "ModifiableShortsFunction.h"
#include <iostream>
#include <fstream>
#include <exception>

int ModifiableShortsFunction:: index(short x) const
{

    int indexToReturn = x + offset; // Calculate internal index using offset

    if (indexToReturn < 0 || indexToReturn >= range) // Validation
    {

        throw std::out_of_range("Index out of range for provided input");

    }

    return indexToReturn;

}

bool ModifiableShortsFunction ::isPointExcluded(short x) const
{

    return isExcluded[index(x)]; // Check if the point is marked as excluded

}

void ModifiableShortsFunction:: swap(ModifiableShortsFunction& other) noexcept
{

    // Swap the function pointers. This changes the function associated with each instance
    FunctionPointer tempFunction = function; 
    function = other.function;
    other.function = tempFunction;

    // Swap pointers to special results. This transfers control of dynamically allocated memory for special results
    short* tempSpecialResults = specialResults;  
    specialResults = other.specialResults;
    other.specialResults = tempSpecialResults;

    // Swap the arrays indicating whether each index is excluded from the function calculation
    bool* tempHasSpecialResult = hasSpecialResult;
    hasSpecialResult = other.hasSpecialResult;
    other.hasSpecialResult = tempHasSpecialResult;

    // Swap the arrays indicating whether each index is excluded from the function calculation
    bool* tempIsExcluded = isExcluded;
    isExcluded = other.isExcluded;
    other.isExcluded = tempIsExcluded;

    // Swap the range values. This affects the calculation of indices and the valid range of input values
    int tempRange = range;
    range = other.range;
    other.range = tempRange;

    // Swap the offset values. Offsets are used to adjust input values to a zero-based index for internal storage
    int tempOffset = offset;
    offset = other.offset;
    other.offset = tempOffset;

}

ModifiableShortsFunction::ModifiableShortsFunction(FunctionPointer f, int maxRange)
    :function(f), range(maxRange), offset(range / 2)
{

    if (f == nullptr) // Validation
    {

        throw std::invalid_argument("Function pointer cannot be null.");

    }

    if (maxRange <= 0) // Validation
    {

        throw std::invalid_argument("Range is out of valid bounds");

    }

    specialResults = new short[range]();
    hasSpecialResult = new bool[range]();
    isExcluded = new bool[range]();

}

ModifiableShortsFunction::~ModifiableShortsFunction()
{

    delete[] specialResults;
    delete[] hasSpecialResult;
    delete[] isExcluded;

}

ModifiableShortsFunction::ModifiableShortsFunction(const ModifiableShortsFunction& other)
    : function(other.function), range(other.range), offset(other.offset)
{

    specialResults = new short[range];
    hasSpecialResult = new bool[range];
    isExcluded = new bool[range];

    for (int i = 0; i < range; i++)
    {

        specialResults[i] = other.specialResults[i];
        hasSpecialResult[i] = other.hasSpecialResult[i];
        isExcluded[i] = other.isExcluded[i];

    }

}

ModifiableShortsFunction& ModifiableShortsFunction:: operator = (ModifiableShortsFunction other)
{

    this->swap(other);
    return *this;

}

ModifiableShortsFunction ModifiableShortsFunction ::operator + (const ModifiableShortsFunction& other) const
{

    if (range != other.range) // Validation
    {

        throw std::invalid_argument("Function ranges do not match");

    }

    ModifiableShortsFunction result(function, range);

    for (int i = -offset; i < range - offset; i++)
    {

        short indexI = index(i);

        if (isExcluded[indexI] || other.isExcluded[indexI]) // If either function has this point excluded, exclude it in the result as well
        {

            result.excludePoint(i);

        }
        else
        {

            // Use special results directly if available, otherwise calculate it
            short value1 = hasSpecialResult[indexI] ? specialResults[indexI] : callFunction(i);
            short value2 = other.hasSpecialResult[indexI] ? other.specialResults[indexI] : other.callFunction(i);
            result.setSpecialResult(i, value1 + value2); // Set the result of adding the two function values at this index

        }

    }

    return result;

}

ModifiableShortsFunction ModifiableShortsFunction ::operator - (const ModifiableShortsFunction& other) const
{

    if (range != other.range) // Validation
    {

        throw std::invalid_argument("Function ranges do not match");

    }

    ModifiableShortsFunction result(function, range);

    for (int i = -offset; i < range - offset; i++)
    {

        short indexI = index(i);


        if (isExcluded[indexI] || other.isExcluded[indexI]) // Exclude the point from the result if it's excluded in either function
        {

            result.excludePoint(i);

        }
        else
        {

            // Compute the difference using special results if available, otherwise calculate it
            short value1 = hasSpecialResult[indexI] ? specialResults[indexI] : callFunction(i);
            short value2 = other.hasSpecialResult[indexI] ? other.specialResults[indexI] : other.callFunction(i);
            result.setSpecialResult(i, value1 - value2); // Set the result of subtracting the other function value from this function value at this index

        }

    }

    return result;

}

ModifiableShortsFunction ModifiableShortsFunction ::operator * (const ModifiableShortsFunction& other) const
{

    if (range != other.range) // Validation
    {

        throw std::invalid_argument("Function ranges do not match");

    }

    ModifiableShortsFunction result(function, range);

    for (short i = -offset; i < range - offset; i++)
    {

        try
        {

            short resultI = other(callFunction(i)); // Attempt to call the other function with the result of this function as input
            result.setSpecialResult(i, resultI); // If successful, set the special result at this index to the result of the composition

        }
        catch (const std::exception&)
        {

            result.excludePoint(i); // Exclude the index if any exception occurs during the function call

        }

    }

    return result;

}

ModifiableShortsFunction ModifiableShortsFunction :: operator ^ (int k) const
{

    ModifiableShortsFunction toReturn = *this; // Start with a copy of this function

    if (k < 0) // Validation
    {

        throw std::invalid_argument("The repetition count cannot be negative");

    }

    for (short i = -offset; i < range - offset; i++)
    {

        if (!isExcluded[index(i)]) // Only apply iteration to non-excluded points
        {

            try
            {

                short repeatedResult = i;

                for (int repeat = 0; repeat < k; repeat++)
                {

                    repeatedResult = toReturn(repeatedResult); // Apply the function iteratively

                }

                toReturn.setSpecialResult(i, repeatedResult); // Store the final result as a special result

            }
            catch (const std::exception&)
            {

                toReturn.excludePoint(i);  // Exclude the point if any error occurs during the iterations

            }

        }

    }

    return toReturn;

}

ModifiableShortsFunction ModifiableShortsFunction::generateInverse() const
{

    if (!isInjection()) // Check Injectivity
    {

        throw std::logic_error("Cannot generate inverse of a function that is not an injection");

    }

    // Allocates memory for storing results, presence flags, and exclusion flags for the inverse function
    short* inverseSpecialResults = new short[range];
    bool* inverseHasSpecialResult = new bool[range]();
    bool* inverseIsExcluded = new bool[range];

    try
    {

        for (int i = 0; i < range; i++)
        {

            inverseIsExcluded[i] = isExcluded[i];

        }

        // Iterates over the function's domain, computes results, and assigns the inverse mappings if the computed results are within the valid range and not excluded
        for (short i = -offset; i < range - offset; i++) 
        {

            if (!isPointExcluded(i))
            {

                short result = callFunction(i);

                if (result >= -offset && result < range - offset)
                {

                    int resultIndex = index(result);
                    inverseSpecialResults[resultIndex] = i;
                    inverseHasSpecialResult[resultIndex] = true;

                }

            }

        }

        ModifiableShortsFunction inverseFunction(this->function, range);

        delete[] inverseFunction.specialResults;
        delete[] inverseFunction.hasSpecialResult;
        delete[] inverseFunction.isExcluded;

        inverseFunction.specialResults = inverseSpecialResults;
        inverseFunction.hasSpecialResult = inverseHasSpecialResult;
        inverseFunction.isExcluded = inverseIsExcluded;

        return inverseFunction;

    }
    catch (...) // Catches exceptions, cleans up allocated memory, and rethrows the exception to ensure no memory leak on failure
    {

        delete[] inverseSpecialResults;
        delete[] inverseHasSpecialResult;
        delete[] inverseIsExcluded;

        throw;

    }

}

bool ModifiableShortsFunction::operator < (const ModifiableShortsFunction& other) const
{

    for (short i = -offset; i < range - offset; i++)
    {

        int indexI = index(i);

        // If this point is excluded and the other is not, this function is less
        if (isExcluded[indexI] && !other.isExcluded[indexI]) return true;

        // If this point is not excluded but the other is, this function is not less
        if (!isExcluded[indexI] && other.isExcluded[indexI]) return false;

        // Continue to next iteration if both points are excluded
        if (isExcluded[indexI] && other.isExcluded[indexI]) continue;

        // Compare function results if both points are included
        short thisValue = hasSpecialResult[indexI] ? specialResults[indexI] : callFunction(i);
        short otherValue = other.hasSpecialResult[indexI] ? other.specialResults[indexI] : other.callFunction(i);

        // Return true if this function's result is less than the other's at any point
        if (thisValue < otherValue) return true;
        if (thisValue > otherValue) return false;

    }

    // If all values are equal, compare the ranges and return true if this range is smaller
    return range < other.range;

}

bool ModifiableShortsFunction::operator == (const ModifiableShortsFunction& other) const
{

    // Return false immediately if the ranges are different
    if (range != other.range) return false;

    for (short i = -offset; i < range - offset; i++)
    {

        int indexI = index(i);

        // Return false if the exclusion status differs for any point
        if (isExcluded[indexI] != other.isExcluded[indexI]) return false;

        // Skip comparison for points excluded in both functions
        if (isExcluded[indexI] && other.isExcluded[indexI]) continue;

        // Compare values directly if points are not excluded
        short thisValue = hasSpecialResult[indexI] ? specialResults[indexI] : callFunction(i);
        short otherValue = other.hasSpecialResult[indexI] ? other.specialResults[indexI] : other.callFunction(i);

        // Return false if any corresponding values differ
        if (thisValue != otherValue) return false;

    }

    // Return true if all checks pass, indicating equality
    return true;

}

bool ModifiableShortsFunction::operator > (const ModifiableShortsFunction& other) const
{

    return other < *this;

}

bool ModifiableShortsFunction::operator <= (const ModifiableShortsFunction& other) const
{

    return !(other < *this);

}

bool ModifiableShortsFunction::operator >= (const ModifiableShortsFunction& other) const
{

    return !(*this < other);

}

short ModifiableShortsFunction::operator () (short x) const
{

    // Check if the input value x is within the valid range, adjusted by the offset
    if (x < -offset || x >= range - offset)
    {

        throw std::out_of_range("Index out of range");

    }

    // Call the internal function with the validated input and return its result
    return callFunction(x);

}

short ModifiableShortsFunction::callFunction(short x) const
{

    // Check if the input value x is within the valid range adjusted by the offset
    if (x < -offset || x >= range - offset)
    {

        throw std::out_of_range("callFunction input is out of range");

    }

    if (isExcluded[index(x)])
    {

        throw std::runtime_error("Error: Function call is excluded for this input");

    }
    else if (hasSpecialResult[index(x)]) // Return the special result if one is set for this index
    {

        return specialResults[index(x)];

    }
    else
    {

        return function(x); // Otherwise, call the stored function pointer with the input x

    }

}

void ModifiableShortsFunction::setSpecialResult(short x, short result)
{

    int indexX = index(x);

    // Ensure the index is within the bounds of the arrays
    if (indexX < 0 || indexX >= range)
    {

        throw std::out_of_range("Index out of range");

    }

    hasSpecialResult[indexX] = true; // Mark this index as having a special result
    specialResults[indexX] = result; // Store the special result for this index

}

void ModifiableShortsFunction::excludePoint(short x)
{

    int indexX = index(x);

    if (indexX < 0 || indexX >= range) // Ensure the index is within the bounds of the arrays
    {

        throw std::out_of_range("Index out of range");

    }

    isExcluded[indexX] = true; // Mark this index as excluded, so the function will not process this input

}

void ModifiableShortsFunction::serialize(const char* fileName) const
{

    std::ofstream file(fileName, std::ios::binary);

    if (!file) // Validation
    {

        throw std::runtime_error("Cannot open file for writing");

    }

    file.write((const char*)(&range), sizeof(range));

    for (int i = 0; i < range; i++) // Iterate over each index in the range to write the function's state
    {
        file.write((const char*)(&specialResults[i]), sizeof(specialResults[i])); // Write the special result value at this index

        unsigned char hasSpecRes = hasSpecialResult[i] ? 1 : 0; // Convert the boolean hasSpecialResult to an unsigned char and write it
        file.write((const char*)(&hasSpecRes), sizeof(hasSpecRes));

        unsigned char isExcl = isExcluded[i] ? 1 : 0; // Convert the boolean isExcluded to an unsigned char and write it
        file.write((const char*)(&isExcl), sizeof(isExcl));

    }

    file.close();

}

void ModifiableShortsFunction::deserialize(const char* fileName)
{

    std::ifstream file(fileName, std::ios::binary);

    if (!file) // Validation
    {

        throw std::runtime_error("Cannot open file for reading");

    }

    int newRange;

    file.read((char*)(&newRange), sizeof(newRange));

    if (!file.good())
    {

        throw std::runtime_error("Error reading range from file");

    }

    // Allocate new arrays for special results, presence flags, and exclusion flags based on newRange
    short* newSpecialResults = new short[newRange];
    bool* newHasSpecialResult = new bool[newRange];
    bool* newIsExcluded = new bool[newRange];

    // Read the data for each element in the range
    for (int i = 0; i < newRange; i++)
    {

        file.read((char*)&newSpecialResults[i], sizeof(short));

        unsigned char hasSpecRes;
        file.read((char*)&hasSpecRes, sizeof(hasSpecRes));
        newHasSpecialResult[i] = hasSpecRes != 0;

        unsigned char isExcl;
        file.read((char*)&isExcl, sizeof(isExcl));
        newIsExcluded[i] = isExcl != 0;

    }

    // Check again if there were any read errors after processing all data
    if (!file.good())
    {

        delete[] newSpecialResults;
        delete[] newHasSpecialResult;
        delete[] newIsExcluded;

        throw std::runtime_error("Error reading data from file");

    }

    // Replace old data with new data
    delete[] specialResults;
    delete[] hasSpecialResult;
    delete[] isExcluded;

    specialResults = newSpecialResults;
    hasSpecialResult = newHasSpecialResult;
    isExcluded = newIsExcluded;
    range = newRange;
    offset = range / 2; // Recalculate the offset based on the new range

    file.close();

}

bool ModifiableShortsFunction::isInjection() const
{

    short* values = new short[range]; // Allocate an array to track which results have been seen

    for (int i = 0; i < range; i++) // Initialize the array with a value that indicates "unseen"
    {

        values[i] = SHORT_MIN;

    }

    bool isInjective = true;

    for (short i = -offset; i < range - offset; i++) // Check each input within the range, adjusted by offset
    {

        if (!isPointExcluded(i)) // Only consider inputs that are not excluded
        {

            short result = callFunction(i);

            if (result >= -offset && result < range - offset) // Ensure the result is within the expected range
            {

                if (values[index(result)] != SHORT_MIN) // Check if the result has already been mapped by another input
                {

                    isInjective = false; // If yes, the function is not injective
                    break;

                }

                values[index(result)] = i; // Mark this result as seen by assigning the current input

            }

        }

    }

    delete[] values; // Clean up the allocated array
    return isInjective; // Return true if the function is injective, false otherwise

}

bool ModifiableShortsFunction::isSurjection() const
{

    bool* seen = new bool[range]; // Create an array to track which outputs have been achieved from the function

    for (int i = 0; i < range; i++)  // Initialize all outputs as not seen
    {

        seen[i] = false;

    }

    for (short i = -offset; i < range - offset; i++) // Iterate over all possible inputs within the valid range, adjusted by offset
    {

        if (!isPointExcluded(i)) // Process only the inputs that are not excluded
        {

            short result = callFunction(i);

            if (result >= -offset && result < range - offset) // Check if the result is within the valid output range
            {

                seen[index(result)] = true; // Mark the output as seen

            }

        }

    }

    bool isSurjective = true;

    for (int i = 0; i < range; i++) // Verify if all possible outputs have been seen
    {

        if (!seen[i])
        {

            isSurjective = false; // If any output has not been seen, the function is not surjective
            break;

        }

    }

    delete[] seen; // Clean up the allocated memory
    return isSurjective; // Return true if every possible output has been achieved, otherwise return false

}

bool ModifiableShortsFunction::isBijection() const
{

    return isInjection() && isSurjection();

}

bool ModifiableShortsFunction::areFunctionsParallel(const ModifiableShortsFunction& other) const
{

    if (range != other.range) // Validation
    {

        throw std::invalid_argument("Function ranges do not match");

    }

    int initialDifference = 0;
    bool hasInitialDifference = false;

    for (short i = -offset; i < range - offset; i++) // Iterate over all possible inputs within the range, adjusted by offset
    {

        int indexI = index(i);

        if (isExcluded[indexI] || other.isExcluded[indexI]) // Skip comparison for points that are excluded in either function
        {

            continue;

        }

        // Retrieve values from both functions, either special results or calculated values
        short thisValue = hasSpecialResult[indexI] ? specialResults[indexI] : callFunction(i);
        short otherValue = other.hasSpecialResult[indexI] ? other.specialResults[indexI] : other.callFunction(i);

        if (!hasInitialDifference) // Initialize the initial difference if it has not been set yet
        {

            initialDifference = thisValue - otherValue;
            hasInitialDifference = true;

        }
        else if (thisValue - otherValue != initialDifference) // Check if the constant difference holds
        {

            return false;

        }

    }

    return hasInitialDifference; // Return true if a consistent difference exists, indicating the functions are parallel

}

void ModifiableShortsFunction::visualizeFunction(int startX, int endX, int startY, int endY) const
{

    if (startX < -offset || endX >= range - offset || startY < -offset || endY >= range - offset) // Validation
    {

        throw std::out_of_range("Visualization range is out of bounds");

    }

    const int sizeX = 21;
    const int sizeY = 21;
    char grid[sizeY][sizeX * 2 - 1];


    for (int i = 0; i < sizeY; i++) // Initialize grid with spaces
    {

        for (int j = 0; j < sizeX * 2 - 1; j++)
        {

            grid[i][j] = ' ';

        }

    }

    int yAxisPosition = -startX;
    int xAxisPosition = endY;

    if (startX <= 0 && endX >= 0) // Draw vertical axis if necessary
    {

        for (int i = 0; i < sizeY; i++)
        {

            grid[i][yAxisPosition * 2] = '|';

        }
    }
    if (startY <= 0 && endY >= 0) // Draw horizontal axis if necessary
    {

        for (int i = 0; i < sizeX * 2 - 1; i++)
        {

            grid[xAxisPosition][i] = (i % 2 == 0) ? '-' : ' ';

        }

    }

    if (startX <= 0 && endX >= 0 && startY <= 0 && endY >= 0) // Draw intersection point if axes intersect
    {

        grid[xAxisPosition][yAxisPosition * 2] = '+';

    }

    for (int x = startX; x <= endX; x++) // Plot function points
    {

        if (!isExcluded[x + offset])
        {

            short y = hasSpecialResult[x + offset] ? specialResults[x + offset] : function((short)(x));

            if (y >= startY && y <= endY)
            {

                int gridX = (x - startX) * 2;
                int gridY = endY - y;
                grid[gridY][gridX] = '*';

            }

        }

    }

    for (int i = 0; i < sizeY; i++) // Output grid
    {

        for (int j = 0; j < sizeX * 2 - 1; j++)
        {

            std::cout << grid[i][j];

        }

        std::cout << '\n';

    }

}