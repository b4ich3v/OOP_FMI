#include "BinaryOperation.h"
#pragma once

class Conjunction: public BinaryOperation
{
public:

	Conjunction(Expression* left, Expression* right);

	Expression* clone() const override;

	bool evaluate() const override;

};


