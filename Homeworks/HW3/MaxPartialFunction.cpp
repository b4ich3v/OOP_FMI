#include "MaxPartialFunction.h"

MaxPartialFunction::MaxPartialFunction(PartialFunction** funcs, int n)
    : CompositePartialFunction(funcs, n) {}

uint32_t MaxPartialFunction::calculate(uint32_t x) const
{

    if (isDefined(x))
    {

        uint32_t maxVal = functions[0]->calculate(x); // Start with the first function's result

        for (int i = 1; i < count; i++)
        {

            uint32_t val = functions[i]->calculate(x);

            if (val > maxVal)
            {

                maxVal = val; // Update maxVal if current function's result is greater

            }

        }

        return maxVal; // Return the maximum value

    }

    return 0; // Return 0 if not defined

}
