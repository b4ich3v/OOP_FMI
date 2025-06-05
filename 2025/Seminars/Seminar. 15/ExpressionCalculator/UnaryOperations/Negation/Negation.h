#include "UnaryOperation.h"
#pragma once

class Negation: public UnaryOperation
{
public:

	Negation(Expression* expr);

	Expression* clone() const override;

	bool evaluate() const override;

};

