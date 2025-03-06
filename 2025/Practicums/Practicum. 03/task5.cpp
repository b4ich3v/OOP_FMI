#include <iostream>
#include <fstream>

namespace HELPERS
{

    const int data[] = { 23, 48, 3, 12, 4006 };
    const int NUMBERS_COUNT = sizeof(data) / sizeof(data[0]);

    void writeDataToBinaryFile(const char* fileName)
    {

        if (!fileName) return;

        std::ofstream file(fileName, std::ios::binary);
        if (!file.is_open()) return;

        file.write(reinterpret_cast<const char*>(data), sizeof(data));
        file.close();

    }

    int getFileSize(std::ifstream& file)
    {

        file.seekg(0, std::ios::end);
        int result = file.tellg();
        file.seekg(0, std::ios::beg);
        return result;

    }

}

struct Parser
{

    int* data = nullptr;
    int size = 0;

};

void initParser(Parser& parser, int& countOfNumbers)
{

    HELPERS::writeDataToBinaryFile("file.dat");

    std::ifstream file("file.dat", std::ios::binary);

    if (!file.is_open()) return;

    int fileSize = HELPERS::getFileSize(file);
    countOfNumbers = fileSize / sizeof(int);

    parser.size = countOfNumbers;
    parser.data = new int[countOfNumbers];

    file.read((char*)(parser.data), fileSize);
    file.close();

}

void printArray(int* arr, int size, int key)
{

    for (int i = 0; i < size; i++)
    {

        std::cout << arr[i] + key << " ";

    }

    std::cout << std::endl;

}

int readKeyFromBinaryFile(const char* fileName)
{

    if (!fileName) return -1;

    std::ifstream file(fileName, std::ios::binary);

    if (!file.is_open()) return -1;

    int result = 0;
    file.read((char*)&result, sizeof(int));
    file.close();

    return result;

}

int main()
{

    Parser parser;
    int countOfNumbers = 0;
    initParser(parser, countOfNumbers);

    for (int i = 0; i < countOfNumbers; i++)
    {

        std::cout << parser.data[i] << " ";

    }

    std::cout << std::endl;

    int key = readKeyFromBinaryFile("../file1.dat");
    printArray(parser.data, countOfNumbers, key);

    delete[] parser.data;
    return 0;

}

