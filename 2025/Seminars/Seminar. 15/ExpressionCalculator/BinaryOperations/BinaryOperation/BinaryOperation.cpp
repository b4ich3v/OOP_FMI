#include "BinaryOperation.h"

BinaryOperation::BinaryOperation(Expression* left, Expression* right, const MyString& oper):
	left(left), right(right), oper(oper) {}
