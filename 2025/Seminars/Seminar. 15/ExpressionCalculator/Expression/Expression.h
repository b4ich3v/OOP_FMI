#pragma once

class Expression
{
public:

	virtual bool evaluate() const = 0;

	virtual Expression* clone() const = 0;

	virtual ~Expression() = default;

};

