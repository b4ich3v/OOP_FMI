#include "MinPartialFunction.h"

MinPartialFunction::MinPartialFunction(PartialFunction** funcs, int n)
    : CompositePartialFunction(funcs, n) {}

uint32_t MinPartialFunction::calculate(uint32_t x) const
{

    if (isDefined(x))
    {

        uint32_t minVal = functions[0]->calculate(x); // Start with the first function's result

        for (int i = 1; i < count; i++)
        {

            uint32_t val = functions[i]->calculate(x);

            if (val < minVal)
            {

                minVal = val; // Update minVal if current function's result is smaller

            }

        }

        return minVal; // Return the minimum value

    }

    return 0; // Return 0 if not defined

}
