#include <cstring>
#include <fstream>
#include <iostream>

namespace CONSTANTS
{

    const char SEPARATOR = '|';
    const char WHITE_SPACE = ' ';
    const char PATTERN_FOR_ROW1[34] = "| Name | Faculty Number | Grade |";
    const char PATTERN_FOR_ROW2[34] = "|------|----------------|-------|";

    const int MAX_SIZE_NAME = 51;
    const int MAX_SIZE_ID = 11;
    const int MAX_SIZE_ROW = 1024;
    const int MAX_SIZE_ROWS = 50;

}

namespace HELP_FUNCTIONS
{

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

            if (current != CONSTANTS::WHITE_SPACE) break;

        }

    }

}

struct FieldForName
{
public:

    char name[CONSTANTS::MAX_SIZE_NAME];

};

struct FieldForId
{
public:

    char id[CONSTANTS::MAX_SIZE_ID];

};

struct FieldForGrade
{
public:

    double aGrade;

};

struct Row
{
public:

    FieldForName field1;
    FieldForId field2;
    FieldForGrade field3;

};

struct Table
{
public:

    Row rows[CONSTANTS::MAX_SIZE_ROWS];
    int countOfRows;

};

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

    strncpy(result.field1.name, firstName, 51);
    result.field1.name[strlen(firstName)] = '\0';

    HELP_FUNCTIONS::skipWhiteSpacesToSep(file);
    file >> result.field2.id;

    HELP_FUNCTIONS::skipWhiteSpacesToSep(file);
    file >> result.field3.aGrade;

    HELP_FUNCTIONS::skipWhiteSpacesToSep(file);
    return result;

}

Table parseTable(const char* fileName)
{

    std::ifstream file(fileName);

    if (!file.is_open()) return {};

    Table result;
    result.countOfRows = HELP_FUNCTIONS::getCountOfRows(file) - 2;

    HELP_FUNCTIONS::skipFirstTwoRows(file);

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
    file << row.field1.name << " ";

    file << CONSTANTS::SEPARATOR << " ";
    file << row.field2.id << " ";

    file << CONSTANTS::SEPARATOR << " ";
    file << row.field3.aGrade << " ";

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

    std::cout << row.field1.name << " ";
    std::cout << row.field2.id << " ";
    std::cout << row.field3.aGrade;

}

void printStudentById(const Table& table, const char* id)
{

    for (int i = 0; i < table.countOfRows; i++)
    {

        if (!strcmp(table.rows[i].field2.id, id))
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

        if (!strcmp(table.rows[i].field2.id, id))
        {

            table.rows[i].field3.aGrade = newGrade;

        }

    }

}

int main()
{

    Table table = parseTable("../test1.txt");

    printStudentById(table, "0MI0600328");
    changeGrade(table, "0MI0600328", 6.00);
    printStudentById(table, "0MI0600328");

    std::cout << std::endl;

    printStudentById(table, "2MI0600305");
    changeGrade(table, "2MI0600305", 2.00);
    printStudentById(table, "2MI0600305");

    writeTableToFile(table, "../test2.txt");

    return 0;

}
