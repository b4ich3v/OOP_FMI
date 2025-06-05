#include "Expression.h"
#include "MyString.h"
#pragma once

class UnaryOperation: public Expression
{
protected:

	Expression* expr = nullptr;
	MyString oper;

public:

	UnaryOperation(Expression* expr, const MyString& oper);

};



