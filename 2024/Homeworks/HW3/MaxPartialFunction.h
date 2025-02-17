#pragma once

#include "CompositePartialFunction.h"

class MaxPartialFunction : public CompositePartialFunction
{
public:

    MaxPartialFunction(PartialFunction** funcs, int n);
    uint32_t calculate(uint32_t x) const override;

};
