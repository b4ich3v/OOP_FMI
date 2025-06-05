#include "Negation.h"

Negation::Negation(Expression* expr):
	UnaryOperation(expr, "!") {}

Expression* Negation::clone() const 
{

	return new Negation(*this);

}

bool Negation::evaluate() const 
{

	return !expr->evaluate();

}
