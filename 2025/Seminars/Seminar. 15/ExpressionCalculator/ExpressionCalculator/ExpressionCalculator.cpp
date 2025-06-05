#include "ExpressionCalculator.h"

void ExpressionCalculator::free() 
{

	delete root;
	root = nullptr;

}

void ExpressionCalculator::copyFrom(const ExpressionCalculator& other) 
{

	root = other.root->clone();

}

void ExpressionCalculator::moveTo(ExpressionCalculator&& other) 
{

	root = other.root;
	other.root = nullptr;

}

void ExpressionCalculator::parseExpr(const MyString& expr) 
{

	size_t position = 0;
	root = parseExprRecursive(expr, position);

}

Expression* ExpressionCalculator::parseExprRecursive(const MyString& expr, size_t& position)
{

    if (position >= expr.getSize())
        throw std::out_of_range("Unexpected end of expression");

    if (expr[position] == '!')
    {

        position += 1;  

        if (position >= expr.getSize())
            throw std::out_of_range("Expected expression after '!'");

        Expression* operand = parseExprRecursive(expr, position);
        return new Negation(operand);

    }

    if (expr[position] == '(')
    {

        position += 1;

        Expression* left = parseExprRecursive(expr, position);

        char oper = expr[position];
        position += 1;

        Expression* right = parseExprRecursive(expr, position);

        if (expr[position] != ')') throw std::logic_error("Expected ')'");

        position += 1;

        if (oper == '&') return new Conjunction(left, right);
        if (oper == '|') return new Disjunction(left, right);
        throw std::logic_error("Unknown operator");

    }
    else if (expr[position] == '0' || expr[position] == '1')
    {

        bool value = (expr[position++] == '1');
        return new Constant(value);

    }
    else
    {

        char var = expr[position++];
        bool value = false;
        std::cout << "Enter actaull value for the current variable: " << var << std::endl;
        std::cin >> value;

        return new Variable(MyString(var), value);
    }

}

ExpressionCalculator::ExpressionCalculator(const MyString& expr)
{

	parseExpr(expr);

}

ExpressionCalculator::ExpressionCalculator(const ExpressionCalculator& other)
{

	copyFrom(other);

}

ExpressionCalculator::ExpressionCalculator(ExpressionCalculator&& other) noexcept
{

	moveTo(std::move(other));

}

ExpressionCalculator& ExpressionCalculator::operator = (const ExpressionCalculator& other)
{

	if (this != &other) 
	{

		free();
		copyFrom(other);

	}

	return *this;

}

ExpressionCalculator& ExpressionCalculator::operator = (ExpressionCalculator && other) noexcept
{

	if (this != &other)
	{

		free();
		moveTo(std::move(other));

	}

	return *this;

}

ExpressionCalculator::~ExpressionCalculator() 
{

	free();

}

bool ExpressionCalculator::evaluate() const 
{

	return root->evaluate();

}

void ExpressionCalculator::clear() 
{

	free();

}

void ExpressionCalculator::setNewExpr(const MyString& expr) 
{

	if (root != nullptr) throw std::logic_error("Error");
	parseExpr(expr);

}
