#include "BinaryFileSorting.h"

BinaryFileSorting::BinaryFileSorting(const MyString& fileName) :
    FileSorting(fileName) {}

BinaryFileSorting::BinaryFileSorting(const MyString& fileName, const int* data, int size) :
    FileSorting(fileName, data, size) {}

void BinaryFileSorting::read() 
{

    std::ifstream file(getFileName().getData(), std::ios::binary);
    if (!file.is_open()) return;

    int bytes = HELPERS::getFileSize(file);
    int size = bytes / sizeof(int);
    int* data = new int[size];
    file.seekg(0, std::ios::beg);
    file.read(reinterpret_cast<char*>(data), size * sizeof(int));

    HELPERS::bubbleSort(data, size);
    setData(data, size);
    delete[] data;

    file.close();

}

void BinaryFileSorting::write() const 
{

    std::ofstream file(getFileName().getData(), std::ios::binary);
    if (!file.is_open()) return;

    const int* data = getData();
    int size = getSize();
    file.write(reinterpret_cast<const char*>(data), size * sizeof(int));

    file.close();

}
