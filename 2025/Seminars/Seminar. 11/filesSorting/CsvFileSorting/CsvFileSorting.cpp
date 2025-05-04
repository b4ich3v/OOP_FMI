#include "CsvFileSorting.h"

CsvFileSorting::CsvFileSorting(const MyString& fileName) :
    FileSorting(fileName) {}

CsvFileSorting::CsvFileSorting(const MyString& fileName, const int* data, int size) :
    FileSorting(fileName, data, size) {}

void CsvFileSorting::read() 
{

    std::ifstream file(getFileName().getData());
    if (!file.is_open()) return;

    char buffer[8192];
    file.getline(buffer, 8192);

    int counter = 0;

    for (int i = 0; buffer[i] != '\0'; i++)
        if (buffer[i] == ',') counter += 1;

    int size = counter + 1;
    int* data = new int[size];
    int index = 0;
    char* token = buffer;

    for (int i = 0; ; i++)
    {

        if (buffer[i] == ',' || buffer[i] == '\0') 
        {
         
            buffer[i] = '\0';
            
            data[index++] = atoi(token);
            if (buffer[i] == '\0') break;
            token = buffer + i + 1;

        }

    }

    HELPERS::bubbleSort(data, size);
    setData(data, size);
    delete[] data;

}

void CsvFileSorting::write() const
{

    std::ofstream file(getFileName().getData());
    if (!file.is_open()) return;

    const int* data = getData();
    int size = getSize();

    for (int i = 0; i < size; i++)
    {

        if (i > 0) file.put(',');

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

    file.close();

}
