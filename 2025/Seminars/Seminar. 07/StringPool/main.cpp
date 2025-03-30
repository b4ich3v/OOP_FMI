#include <iostream>
#include "StringPool.h"

int main()
{

    StringPool pool;

    pool.chainString("Hello");
    pool.chainString("World");
    pool.chainString("Hello");
    pool.printPool();

    std::cout << pool.getCountOfNodes() << std::endl;

    const char* str1 = pool.unchainString("Hello");
    std::cout << str1 << std::endl << std::endl;
    pool.printPool();

    const char* str2 = pool.unchainString("Hello");
    std::cout << str2 << std::endl << std::endl;
    pool.printPool();

    const char* str3 = pool.unchainString("World");
    std::cout << str3 << std::endl;
    std::cout << pool.getCountOfNodes() << std::endl;
    pool.printPool();

    delete[] str2;
    delete[] str3;
    return 0;

}
