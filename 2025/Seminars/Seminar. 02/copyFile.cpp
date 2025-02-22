#include <iostream>
#include <fstream>

void copyFile(const char* fileName1, const char* fileName2)
{

    std::ifstream file1(fileName1);
    std::ofstream file2(fileName2);

    if (!file1.is_open() || !file2.is_open()) return;

    char buffer[1024];

    while (true)
    {

        file1.getline(buffer, 1024);
        file2 << buffer << std::endl;

        if (file1.eof()) break;

    }

    file1.close();
    file2.close();

}

int main()
{

    copyFile("../main.cpp", "../example.txt");
    return 0;

}
