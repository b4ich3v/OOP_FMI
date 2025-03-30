#include <iostream>
#include "StringPool.h"

int main() 
{

    StringPool pool;

    pool.chainString("Hello");
    pool.chainString("World");
    pool.chainString("Hello");  

    std::cout << pool.getCountOfNodes() << std::endl;

    const char* str1 = pool.unchainString("Hello");
    std::cout << str1 << std::endl;


    const char* str2 = pool.unchainString("Hello");
    std::cout << str2 << std::endl;
 

    const char* str3 = pool.unchainString("World");
    std::cout << str3 << std::endl;
    std::cout << pool.getCountOfNodes() << std::endl;

    delete[] str2;
    delete[] str3;
    return 0;

}
