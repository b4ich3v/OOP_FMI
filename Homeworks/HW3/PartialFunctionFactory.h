#pragma once

#include "PartialFunction.h"

const int MAX_FILENAME_FUNCTION_LENGTH = 256;

class PartialFunctionFactory
{
public:

    static PartialFunction* createPartialFunction(const char* fileName);

};
