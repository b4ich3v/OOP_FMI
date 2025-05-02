#include <iostream>
#include <cstring>
#include <fstream>
#include "MyString.h"

enum class FileType
{

    TXT = 0,
    BINARY = 1,
    CSV = 2

};

namespace HELPERS 
{

    const int DEFAULT_SIZE = 10;
    
    int getFileSize(std::ifstream& file) 
    {

        int currentPos = file.tellg();
        file.seekg(0, std::ios::end);
        int result = file.tellg();
        
        file.clear();
        file.seekg(currentPos);

        return result;

    }

    int getCountOfNumbersBySep(const char seperator, std::ifstream& file) 
    {

        int currentPos = file.tellg();
        int result = 0;

        while (!file.eof()) 
        {

            if ((char)file.get() == seperator) result += 1; 

        }

        file.clear();
        file.seekg(currentPos);

        return result + 1;

    }

}

class FileReader 
{
private:

    MyString fileName;

public:

    FileReader(const MyString& fileName) : fileName(fileName) {}

    const MyString& getFileName() const
    {

        return fileName;

    }

    virtual void read(int*& array, int& size) const = 0;

    virtual ~FileReader() = default;

};

class FileWriter 
{
private:

    MyString fileName;

public:

    FileWriter(const MyString& fileName): fileName(fileName) {}

    const MyString& getFileName() const 
    {

        return fileName;

    }

    virtual void write(const int* array, int size) const = 0;

    virtual ~FileWriter() = default;

};

class ArrayFileReader: public FileReader
{
public:

    ArrayFileReader(const MyString& fileName): FileReader(fileName) {}

    void read(int*& array, int& size) const override
    {

        if (!array || size < 0) return;

        std::ifstream file(getFileName().getData());

        if (!file.is_open()) return;

        size = HELPERS::getCountOfNumbersBySep(' ', file);
        delete[] array;
        array = new int[size];
        int currentNumber = 0;

        for (int i = 0; i < size; i++)
        {

            file >> currentNumber;
            array[i] = currentNumber;

        }

        file.close();

    }

};

class ArrayFileWriter: public FileWriter 
{
public:

    ArrayFileWriter(const MyString& fileName): FileWriter(fileName) {}

    void write(const int* array, int size) const override 
    {

        if (!array || size < 0) return;

        std::ofstream file(getFileName().getData());

        if (!file.is_open()) return;

        for (int i = 0; i < size; i++)
        {

            file << array[i];

        }

        file.close();

    }

};

class BinaryFileReader: public FileReader
{
public:

    BinaryFileReader(const MyString& fileName): FileReader(fileName) {}

    void read(int*& array, int& size) const override 
    {

        if (!array || size < 0) return;

        std::ifstream file(getFileName().getData(), std::ios::binary);

        if (!file.is_open()) return;

        size = HELPERS::getFileSize(file) / sizeof(int);
        delete[] array;
        array = new int[size];
        file.read((char*)array, size * sizeof(int));

        file.close();

    }

};

class BinaryFileWriter: public FileWriter
{
public:

    BinaryFileWriter(const MyString& fileName): FileWriter(fileName) {}

    void write(const int* array, int size) const override 
    {

        if (!array || size < 0) return;

        std::ofstream file(getFileName().getData(), std::ios::binary);

        if (!file.is_open()) return;

        file.write((const char*)array, sizeof(int) * size);

        file.close();

    }

};

class CSVFileReader: public FileReader
{
public:

    CSVFileReader(const MyString& fileName): FileReader(fileName) {}

    void read(int*& array, int& size) const override
    {

        if (!array || size < 0) return;

        std::ifstream file(getFileName().getData());

        if (!file.is_open()) return;

        size = HELPERS::getCountOfNumbersBySep(',', file);
        delete[] array;
        array = new int[size];
        int currentNumber = 0;

        for (int i = 0; i < size; i++)
        {

            file >> currentNumber;
            array[i] = currentNumber;

        }

        file.close();

    }

};

class CSVFileWriter: public FileWriter
{
public:

    CSVFileWriter(const MyString& fileName) : FileWriter(fileName) {}

    void write(const int* array, int size) const override
    {

        if (!array || size < 0) return;

        std::ofstream file(getFileName().getData());

        if (!file.is_open()) return;

        for (int i = 0; i < size; i++) 
        {

            file << array[i];
            if (i < size - 1) file << ',';
                
        }


        file.close();

    }

};

class FileManipulationFactory 
{
public:

    static FileReader* fileReaderFactory(const MyString& fileName) 
    {

        std::cout << "Enter number: " << std::endl;
        int number = 0;
        std::cin >> number;

        FileType type = (FileType)number;

        switch (type)
        {

        case FileType::TXT: return new ArrayFileReader(fileName);
        case FileType::BINARY: return new BinaryFileReader(fileName);
        case FileType::CSV: return new CSVFileReader(fileName);
        default: return nullptr;
           
        }

        return nullptr;

    }

    static FileWriter* fileWriterFactory(const MyString& fileName) 
    {

        std::cout << "Enter number: " << std::endl;
        int number = 0;
        std::cin >> number;

        FileType type = (FileType)number;

        switch (type)
        {

        case FileType::TXT: return new ArrayFileWriter(fileName);
        case FileType::BINARY: return new BinaryFileWriter(fileName);
        case FileType::CSV: return new CSVFileWriter(fileName);
        default: return nullptr;

        }

        return nullptr;

    }

};

void transfer(const MyString& fromName, const MyString& toName) 
{

    int* dummyArray = new int[HELPERS::DEFAULT_SIZE];
    int size = HELPERS::DEFAULT_SIZE;

    FileReader* fileObj1 = FileManipulationFactory::fileReaderFactory(fromName);
    if (!fileObj1) { delete[] dummyArray; delete fileObj1; return; }
    fileObj1->read(dummyArray, size);

    FileWriter* fileObj2 = FileManipulationFactory::fileWriterFactory(toName);
    if (!fileObj2) { delete[] dummyArray; delete fileObj2; return; }
    fileObj2->write(dummyArray, size);

    delete fileObj1;
    delete fileObj2;
    delete[] dummyArray;

}

int main() 
{
 
    std::ofstream testFile("input.txt");
    testFile << "1 2 3 4 5";
    testFile.close();

    MyString fromFile("input.txt");
    MyString toFile("output.dat");

    transfer(fromFile, toFile);

    
    MyString fromBinary("output.dat");
    MyString toCSV("converted.csv");

    transfer(fromBinary, toCSV);

    return 0;

}
