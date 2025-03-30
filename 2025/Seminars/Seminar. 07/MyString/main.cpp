#include "MyString.h"

int main()
{

    MyString str1("Yoan");
    MyString str2(" Baychev");

    str1 += str2;
    std::cout << str1;

    MyString copyStr1 = str1;
    std::cout << copyStr1;

    MyString str;
    std::cin >> str;
    std::cout << str;

    std::cout << (str1 <= str2);

    return 0;

}
