#pragma once

#include "PartialFunction.h"
#include <stdexcept>

class CompositePartialFunction : public PartialFunction
{
protected:

    PartialFunction** functions; // Array of partial functions
    int count; // Number of functions

    CompositePartialFunction(PartialFunction** funcs, int n);
    virtual ~CompositePartialFunction(); // Virtual destructor for proper cleanup

public:

    bool isDefined(uint32_t x) const override;

};
