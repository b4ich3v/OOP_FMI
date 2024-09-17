#include "T0PartialFunction.h"

T0PartialFunction::T0PartialFunction(uint32_t* a, uint32_t* r, int s) : args(a), results(r), size(s)
{

    if (s <= 0)
    {

        throw std::invalid_argument("Size must be greater than 0");

    }
    if (a == nullptr || r == nullptr)
    {

        throw std::invalid_argument("Arguments and results arrays cannot be null");

    }

}

bool T0PartialFunction::isDefined(uint32_t x) const
{

    for (int i = 0; i < size; i++)
    {

        if (args[i] == x)
        {

            return true; // Return true if x is in the args array

        }

    }

    return false; // Return false if x is not found

}

uint32_t T0PartialFunction::calculate(uint32_t x) const
{

    for (int i = 0; i < size; i++)
    {

        if (args[i] == x)
        {

            return results[i]; // Return the corresponding result

        }

    }

    return 0; // Return 0 if x is not found

}

T0PartialFunction::~T0PartialFunction()
{

    delete[] args; // Clean up args array
    delete[] results; // Clean up results array

}
