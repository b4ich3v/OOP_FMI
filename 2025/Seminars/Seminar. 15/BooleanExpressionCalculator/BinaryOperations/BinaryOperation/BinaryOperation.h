#include "Expression.h"
#include "MyString.h"
#pragma once

class BinaryOperation: public Expression
{
protected:

	Expression* left = nullptr;
	MyString oper;
	Expression* right = nullptr;

public:

	BinaryOperation(Expression* left, Expression* right, const MyString& oper);

};

