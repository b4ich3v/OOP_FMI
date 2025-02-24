#include <iostream>
#include <fstream>

int countOfCurrentSymbol(const char* fileName, char target)
{

    std::ifstream file(fileName);
    int counter = 0;
    char ch = 'a';

    if (!file.is_open()) return 0;

    while (true)
    {

        ch = file.get();

        if (ch == target) counter += 1;
        if (file.eof()) break;


    }

    file.close();
    return counter;

}

int main()
{

    std::cout << countOfCurrentSymbol("../test1.txt", 'a');
    return 0;

}
