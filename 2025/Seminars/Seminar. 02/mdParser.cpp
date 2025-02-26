#include <cstring>
#include <fstream>
#include <iostream>

namespace CONSTANTS
{

    const char SEPARATOR = '|';
    const char PATTERN_FOR_ROW1[34] = "| Name | Faculty Number | Grade |";
    const char PATTERN_FOR_ROW2[34] = "|------|----------------|-------|";

    const int MAX_SIZE_NAME = 51;
    const int MAX_SIZE_ID = 11;
    const int MAX_SIZE_ROW = 1024;
    const int MAX_SIZE_ROWS = 50;

}

struct Row
{
public:

    char name[CONSTANTS::MAX_SIZE_NAME];
    char id[CONSTANTS::MAX_SIZE_ID];
    double aGrade;

};

struct Table
{
public:

    Row rows[CONSTANTS::MAX_SIZE_ROWS];
    int countOfRows;

};

int getCountOfRows(std::ifstream& file)
{

    int counter = 0;
    char buffer[CONSTANTS::MAX_SIZE_ROW];

    while (true)
    {

        file.getline(buffer, CONSTANTS::MAX_SIZE_ROW);
        counter += 1;

        if (file.eof()) break;

    }

    file.clear();
    file.seekg(0, std::ios::beg);

    return counter;

}

void skipFirstTwoRows(std::ifstream& file)
{

    char buffer[CONSTANTS::MAX_SIZE_ROW];

    for (int i = 0; i < 2; i++)
    {

        file.getline(buffer, CONSTANTS::MAX_SIZE_ROW);

    }

}

void skipWhiteSpacesToSep(std::ifstream& file)
{

    char current = 'a';

    while (!file.eof())
    {

        current = file.get();

        if (current != ' ') break;

    }

}

Row parseRow(std::ifstream& file)
{

    file.ignore(2);
    Row result;

    char firstName[CONSTANTS::MAX_SIZE_NAME];
    char secondName[CONSTANTS::MAX_SIZE_NAME];

    file >> firstName;
    strcat(firstName, " ");

    file >> secondName;
    strcat(firstName, secondName);

    strncpy(result.name, firstName, 51);
    result.name[strlen(firstName)] = '\0';

    skipWhiteSpacesToSep(file);
    file >> result.id;

    skipWhiteSpacesToSep(file);
    file >> result.aGrade;

    skipWhiteSpacesToSep(file);
    return result;

}

Table parseTable(const char* fileName)
{

    std::ifstream file(fileName);

    if (!file.is_open()) return {};

    Table result;
    result.countOfRows = getCountOfRows(file) - 2;

    skipFirstTwoRows(file);

    for (int i = 0; i < result.countOfRows; i++)
    {

        result.rows[i] = parseRow(file);

    }

    file.close();
    return result;

}

void writeFirstTwoRows(std::ofstream& file)
{

    file << CONSTANTS::PATTERN_FOR_ROW1 << std::endl;
    file << CONSTANTS::PATTERN_FOR_ROW2 << std::endl;

}

void writeRowToFile(const Row& row, std::ofstream& file)
{

    file << CONSTANTS::SEPARATOR << " ";
    file << row.name << " ";

    file << CONSTANTS::SEPARATOR << " ";
    file << row.id << " ";

    file << CONSTANTS::SEPARATOR << " ";
    file << row.aGrade << " ";

    file << CONSTANTS::SEPARATOR << std::endl;

}

void writeTableToFile(const Table& table, const char* fileName)
{

    std::ofstream file(fileName);

    if (!file.is_open()) return;

    writeFirstTwoRows(file);

    for (int i = 0; i < table.countOfRows; i++)
    {

        writeRowToFile(table.rows[i], file);

    }

    file.close();

}

void printStudent(const Row& row)
{

    std::cout << row.name << " ";
    std::cout << row.id << " ";
    std::cout << row.aGrade;

}

void printStudentById(const Table& table, const char* id)
{

    for (int i = 0; i < table.countOfRows; i++)
    {

        if (!strcmp(table.rows[i].id, id))
        {

            printStudent(table.rows[i]);
            std::cout << std::endl;

        }

    }

}

void changeGrade(Table& table, const char* id, double newGrade)
{

    for (int i = 0; i < table.countOfRows; i++)
    {

        if (!strcmp(table.rows[i].id, id))
        {

            table.rows[i].aGrade = newGrade;

        }

    }

}

int main()
{

    Table table = parseTable("../test1.txt");
    writeTableToFile(table, "../test2.txt");

    printStudentById(table, "0MI0600328");
    changeGrade(table, "0MI0600328", 6.00);
    printStudentById(table, "0MI0600328");

    return 0;

}
