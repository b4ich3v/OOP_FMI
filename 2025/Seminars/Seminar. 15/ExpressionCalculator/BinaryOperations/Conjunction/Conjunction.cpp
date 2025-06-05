#include "Conjunction.h"

Conjunction::Conjunction(Expression* left, Expression* right):
	BinaryOperation(left, right, "&") {}

Expression* Conjunction::clone() const
{

	return new Conjunction(*this);

}

bool Conjunction::evaluate() const 
{

	return left->evaluate() && right->evaluate();

}
