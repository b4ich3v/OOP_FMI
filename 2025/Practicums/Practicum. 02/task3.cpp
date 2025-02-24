#include <iostream>
#include <fstream>

typedef bool (*predicate)(int, int);

int getFileSizeCustom(std::ifstream& file)
{

    char currentCh = 'a';
    int counter = 0;

    while (true)
    {

        currentCh = file.get();

        if (currentCh == ' ') counter += 1;
        if(file.eof()) break;


    }

    file.clear();
    file.seekg(0, std::ios::beg);

    return counter + 1;

}

int* readArray(const char* fileName, int& size)
{

    std::ifstream file(fileName);

    if (!file.is_open()) return nullptr;

    size = getFileSizeCustom(file);
    int* result = new int[size];
    int number = 0;

    for (int i = 0; i < size; i++)
    {

        file >> number;
        result[i] = number;

    }

    file.close();
    return result;

}

bool func1(int a, int b)
{

    return a > b;

}

bool func2(int a, int b)
{

    return a < b;

}

void bubbleSort(int* array, int size, predicate f)
{

    for (int i = 0; i < size - 1; i++)
    {

        for (int j = 0; j < size - i - 1; j++)
        {

            if (f(array[j], array[j + 1]))
            {

                std::swap(array[j], array[j + 1]);

            }

        }

    }

}

void printArray(int* array, int size)
{

    for (int i = 0; i < size; i++)
    {

        std::cout << array[i] << " ";

    }

    std::cout << std::endl;

}

int main()
{

    int size = 0;
    int* array1 = readArray("../test1.txt", size);
    int* array2 = readArray("../test1.txt", size);

    bubbleSort(array1, size, func1);
    bubbleSort(array2, size, func2);

    printArray(array1, size);
    printArray(array2, size);

    delete[] array1;
    delete[] array2;

    return 0;

}
