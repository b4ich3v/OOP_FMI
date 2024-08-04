#include <iostream>
#include <fstream>
#include <cstring>

#pragma warning(disable:4996)
const int STUDENTS_MAX_SIZE = 10;

enum Major
{

    Undefined,
    Informatics,
    ComputerScience,
    Mathematics,
    SoftwareEngineering

};

const char* getMajorStr(Major major)
{

    switch (major)
    {

    case Major::Informatics: return "INF";
    case Major::ComputerScience: return "CS";
    case Major::Mathematics: return "MATH";
    case Major::SoftwareEngineering: return "SE";
    default: return "Undefined";

    }

}

struct Student
{

    char name[100] = "";
    unsigned int fn = 0;
    Major major = Major::Undefined;

};

void printStudent(const Student& student)
{

    std::cout << student.name << " " << student.fn << " " << getMajorStr(student.major) << std::endl;

}

struct StudentDatabase
{

    unsigned studentsCount = 0;
    Student students[STUDENTS_MAX_SIZE];

};

Student readStudent(std::ifstream& file)
{

    Student student;

    file.getline(student.name, 100);
    file >> student.fn;

    char majorString[10];
    file >> majorString;

    if (strcmp(majorString, "INF") == 0)
    {

        student.major = Major::Informatics;

    }
    else if (strcmp(majorString, "CS") == 0)
    {

        student.major = Major::ComputerScience;

    }
    else if (strcmp(majorString, "MATH") == 0)
    {

        student.major = Major::Mathematics;

    }
    else if (strcmp(majorString, "SE") == 0) 
    {

        student.major = Major::SoftwareEngineering;

    }
    else 
    {

        student.major = Major::Undefined;

    }
        
    file.ignore();
    return student;

}

void saveStudent(std::ofstream& file, const Student& student)
{

    file << student.name << "\n"
        << student.fn << "\n"
        << getMajorStr(student.major) << "\n";

}

void saveDatabase(const char* fileName, const StudentDatabase& data)
{

    std::ofstream file(fileName);

    if (!file.is_open())
    {

        std::cout << "Error opening file for writing." << std::endl;
        return;

    }

    file << data.studentsCount << "\n";

    for (unsigned i = 0; i < data.studentsCount; i++)
    {

        saveStudent(file, data.students[i]);

    }

}

void readDatabase(const char* fileName, StudentDatabase& db)
{

    std::ifstream file(fileName);

    if (!file.is_open())
    {

        std::cout << "Error opening file for reading." << std::endl;
        return;

    }

    file >> db.studentsCount;
    file.ignore(); 

    for (unsigned i = 0; i < db.studentsCount; i++)
    {

        db.students[i] = readStudent(file);

    }

}

int main()
{

    StudentDatabase data;
    data.studentsCount = 3;
    strcpy(data.students[0].name, "Alice");
    data.students[0].fn = 123;
    data.students[0].major = Major::Informatics;

    strcpy(data.students[1].name, "Bob");
    data.students[1].fn = 456;
    data.students[1].major = Major::Mathematics;

    strcpy(data.students[2].name, "Charlie");
    data.students[2].fn = 789;
    data.students[2].major = Major::SoftwareEngineering;

    saveDatabase("students.txt", data);


    StudentDatabase loadedDb;
    readDatabase("students.txt", loadedDb);

    for (int i = 0; i < loadedDb.studentsCount; i++)
    {

        printStudent(loadedDb.students[i]);

    }

    return 0;

}
