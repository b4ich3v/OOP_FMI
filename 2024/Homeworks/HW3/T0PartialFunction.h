#pragma once

#include "PartialFunction.h"
#include <stdexcept>

class T0PartialFunction : public PartialFunction
{
private:

    uint32_t* args; // Array of arguments
    uint32_t* results; // Array of results
    int size; // Size of the arrays

public:

    T0PartialFunction(uint32_t* a, uint32_t* r, int s);
    bool isDefined(uint32_t x) const override;
    uint32_t calculate(uint32_t x) const override;
    ~T0PartialFunction();

};
