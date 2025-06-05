#include "Constant.h"

Constant::Constant(const bool value):
	value(value) {}

Expression* Constant::clone() const 
{

	return new Constant(*this);

}

bool Constant::evaluate() const 
{

	return value;

}
