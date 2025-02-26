#include <iostream>
#include <fstream>

void concatTwoFilesAndReplace(const char* fileName1, const char* fileName2, const char* fileName3)
{

    std::ifstream file1(fileName1);
    std::ifstream file2(fileName2);
    std::ofstream file3(fileName3);

    if (!file1.is_open() || !file2.is_open() || !file3.is_open()) return;

    char buffer[1024];

    while (true)
    {

        file1.getline(buffer, 1024);
        file3 << buffer;
        file3 << std::endl;

        if (file1.eof()) break;

    }

    while (true)
    {

        file2.getline(buffer, 1024);
        file3 << buffer;
        file3 << std::endl;

        if (file2.eof()) break;

    }

    file1.close();
    file2.close();
    file3.close();

}

int main()
{

    concatTwoFilesAndReplace("../test1.txt", "../test2.txt", "../result.txt");
    return 0;

}
