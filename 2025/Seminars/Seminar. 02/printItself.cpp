#include <iostream>
#include <fstream>

void printItself()
{

    std::ifstream file("../main.cpp");

    if (!file.is_open()) return;

    char buffer[1024];

    while (true) 
    {

        file.getline(buffer, 1024);
        std::cout << buffer << std::endl;

        if (file.eof()) break;

    }

    file.close();

}

int main()
{

    printItself();
    return 0;

}
