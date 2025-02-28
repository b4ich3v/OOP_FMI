#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

namespace HELPERS
{

    const char PATTERN1[7] = "Dear, ";
    const char PATTERN2[11] = "Sincerely,";
    const int MAX_SIZE_ATTR = 50;
    const int MAX_SIZE_LINE = 1024;
    const int COUNT_ATTR = 4;

}

struct Data
{
public:

    char tittle[HELPERS::MAX_SIZE_ATTR];
    char recipientName[HELPERS::MAX_SIZE_ATTR];
    char message[HELPERS::MAX_SIZE_ATTR];
    char senderName[HELPERS::MAX_SIZE_ATTR];

};

Data readFromFile(const char* fileName)
{

    std::ifstream file(fileName);

    if (!file.is_open()) return {};

    char buffer[HELPERS::MAX_SIZE_LINE];
    int counter = 0;
    char allRows[HELPERS::COUNT_ATTR][HELPERS::MAX_SIZE_LINE];

    while (true)
    {

        file.getline(buffer, HELPERS::MAX_SIZE_LINE);
        strncpy(allRows[counter], buffer, strlen(buffer));
        counter += 1;

        if (counter == 4) break;

    }

    counter = 0;
    Data result;

    while (true)
    {

        std::stringstream ss(allRows[counter]);
        ss >> buffer;
        ss.seekg(1, std::ios::cur);
        ss.getline(buffer, HELPERS::MAX_SIZE_LINE);

        if (counter == 0)
        {

            strncpy(result.tittle, buffer, strlen(buffer));
            result.tittle[strlen(buffer)] = '\0';

        }
        else if (counter == 1)
        {

            strncpy(result.recipientName, buffer, strlen(buffer));
            result.recipientName[strlen(buffer)] = '\0';

        }
        else if (counter == 2)
        {

            strncpy(result.message, buffer, strlen(buffer));
            result.message[strlen(buffer)] = '\0';

        }
        else if (counter == 3)
        {

            strncpy(result.senderName, buffer, strlen(buffer));
            result.senderName[strlen(buffer)] = '\0';

        }

        counter += 1;

        if (counter == 4) break;

    }

    return result;

}

void writeToFile(const char* fileName, const Data& data)
{

    std::ofstream file(fileName);

    if (!file.is_open()) return;

    file << HELPERS::PATTERN1;
    file << data.tittle << " " << data.recipientName;
    file << std::endl << std::endl;
    file << data.message;
    file << std::endl << std::endl;
    file << HELPERS::PATTERN2;
    file << std::endl;
    file << data.senderName;

    file.close();

}

void printData(const Data& data)
{

    std::cout << data.tittle << " ";
    std::cout << data.recipientName << " ";
    std::cout << data.message << " ";
    std::cout << data.senderName << " ";

}

int main()
{

    Data data = readFromFile("../test1.txt");
    printData(data);
    writeToFile("../test2.txt", data);

    return 0;

}
