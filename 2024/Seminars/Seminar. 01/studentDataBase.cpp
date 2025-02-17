#include <iostream>
#include <assert.h>

const int STUDENTS_MAX_SIZE = 10;

enum Major
{

    Undefined,
    Informatics,
    ComputerScience,
    Mathematics,
    SoftwareЕngineering

};

enum class Criteria
{

    sortByName,
    sortByMajor,
    sortByFn

};

const char* getMajorStr(Major major)
{

    switch (major)
    {

    case Major::Informatics: return "INF";
    case Major::ComputerScience: return "CS";
    case Major::Mathematics: return "MATH";
    case Major::SoftwareЕngineering: return "SE";

    }

    return "";

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

void sortStudents(StudentDatabase& data)
{

    assert(data.studentsCount <= STUDENTS_MAX_SIZE);

}

void printDatabase(const StudentDatabase& data)
{

    assert(data.studentsCount <= STUDENTS_MAX_SIZE);

    for (int i = 0; i < data.studentsCount; i++)
    {

        printStudent(data.students[i]);

    }
       
}

void sortDatabase(StudentDatabase& database, bool(*isLess)(const Student& lhs, const Student& rhs))
{

    for (int i = 0; i < database.studentsCount - 1; i++)
    {

        int minIndex = i;

        for (int j = i + 1; j < database.studentsCount; j++)
        {

            if (isLess(database.students[j], database.students[minIndex]))
            {

                minIndex = j;

            }

        }

        if (i != minIndex) 
        {

            std::swap(database.students[i], database.students[minIndex]);

        }
          
    }
}

void sortByCriteria(StudentDatabase& data, Criteria criteria)
{

    switch (criteria)
    {

    case Criteria::sortByName: return sortDatabase(data, [](const Student& lhs, const Student& rhs) { return strcmp(lhs.name, rhs.name) < 0; });
    case Criteria::sortByMajor: return sortDatabase(data, [](const Student& lhs, const Student& rhs) { return lhs.major < rhs.major; });
    case Criteria::sortByFn: return sortDatabase(data, [](const Student& lhs, const Student& rhs) { return lhs.fn < rhs.fn; });

    }
}

int main()
{

    StudentDatabase s =
    {

        3,
        {

            {"Petur", 12, Major::Mathematics},
            {"Ivan", 12345, Major::ComputerScience},
            {"Aleksandur", 56, Major::SoftwareЕngineering}

        }

    };

    printDatabase(s);
    sortByCriteria(s, Criteria::sortByName);
    printDatabase(s);
    sortByCriteria(s, Criteria::sortByMajor);
    printDatabase(s);
    sortByCriteria(s, Criteria::sortByFn);
    printDatabase(s);

    return 0;

}
