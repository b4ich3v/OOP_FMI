#include <iostream>
#include <fstream>

namespace CONSTANTS
{

    const char PATTERN[17] = "0123456789ABCDEF";
    const int MASK = 15;

    const int A_REFERENCE = 10;
    const int B_REFERENCE = 11;
    const int C_REFERENCE = 12;
    const int D_REFERENCE = 13;
    const int E_REFERENCE = 14;
    const int F_REFERENCE = 15;
    const int COUNT_HEXADECIMAL = 16;

}

struct HexViewer
{
public:

    char* data;
    int size;

};

struct HexParts
{
public:

    char part1;
    char part2;

};

int getFileSize(std::ifstream& file)
{

    int currentPosition = file.tellg();
    file.seekg(0, std::ios::end);
    int size = file.tellg();
    file.seekg(currentPosition, std::ios::beg);
    file.clear();

    return size;

}

HexViewer readDataFromBinaryFile(const char* fileName)
{

    std::ifstream file(fileName, std::ios::binary);

    if (!file.is_open()) return { nullptr, 0 };

    HexViewer result;
    result.size = getFileSize(file);
    result.data = new char[result.size + 1];
    file.read((char*)result.data, result.size);
    result.data[result.size] = '\0';

    file.close();
    return result;

}

void deleteHexViewer(HexViewer& hex)
{

    delete[] hex.data;
    hex.data = nullptr;
    hex.size = 0;

}

HexParts* getHexadecimal(const HexViewer& hex, int& size)
{

    HexParts* result = new HexParts[2 * hex.size + 1];
    int index = 0;

    for (int i = 0; i < hex.size; i++)
    {

        char currentByte = hex.data[i];
        char upperBits = (currentByte >> 4) & CONSTANTS::MASK;
        char lowerBits = currentByte & CONSTANTS::MASK;

        if (CONSTANTS::PATTERN[upperBits] != '0' || CONSTANTS::PATTERN[lowerBits] != '0')
        {

            result[index].part1 = CONSTANTS::PATTERN[upperBits];
            result[index].part2 = CONSTANTS::PATTERN[lowerBits];
            index += 1;

        }

    }

    size = index;
    return result;

}

bool isDigit(char ch)
{

    return ch >= '0' && ch <= '9';

}

void processingPart(int& number, char part, int& iter)
{

    if (isDigit(part)) number += iter * (part - '0');
    else if (part >= 'A' && part <= 'F')
    {

        switch (part)
        {

        case 'A': number += iter * CONSTANTS::A_REFERENCE; break;
        case 'B': number += iter * CONSTANTS::B_REFERENCE; break;
        case 'C': number += iter * CONSTANTS::C_REFERENCE; break;
        case 'D': number += iter * CONSTANTS::D_REFERENCE; break;
        case 'E': number += iter * CONSTANTS::E_REFERENCE; break;
        case 'F': number += iter * CONSTANTS::F_REFERENCE; break;
        default: break;

        }

    }

    iter /= CONSTANTS::COUNT_HEXADECIMAL;

}

void reverseDataParts(HexParts* parts, int size)
{

    for (int i = 0; i < size / 2; i++)
    {

        std::swap(parts[i], parts[size - i - 1]);

    }

}

void convertToDecimal(HexParts* parts, int size)
{

    int number = 0;
    int iter = 1;

    for (int i = 0; i < size * 2 - 1; i++) iter *= CONSTANTS::COUNT_HEXADECIMAL;
    reverseDataParts(parts, size);

    for (int i = 0; i < size; i++)
    {

        char p1 = parts[i].part1;
        char p2 = parts[i].part2;


        processingPart(number, p1, iter);
        processingPart(number, p2, iter);

    }

    std::cout << number << std::endl;

}

int main()
{

    //std::ofstream file("../file.dat");
    //int number = 1322;
    //file.write((const char*)&number, sizeof(int));
    //file.close();

    int size = 0;
    HexViewer hex = readDataFromBinaryFile("../file.dat");
    HexParts* parts = getHexadecimal(hex, size);
    convertToDecimal(parts, size);

    delete[] parts;
    deleteHexViewer(hex);

    return 0;

}
