#include <cstring>
#include <fstream>
#include <iostream>

int getFileSize(std::ifstream& file)
{

    file.seekg(0, std::ios::end);
    int result = file.tellg();
    file.seekg(0, std::ios::beg);

    return result;

}

void replaceInFile(const char* fileName, const char target, const char newSymbol)
{

    std::fstream file(fileName, std::ios::in | std::ios::out | std::ios::binary);

    if (!file.is_open()) return;

    while (true)
    {

        char current = file.get();

        if (current == target)
        {

            file.seekg(-1, std::ios::cur);
            file.put(newSymbol);
            file.flush();

        }

        if (file.eof()) break;

    }

    file.close();

}

void readDataFromFile(const char* fileName)
{

    std::ifstream file(fileName, std::ios::binary);

    if (!file.is_open()) return;

    char data[1000];
    file.read((char*)data, sizeof(char) * getFileSize(file));

    std::cout << data;
    file.close();

}

int main()
{

    //std::ofstream file("../file.dat", std::ios::binary);
    //char text[] = "AAAaabbAcc";
    //file.write((const char*)text, sizeof(char) * 11);
    //file.close();

    replaceInFile("../file.dat", 'A', '#');
    readDataFromFile("../file.dat");

    return 0;

}
