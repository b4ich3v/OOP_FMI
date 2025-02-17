#include "T2PartialFunction.h"

T2PartialFunction::T2PartialFunction(uint32_t* def, int s) : defined(def), size(s)
{

    if (s <= 0)
    {

        throw std::invalid_argument("Size must be greater than 0");

    }

}

bool T2PartialFunction::isDefined(uint32_t x) const
{

    return true; // Always defined

}

uint32_t T2PartialFunction::calculate(uint32_t x) const
{

    for (int i = 0; i < size; i++)
    {

        if (defined[i] == x)
        {

            return 1; // Return 1 if x is in the defined array

        }

    }

    return 0; // Return 0 if x is not found

}

T2PartialFunction::~T2PartialFunction()
{

    delete[] defined; // Clean up defined array

}
