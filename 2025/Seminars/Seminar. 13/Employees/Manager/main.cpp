#include <iostream>
#include "Manager.h"

int main()
{

    MyString name("Ivan Petrov");
    MyString project("AI Assistant");

    Manager mg(name, project);
    mg.printInfo();

    return 0;
}

