#include <iostream>

struct ComplexNumber
{
public:

    double real;
    double im;

};

ComplexNumber init(double real, double im)
{

    return { real, im };

}

void print(const ComplexNumber& number)
{

    std::cout << number.real << " + " << number.im << "i";

}

ComplexNumber conjugate(const ComplexNumber& number)
{

    return { number.real, -number.im };

}

ComplexNumber add(const ComplexNumber& number1, const ComplexNumber& number2)
{

    return { number1.real + number2.real, number1.im + number2.im };

}

ComplexNumber subtract(const ComplexNumber& number1, const ComplexNumber& number2)
{

    return { number1.real - number2.real, number1.im - number2.im };

}

ComplexNumber multiply(const ComplexNumber& number1, const ComplexNumber& number2)
{

    return { number1.real * number2.real - number1.im * number2.im,
             number1.real * number2.im + number1.im * number2.real };

}

ComplexNumber reverse(const ComplexNumber& number)
{

    double denominator = number.real * number.real + number.im * number.im;
    if (denominator == 0) return {};

    return { number.real / denominator, -number.im / denominator };

}

ComplexNumber divide(const ComplexNumber& number1, const ComplexNumber& number2)
{

    if (number2.real == 0 && number2.im == 0) return {};

    ComplexNumber conjugateNum2 = conjugate(number2);
    ComplexNumber numerator = multiply(number1, conjugateNum2);
    double denominator = number2.real * number2.real + number2.im * number2.im;

    return { numerator.real / denominator, numerator.im / denominator };

}
