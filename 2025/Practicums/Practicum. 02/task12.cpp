#include <cstring>
#include <fstream>
#include <iostream>

void findAndAllValidWords(const char* fileName, const char* target, const char* str, char allWords[50][50], int& size)
{

    std::ifstream file(fileName);

    if (!file.is_open()) return;

    char buffer[50];
    int index = 0;

    while (true)
    {

        file.getline(buffer, 1024, ' ');

        if (!strcmp(buffer, target)) strncpy(allWords[index], str, 50);
        else strncpy(allWords[index], buffer, 50);

        index += 1;

        if (file.eof()) break;

    }

    size = index;
    file.close();

}

void replaceAllWordsInFile(const char* fileName, char allWords[50][50], int size)
{

    std::ofstream file(fileName, std::ios::trunc);

    if (!file.is_open()) return;

    for (int i = 0; i < size; i++)
    {

        file << allWords[i] << " ";

    }

    file.close();

}

int main()
{

    char allWords[50][50];
    int size = 0;

    findAndAllValidWords("../test1.txt", "sun", "moon", allWords, size);
    replaceAllWordsInFile("../test1.txt", allWords, size);

    return 0;

}
