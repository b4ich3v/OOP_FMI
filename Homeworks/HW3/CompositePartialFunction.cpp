#include "CompositePartialFunction.h"

CompositePartialFunction::CompositePartialFunction(PartialFunction** funcs, int n)
    : functions(funcs), count(n)
{

    if (n <= 0)
    {

        throw std::invalid_argument("Count must be greater than 0"); // Validate count

    }

}

CompositePartialFunction::~CompositePartialFunction()
{

    for (int i = 0; i < count; i++)
    {

        delete functions[i]; // Clean up all functions

    }
    delete[] functions;

}

bool CompositePartialFunction::isDefined(uint32_t x) const
{

    for (int i = 0; i < count; i++)
    {

        if (!functions[i]->isDefined(x))
        {

            return false; // Return false if any function is not defined for x

        }

    }

    return true; // All functions are defined for x

}
