#include "Disjunction.h"

Disjunction::Disjunction(Expression* left, Expression* right):
	BinaryOperation(left, right, "|") {}

Expression* Disjunction::clone() const
{

	return new Disjunction(*this);

}

bool Disjunction::evaluate() const
{

	return left->evaluate() || right->evaluate();

}
