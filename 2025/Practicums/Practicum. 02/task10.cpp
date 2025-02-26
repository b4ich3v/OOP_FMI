#include <iostream>
#include <fstream>
#include <cstring>

int getDifLine(const char* fileName1, const char* fileName2)
{

    std::ifstream file1(fileName1);
    std::ifstream file2(fileName2);

    if (!file1.is_open() || !file2.is_open()) return -1;

    int counter = 0;
    char buffer1[1024];
    char buffer2[1024];

    while (true)
    {

        file1.getline(buffer1, 1024);
        file2.getline(buffer2, 1024);

        if (!strcmp(buffer1, buffer2)) counter += 1;
        if (file1.eof() || file2.eof()) break;

    }

    file1.close();
    file2.close();

    return counter;

}

int main()
{

    std::cout << getDifLine("../test1.txt", "../test2.txt");

    return 0;

}
