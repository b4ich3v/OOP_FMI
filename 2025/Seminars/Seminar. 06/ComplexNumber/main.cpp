#include "ComplexNumber.h"

int main()
{

	ComplexNumber number(1, 1);
	ComplexNumber number1(1, 1);
	ComplexNumber number2(2, -11);
	ComplexNumber number3(3, 9);
	ComplexNumber number4(-6, 1);

	number1 *= number2;
	number1.printNumber();

	number2 += number3;
	number2.printNumber();

	number3 /= number1;
	number3.printNumber();

	number4 -= number3;
	number4.printNumber();

	ComplexNumber poweredNumber = number ^ (-3);
	poweredNumber.printNumber();

	return 0;

}
