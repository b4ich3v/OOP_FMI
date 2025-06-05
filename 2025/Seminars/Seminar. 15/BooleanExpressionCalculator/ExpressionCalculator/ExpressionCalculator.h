#include "Variable.h"
#include "Constant.h"
#include "Conjunction.h"
#include "Disjunction.h"
#include "Negation.h"
#include "MyString.h"
#pragma once

class ExpressionCalculator
{
private:

	Expression* root = nullptr;

	void free();

	void copyFrom(const ExpressionCalculator& other);

	void moveTo(ExpressionCalculator&& other);

	void parseExpr(const MyString& expr);

	Expression* parseExprRecursive(const MyString& expr, size_t& position);

public:

	ExpressionCalculator(const MyString& expr);

	ExpressionCalculator(const ExpressionCalculator& other);

	ExpressionCalculator(ExpressionCalculator&& other) noexcept;

	ExpressionCalculator& operator = (const ExpressionCalculator& other);

	ExpressionCalculator& operator = (ExpressionCalculator&& other) noexcept;

	~ExpressionCalculator();

	bool evaluate() const;

	void clear();

	void setNewExpr(const MyString& expr);

};
