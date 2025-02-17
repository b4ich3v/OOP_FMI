#pragma once

#include "PartialFunction.h"
#include "CriteriaResult.h"

// Template class for a partial function defined by a criteria
template <typename Func>

class PartialFunctionByCriteria : public PartialFunction
{
private:

    Func func; // The criteria function

public:

    PartialFunctionByCriteria(const Func& f) : func(f) {} // Constructor

    bool isDefined(uint32_t x) const override
    {

        return func(x).isDefined; // Check if defined by the criteria function

    }

    uint32_t calculate(uint32_t x) const override
    {

        return func(x).result; // Calculate result by the criteria function

    }

};
