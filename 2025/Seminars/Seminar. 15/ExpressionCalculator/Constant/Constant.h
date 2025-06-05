#include "Expression.h"
#pragma once

class Constant: public Expression
{
private:

	const bool value = false;

public:

	Constant(const bool value);

	Expression* clone() const override;

	bool evaluate() const override;

};

