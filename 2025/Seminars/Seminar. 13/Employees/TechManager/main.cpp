#include <iostream>
#include "TechManager.h"

int main()
{

    MyString name("Ivan Petrov");
    MyString project("AI Assistant");
    MyString tech("Machine Learning");
    MyString task("Implement Bitset");

    TechManager tm(name, project, tech);
    tm.assignTask(task);

    return 0;
}
