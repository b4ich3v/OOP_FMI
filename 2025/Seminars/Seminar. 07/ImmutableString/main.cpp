#include <iostream>
#include "ImmutableString.h"

int main() 
{
    
    ImmutableString s1("Hello, world!");
    ImmutableString s2("Goodbye!");

    std::cout << "s1: " << s1 << std::endl;
    std::cout << "s2: " << s2 << std::endl;

    if (s1 < s2) std::cout << s1 << " is less than " << s2 << std::endl;
    else if (s1 == s2) std::cout << s1 << " is equal to " << s2 << std::endl;
    else std::cout << s1 << " is greater than " << s2 << std::endl;

    ImmutableString s3(s1);
    std::cout << s3 << std::endl;
    std::cout << s1[0] << std::endl;

    return 0;

}
