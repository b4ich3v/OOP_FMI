#include "UnaryOperation.h"

UnaryOperation::UnaryOperation(Expression* expr, const MyString& oper):
	expr(expr), oper(oper) {}
