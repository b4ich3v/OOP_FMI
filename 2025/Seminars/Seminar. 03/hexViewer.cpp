#include <iostream>
#include <fstream>

struct HexViewer
{
public:

    char* data;
    int size;

};

int getFileSize(std::ifstream& file)
{

    file.seekg(0, std::ios::end);
    int result = file.tellg();
    file.seekg(0, std::ios::beg);

    return result;

}

void freeHex(HexViewer& hex)
{

    delete[] hex.data;
    hex.size = 0;

}

HexViewer hexParser(const char* fileName)
{

    std::ifstream file(fileName, std::ios::in | std::ios::binary);

    if (!file.is_open()) return { nullptr, 0 };

    HexViewer result;
    int size = getFileSize(file);
    result.size = size;
    result.data = new char[size + 1];

    file.read((char*)result.data, sizeof(char) * size);
    result.data[size] = '\0';

    file.close();
    return result;

}

void printHex(const HexViewer& hex)
{

    const char helper[] = "0123456789ABCDEF";
    const int number = 15;

    for (int i = hex.size - 1; i >= 0 ; i--)
    {

        char currentByte = hex.data[i];
        char lowerBits = helper[(currentByte >> 4) & number];
        char upperBits = helper[currentByte & number];

        std::cout << upperBits << lowerBits << " ";

    }

}

int main()
{

    //int number = 1233;
    //std::ofstream file("../file.dat");
    //file.write((const char*)&number, sizeof(int));

    HexViewer hex = hexParser("../file.dat");
    printHex(hex);
    freeHex(hex);

    return 0;

}
