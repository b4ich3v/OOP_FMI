#pragma once

#include "CompositePartialFunction.h"

class MinPartialFunction : public CompositePartialFunction
{
public:

    MinPartialFunction(PartialFunction** funcs, int n);
    uint32_t calculate(uint32_t x) const override;

};
