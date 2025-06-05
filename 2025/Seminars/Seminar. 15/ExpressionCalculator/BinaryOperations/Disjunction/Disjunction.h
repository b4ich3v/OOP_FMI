#include "BinaryOperation.h"
#pragma once

class Disjunction: public BinaryOperation
{
public:

	Disjunction(Expression* left, Expression* right);

	Expression* clone() const override;

	bool evaluate() const override;

};
