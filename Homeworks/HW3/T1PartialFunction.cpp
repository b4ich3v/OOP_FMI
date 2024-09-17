#include "T1PartialFunction.h"

T1PartialFunction::T1PartialFunction(uint32_t* ex, int s) : excluded(ex), size(s)
{

    if (s <= 0)
    {

        throw std::invalid_argument("Size must be greater than 0");

    }

}

bool T1PartialFunction::isDefined(uint32_t x) const
{

    for (int i = 0; i < size; i++)
    {

        if (excluded[i] == x)
        {

            return false; // Return false if x is in the excluded array

        }

    }

    return true; // Return true if x is not excluded

}

uint32_t T1PartialFunction::calculate(uint32_t x) const
{

    if (isDefined(x))
    {

        return x; // Return x if it is defined

    }

    return 0; // Return 0 if it is not defined

}

T1PartialFunction::~T1PartialFunction()
{

    delete[] excluded; // Clean up excluded array

}
