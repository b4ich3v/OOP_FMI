#include "Variable.h"

Variable::Variable(const MyString& name, bool value):
	name(name), value(value) {}

bool Variable::evaluate() const 
{

	return value;

}

Expression* Variable::clone() const 
{

	return new Variable(*this);

}

void Variable::setVariable(bool value) 
{

	this->value = value;

}
