#include <iostream>
#include <fstream>

void concatTwoFilesAndReplace(const char* fileName1, const char* fileName2, const char* fileName3)
{

    std::ifstream file1(fileName1);
    std::ifstream file2(fileName2);
    std::ofstream file3(fileName3);

    if (!file1.is_open() || !file2.is_open() || !file3.is_open()) return;

    char buffer[1024];
    bool isFirstRow = true;

    while (true)
    {

        if(!isFirstRow) file3 << std::endl;

        file1.getline(buffer, 1024);
        file3 << buffer;

        if (file1.eof()) break;

        isFirstRow = false;

    }

    isFirstRow = true;
    file3 << " ";

    while (true)
    {

        if (!isFirstRow) file3 << std::endl;

        file2.getline(buffer, 1024);
        file3 << buffer;

        if (file2.eof()) break;

        isFirstRow = false;

    }

    file1.close();
    file2.close();
    file3.close();

}

void addSymbolIfNeeded(const char* fileName, char ch)
{

    std::fstream file(fileName);

    if (!file.is_open()) return;

    char buffer[1024];

    while (true)
    {

        file.get(buffer, 1024, ' ');
        file.put(ch);

        if (file.eof()) break;

    }

    file.close();

}

int main()
{

    concatTwoFilesAndReplace("../test1.txt", "../test2.txt", "../result.txt");
    addSymbolIfNeeded("../result.txt", ',');

    return 0;

}
