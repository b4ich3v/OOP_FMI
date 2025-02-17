#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

#pragma warning(disable : 4996)

struct HexViewer
{

    char* data = nullptr;
    int size = 0;

};

int getFileSize(std::ifstream& is)
{


    if (!is.is_open()) 
    {

        return -1;

    }

    int currPosition = is.tellg();
    is.seekg(0, std::ios::end);
    int size = is.tellg();
    is.seekg(currPosition, std::ios::beg);
    is.clear();

    return size;

}

HexViewer init(const char* fileName)
{

    std::ifstream is(fileName, std::ios::binary);
    HexViewer toReturn;

    if (!is.is_open()) 
    {

        std::cout << "Error";
        return toReturn;

    }

    int size = getFileSize(is);
    toReturn.size = size;
    toReturn.data = new char[size + 1];
 
    is.read((char*)&toReturn.data, sizeof(char) * size);
    is.close();

    return toReturn;

}

void freeHexViewer(HexViewer& hex)
{

    delete[] hex.data;
    hex.data = nullptr;
    hex.size = 0;

}

bool isValidSymbol(char ch)
{

    return ch >= 'a' && ch <= 'z' ||
           ch >= 'A' && ch <= 'Z' ||
           ch >= '0' && ch <= '9';

}

void print(const HexViewer& myFile)
{

    for (int i = 0; i < myFile.size; i++)
    {

        std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)myFile.data[i] << " ";

    }
       
    std::cout << std::endl;

    for (int i = 0; i < myFile.size; i++)
    {

        if (isValidSymbol(myFile.data[i])) 
        {

            std::cout << myFile.data[i] << "  ";

        }  
        else 
        {

            std::cout << ".. ";

        }
           
    }

    std::cout << std::endl;

}

int main() 
{

    HexViewer hex = init("student.dat");

    if (hex.data != nullptr) 
    {

        print(hex);
        freeHexViewer(hex);

    }

    return 0;

}
