#include <iostream>
#include <fstream>

namespace CONSTANTS 
{

    const int MASK_E = 1;
    const int MASK_C = 2;
    const int MASK_T = 4;

    const int MASK_EC = 3;
    const int MASK_ET = 5;
    const int MASK_TC = 6;

    const int MAX_COUNT_DISCIPLINES = 50;
    const int MAX_SIZE_NAME = 50;

}

enum class Category
{

    OKN = 0,
    M = 1,
    PM = 2,
    PR = 3,
    Other = 4

};

enum class TypeOfExam
{

    E = 1 << 0,
    C = 1 << 1,
    T = 1 << 2,

    EC = E | C,
    ET = E | T,
    TC = T | C

};

struct ElectiveDiscipline
{
public:

    int id;
    char name[CONSTANTS::MAX_SIZE_NAME];
    double credits;
    Category category;
    TypeOfExam typesMask;

};

struct ElectiveDisciplineData
{
public:

    ElectiveDiscipline disciplines[CONSTANTS::MAX_COUNT_DISCIPLINES];
    int countOfDisciplines;

};

void writeDisciplineToFile(std::ofstream& file, const ElectiveDiscipline& d)
{

    file << d.id << " ";
    file << d.name << " ";
    file << d.credits << " ";
    file << (int)d.category << " ";
    file << (int)d.typesMask;
    file << std::endl;

}

void saveDataToFile(const char* fileName, const ElectiveDisciplineData& data)
{

    std::ofstream file(fileName);

    if (!file.is_open()) return;

    file << data.countOfDisciplines << std::endl;

    for (int i = 0; i < data.countOfDisciplines; i++)
    {

        writeDisciplineToFile(file, data.disciplines[i]);

    }

    file.close();

}

ElectiveDiscipline readDisciplineFromFile(std::ifstream& file)
{

    ElectiveDiscipline result;

    file >> result.id;
    file >> result.name;
    file >> result.credits;

    int number = 0;
    file >> number;

    switch (number)
    {

    case 0: result.category = Category::OKN; break;
    case 1: result.category = Category::M; break;
    case 2: result.category = Category::PM; break;
    case 3: result.category = Category::PR; break;
    default: result.category = Category::Other; break;

    }

    file >> number;

    if (number == CONSTANTS::MASK_E) result.typesMask = TypeOfExam::E;
    else if (number == CONSTANTS::MASK_C) result.typesMask = TypeOfExam::C;
    else if (number == CONSTANTS::MASK_T) result.typesMask = TypeOfExam::T;
    else if (number == CONSTANTS::MASK_EC) result.typesMask = TypeOfExam::EC;
    else if (number == CONSTANTS::MASK_ET) result.typesMask = TypeOfExam::ET;
    else if (number == CONSTANTS::MASK_TC) result.typesMask = TypeOfExam::TC;

    file.ignore(1);
    return result;

}

ElectiveDisciplineData readDataFromFile(const char* fileName)
{

    std::ifstream file(fileName);

    if (!file.is_open()) return {};

    ElectiveDisciplineData result;
    file >> result.countOfDisciplines;
    file.ignore(1);

    for (int i = 0; i < result.countOfDisciplines; i++)
    {

        result.disciplines[i] = readDisciplineFromFile(file);

    }

    file.close();
    return result;

}

void printDiscipline(const ElectiveDiscipline& d)
{

    std::cout << d.id << " " << d.name << " " << d.credits << " ";

    switch (d.category)
    {

    case Category::OKN: std::cout << "OKN ";; break;
    case Category::M: std::cout << "M "; break;
    case Category::PM: std::cout << "PM "; break;
    case Category::PR: std::cout << "PR "; break;
    default: std::cout << "Other "; break;

    }

    if ((int)d.typesMask == CONSTANTS::MASK_E) std::cout << "E ";
    else if ((int)d.typesMask == CONSTANTS::MASK_C) std::cout << "C ";
    else if ((int)d.typesMask == CONSTANTS::MASK_T) std::cout << "T ";
    else if ((int)d.typesMask == CONSTANTS::MASK_EC) std::cout << "EC ";
    else if ((int)d.typesMask == CONSTANTS::MASK_ET) std::cout << "ET ";
    else if ((int)d.typesMask == CONSTANTS::MASK_TC) std::cout << "TC ";

    std::cout << std::endl;

}

void printData(const ElectiveDisciplineData& data)
{

    for (int i = 0; i < data.countOfDisciplines; i++)
    {

        printDiscipline(data.disciplines[i]);

    }

    std::cout << std::endl;

}

void addDiscipline(const ElectiveDiscipline& d, ElectiveDisciplineData& data) 
{

    if (data.countOfDisciplines == 50) return;

    bool found = false;

    for (int i = 0; i < data.countOfDisciplines; i++)
    {

        if (data.disciplines[i].id == d.id)
        {

            data.disciplines[i] = d;
            found = true;

        }

    }

    if (!found) 
    {

        data.disciplines[data.countOfDisciplines] = d;
        data.countOfDisciplines += 1;

    }

}

void removeDisciplineById(int id, ElectiveDisciplineData& data)
{

    int index = -1;

    for (int i = 0; i < data.countOfDisciplines; i++)
    {

        if (data.disciplines[i].id == id)
        {

            index = i;
            break;

        }

    }

    if (index != -1)
    {

        for (int i = index; i < data.countOfDisciplines - 1; i++)
        {

            data.disciplines[i] = data.disciplines[i + 1];

        }

        data.countOfDisciplines -= 1;

    }

    std::cout << std::endl;

}

void printDisciplineById(int id, const ElectiveDisciplineData& data) 
{

    for (int i = 0; i < data.countOfDisciplines; i++)
    {

        if (data.disciplines[i].id == id) printDiscipline(data.disciplines[i]);

    }

    std::cout << std::endl;

}

void printDisciplineByCategory(Category category, const ElectiveDisciplineData& data)
{

    for (int i = 0; i < data.countOfDisciplines; i++)
    {

        if (data.disciplines[i].category == category) printDiscipline(data.disciplines[i]);

    }

}

void printDisciplineByCredits(double min, double max, const ElectiveDisciplineData& data)
{

    for (int i = 0; i < data.countOfDisciplines; i++)
    {

        if (data.disciplines[i].credits >= min && data.disciplines[i].credits <= max) printDiscipline(data.disciplines[i]);

    }

}

int main()
{

    ElectiveDiscipline d1 = { 1, "SDA", 5, Category::OKN, TypeOfExam::ET };
    ElectiveDiscipline d2 = { 2, "PYTHON",7.5, Category::PM, TypeOfExam::TC };
    ElectiveDiscipline d3 = { 3, "OOP", 9, Category::Other, TypeOfExam::C };

    ElectiveDisciplineData data = { {d1, d2, d3}, 3 };

    saveDataToFile("../test1.txt", data);
    ElectiveDisciplineData newData = readDataFromFile("../test1.txt");
    printData(newData);

    ElectiveDiscipline d4 = { 3, "YES", 0, Category::Other, TypeOfExam::C };
    ElectiveDiscipline d5 = { 4, "NZ", 2.5, Category::M, TypeOfExam::E };

    addDiscipline(d4, data);
    addDiscipline(d5, data);
    printData(data);

    removeDisciplineById(1, data);
    printData(data);

    printDisciplineById(3, data);
    printDisciplineByCategory(Category::M, data);
    printDisciplineByCredits(2.5, 7.5, data);

    return 0;

}
