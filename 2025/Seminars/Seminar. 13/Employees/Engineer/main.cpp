#include <iostream>
#include "Engineer.h"

int main()
{

    MyString name("Ivan Petrov");
    MyString tech("Machine Learning");

    Engineer eg(name, tech);
    eg.printInfo();

    return 0;
}

