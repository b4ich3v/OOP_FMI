#include "MyString.h"

int main()
{

    MyString str1("Yoan");
    MyString str2(" Baychev");
    MyString str3("xValue example");
    MyString&& xRef = std::move(str3);

    str1 += str2;
    str2 = str1;
    std::cout << str1;
    std::cout << str1;

    MyString copyStr1 = str1;
    std::cout << copyStr1;

    MyString str;
    std::cin >> str;
    std::cout << str;

    std::cout << (str1 <= str2) << std::endl;
    std::cout << xRef << std::endl;

    return 0;

}
