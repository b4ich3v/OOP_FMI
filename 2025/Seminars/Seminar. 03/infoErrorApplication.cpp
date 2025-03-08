#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>

#pragma warning(disable:4996)

namespace HELPERS
{

    const char PATTERN1[] = "[ERROR]";
    const char PATTERN2[] = "[INFO]";
    const int MAX_SIZE_OPTION = 1024;

}

struct ArrayForString
{
public:

    char** strings = nullptr;
    int size = 0;
    int capacity = 8;

};

void freeArrayForStringData(ArrayForString& array) 
{

    if (!array.strings) return;

    for (int i = 0; i < array.size; i++)
    {

        delete[] array.strings[i];
        array.strings[i] = nullptr;

    }

    delete[] array.strings;
    array.strings = nullptr;

}

void resize(ArrayForString& array, int newCapacity)
{

    if (newCapacity < array.capacity) return;

    char** newStrings = new char* [newCapacity];

    for (int i = 0; i < array.size; i++)
    {

        newStrings[i] = new char[strlen(array.strings[i]) + 1];
        strcpy(newStrings[i], array.strings[i]); 

    }

    delete[] array.strings; 
    array.strings = newStrings;
    array.capacity = newCapacity;

}

void addString(ArrayForString& array, char* str)
{

    if (array.size == array.capacity) resize(array, array.capacity * 2);

    array.strings[array.size] = new char[strlen(str) + 1];
    strcpy(array.strings[array.size], str);  
    array.size += 1;

}

char* getBack(const ArrayForString& array) 
{

    if (array.size == 0) return nullptr;
    return array.strings[array.size - 1];

}

bool isEmpty(const ArrayForString& array) 
{

    return array.size == 0;

}

void readDataFromBinaryFile(std::ifstream& file)
{

    int countOfLogs = 0;
    file.read((char*)&countOfLogs, sizeof(int));

    for (int i = 0; i < countOfLogs; i++)
    {

        int size = 0;
        file.read((char*)&size, sizeof(int));

        char* currentLog = new char[size + 1];
        file.read((char*)currentLog, size);
        currentLog[size] = '\0';

        std::cout << currentLog << std::endl;
        delete[] currentLog;

    }

}

void createArrayBeforeCycle(ArrayForString& array) 
{

    array.strings = new char*[array.capacity];

}

int main()
{

    ArrayForString arr1;
    ArrayForString arr2;
    createArrayBeforeCycle(arr1);
    createArrayBeforeCycle(arr2);
    std::ofstream dataBase("../file.dat", std::ios::binary);

    while (true)
    {

        char option[HELPERS::MAX_SIZE_OPTION];
        std::cin.getline(option, HELPERS::MAX_SIZE_OPTION);

        if (!strcmp(option, "show_errors"))
        {

            if (isEmpty(arr2))
            {

                std::cout << "No errors to be shown!" << std::endl;

            }
            else
            {

                std::cout << getBack(arr2) << std::endl;

            }

        }
        else if (!strcmp(option, "input"))
        {

            char patternOption[HELPERS::MAX_SIZE_OPTION];
            char text[HELPERS::MAX_SIZE_OPTION];

            std::cin.getline(patternOption, HELPERS::MAX_SIZE_OPTION); 
            std::cin.getline(text, HELPERS::MAX_SIZE_OPTION);

            if (!strcmp(patternOption, HELPERS::PATTERN1))
            {

                addString(arr1, text);
                addString(arr2, text);

            }
            else if (!strcmp(patternOption, HELPERS::PATTERN2))
            {

                addString(arr1, text);

            }
            else
            {

                std::cout << "Error" << std::endl;

            }

        }
        else if (!strcmp(option, "exit"))
        {

            std::cout << "See you soon!" << std::endl;
            break;

        }

    }

    int countOfLogs = arr1.size;
    dataBase.write((const char*)&countOfLogs, sizeof(int));

    for (int i = 0; i < arr1.size; i++)
    {

        int size = strlen(arr1.strings[i]);
        dataBase.write((const char*)&size, sizeof(int));
        dataBase.write((const char*)arr1.strings[i], size);

    }

    dataBase.close();
    std::ifstream file("../file.dat", std::ios::binary);

    if (file.is_open()) return -1;
    
    std::cout << std::endl;
    readDataFromBinaryFile(file);
    file.close();

    freeArrayForStringData(arr1);
    freeArrayForStringData(arr2);

    return 0;

}
