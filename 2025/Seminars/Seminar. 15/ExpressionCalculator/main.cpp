#include <iostream>
#include "ExpressionCalculator.h"

int main() 
{

	MyString expr1("(((a&b)|c)|0)");
	MyString expr2("(1&a)");
	MyString expr3("(((1|0)&1)&(1|0))");
	MyString expr4("(!(1&0))");

	ExpressionCalculator calculator(expr1);
	std::cout << std::endl << calculator.evaluate() << std::endl << std::endl;
	calculator.clear();

	calculator.setNewExpr(expr2);
	std::cout << std::endl << calculator.evaluate() << std::endl << std::endl;
	calculator.clear();

	calculator.setNewExpr(expr3);
	std::cout << std::endl << calculator.evaluate() << std::endl << std::endl;
	calculator.clear();

	calculator.setNewExpr(expr4);
	std::cout << std::endl << calculator.evaluate() << std::endl << std::endl;
	calculator.clear();

	return 0;

}
