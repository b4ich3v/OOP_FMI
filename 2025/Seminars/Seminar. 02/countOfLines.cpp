#include <iostream>
#include <fstream>

int countOfLines()
{

    std::ifstream file("../main.cpp");

    if (!file.is_open()) return;

    char buffer[1024];
    int counter = 0;

    while (true) 
    {

        file.getline(buffer, 1024);
        counter += 1;

        if (file.eof()) break;

    }

    file.close();
    return counter;

}

int main()
{

    std::cout << countOfLines();
    return 0;

}


