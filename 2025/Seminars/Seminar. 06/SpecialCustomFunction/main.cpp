#include "SpecialCustomFunction.h"

int main()
{

    int arr[5] = { 3,-4,0,10,40 };
    SpecialCustomFunction func([](int num) -> int { return num * num + num; }, arr, 5);

    func.printSpecialNumbers();
    std::cout << func(7) << std::endl << func(4) << std::endl; 

    func--; 

    std::cout << func(-5) << std::endl; 

    SpecialCustomFunction func2 = !func; 
    func.printSpecialNumbers();

    std::cout << func2(5) << std::endl; 


    return 0;

}
