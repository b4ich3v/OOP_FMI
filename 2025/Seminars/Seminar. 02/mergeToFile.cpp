#include <iostream>
#include <fstream>

int getFileSize(std::ifstream& file, const char target)
{

    int result = 0;
    char current = 'a';

    while (true)
    {

        current = file.get();

        if (current == target) result += 1;
        if (file.eof()) break;

    }

    file.clear();
    file.seekg(0, std::ios::beg);
    return result + 1;

}

int* readFromFile(std::ifstream& file, int& size)
{

    size = getFileSize(file, ' ');
    int* array = new int[size];

    for (int i = 0; i < size; i++)
    {

        file >> array[i];

    }

    file.close();
    return array;

}

void mergeToFile(const char* fileName, const char* fileName1, const char* fileName2)
{

    std::ofstream file(fileName);
    std::ifstream file1(fileName1);
    std::ifstream file2(fileName2);

    if (!file.is_open() || !file1.is_open() || !file2.is_open()) return;

    int size1 = 0;
    int size2 = 0;

    int* array1 = readFromFile(file1, size1);
    int* array2 = readFromFile(file2, size2);

    int index1, index2 = 0;

    while (index1 < size1 && index2 < size2)
    {

        if (array1[index1] <= array2[index2])
        {

            file << array1[index1] << " ";
            index1 += 1;

        }
        else
        {

            file << array2[index2] << " ";
            index2 += 1;

        }

    }

    while (index1 < size1)
    {

        file << array1[index1] << " ";
        index1 += 1;

    }

    while (index2 < size2)
    {

        file << array2[index2] << " ";
        index2 += 1;

    }

    delete[] array1;
    delete[] array2;
    file.close();

}

int main()
{

    mergeToFile("../result.txt", "../test1.txt", "../test2.txt");
    return 0;

}


