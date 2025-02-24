#include <iostream>
#include <fstream>

void evaluateNumbers(const char* fileName, int number1, int number2, int number3)
{

    std::ofstream file(fileName);

    if (!file.is_open()) return;

    file << (number1 + number2 + number3);
    file << " ";
    file << (number1 * number2 * number3);
    file.close();

}

int main()
{

    int number1 = 0;
    int number2 = 0;
    int number3 = 0;

    std::cin >> number1 >> number2 >> number3;
    evaluateNumbers("../test1.txt", number1, number2, number3);

    return 0;

}
