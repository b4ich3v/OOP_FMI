#include "ArrFileSorting.h"

ArrFileSorting::ArrFileSorting(const MyString& fileName) :
    FileSorting(fileName) {}

ArrFileSorting::ArrFileSorting(const MyString& fileName, const int* data, int size) :
    FileSorting(fileName, data, size) {}

void ArrFileSorting::read() 
{

    std::ifstream file(getFileName().getData());
    if (!file.is_open()) return;

    const char* clean = HELPERS::cutWhiteSpaces(file);

    if (clean[0] != '[') { delete[] clean; return; }
    int size = 0;

    for (int i = 1; clean[i] != ']' && clean[i] != '\0'; i++) 
    {

        if (clean[i] == '-') continue;
        else if (clean[i] >= '0' && clean[i] <= '9')
        {

            size += 1;
            while (clean[i + 1] >= '0' && clean[i + 1] <= '9') i += 1;

        }

    }
        
    int* data = new int[size];
    int index = 0;

    for (int i = 1; clean[i] != ']' && clean[i] != '\0'; i++)
    {
   
        int sign = 1;

        if (clean[i] == '-') { sign = -1; ++i; }
        int number = 0;

        while (clean[i] >= '0' && clean[i] <= '9') 
        {

            number = number * 10 + (clean[i] - '0');
            i += 1;

        }

        data[index++] = sign * number;

    }


    delete[] clean;

    HELPERS::bubbleSort(data, size);
    setData(data, size);
    delete[] data;
    file.close();

}

void ArrFileSorting::write() const
{

    std::ofstream file(getFileName().getData());
    if (!file.is_open()) return;

    const int* data = getData();
    int size = getSize();

    file.put('[');

    for (int i = 0; i < size; i++) 
    {
        
        if (i > 0) file.put(' ');
        
        int number = data[i];

        if (number < 0) { file.put('-'); number = -number; }
        
        char temp[12];
        int position = 0;

        do 
        {

            temp[position++] = char('0' + (number % 10));
            number /= 10;

        } while (number);
        
        for (int j = position - 1; j >= 0; j--) file.put(temp[j]);

    }

    file.put(']');
    file.close();

}
