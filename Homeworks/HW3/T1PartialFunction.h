#pragma once

#include "PartialFunction.h"
#include <stdexcept>

class T1PartialFunction : public PartialFunction
{
private:

    uint32_t* excluded; // Array of excluded values
    int size; // Size of the array

public:

    T1PartialFunction(uint32_t* ex, int s);
    bool isDefined(uint32_t x) const override;
    uint32_t calculate(uint32_t x) const override;
    ~T1PartialFunction();

};
