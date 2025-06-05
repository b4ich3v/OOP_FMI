#include "MyString.h"
#include "Expression.h"
#pragma once

class Variable: public Expression
{
private:

	MyString name;
	bool value = false;

public:

	Variable() = default;

	Variable(const MyString& name, bool value);

	bool evaluate() const override;

	Expression* clone() const override;

	void setVariable(bool value = true);

};

