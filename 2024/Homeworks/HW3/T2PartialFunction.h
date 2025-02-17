#pragma once

#include "PartialFunction.h"
#include <stdexcept>

class T2PartialFunction : public PartialFunction
{
private:

    uint32_t* defined; // Array of defined values
    int size; // Size of the array

public:

    T2PartialFunction(uint32_t* def, int s);
    bool isDefined(uint32_t x) const override;
    uint32_t calculate(uint32_t x) const override;
    ~T2PartialFunction();

};
