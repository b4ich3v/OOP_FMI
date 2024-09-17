#pragma once

#include <cstdint>

// Abstract base class representing a partial function
class PartialFunction
{
public:

    virtual bool isDefined(uint32_t x) const = 0; // Check if the function is defined for a given x
    virtual uint32_t calculate(uint32_t x) const = 0; // Calculate the result of the function for a given x
    virtual ~PartialFunction() = default; // Virtual destructor for proper cleanup

};
