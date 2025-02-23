#include <cstring>
#include <fstream>
#include <iostream>

enum class Major
{

    SI = 0,
    KN = 1,
    None = 2

};

struct Student
{
public:

    char name[15];
    int age;
    Major major;

};

int getFileSize(std::ifstream& file) 
{

    file.seekg(0, std::ios::end);
    int result = file.tellg();
    file.seekg(0, std::ios::beg);

    return result;

}

void writeStudent(const Student& st, std::ofstream& file) 
{

    file.write((const char*)&st, sizeof(Student));

}

Student readStudent(std::ifstream& file) 
{

    Student result;
    file.read((char*)&result, sizeof(Student));

    return result;

}

void writeGroupOfStudents(Student* students, int size, const char* fileName) 
{

    std::ofstream file(fileName, std::ios::binary);

    if (!file.is_open()) return;

    for (int i = 0; i < size; i++)
    {

        writeStudent(students[i], file);

    }

    file.close();

}

Student* readGroupOfStudents(const char* fileName) 
{

    std::ifstream file(fileName, std::ios::binary);

    if (!file.is_open()) return nullptr;

    int size = getFileSize(file);
    Student* result = new Student[size];

    for (int i = 0; i < size; i++)
    {

        result[i] = readStudent(file);

    }

    file.close();
    return result;

}

void printStudents(Student* students, int size) 
{

    for (int i = 0; i < size; i++)
    {

        std::cout << students[i].name << " ";
        std::cout << students[i].age << " ";
        std::cout << (int)students[i].major << std::endl;

    }

}

void free(Student* students) 
{

    delete[] students->name;
    students->major = Major::None;
    students->age = -1;

}

int main()
{

    /*Student* students = new Student[3];
    
    strncpy(students[0].name, "Yoan", strlen("Yoan"));
    students[0].name[strlen("Yoan")] = '\0';
    students[0].age = 20;
    students[0].major = Major::SI;

    strncpy(students[1].name, "Ivo", strlen("Ivo"));
    students[1].name[strlen("Ivo")] = '\0';
    students[1].age = 21;
    students[1].major = Major::SI;

    strncpy(students[2].name, "Koki", strlen("Koki"));
    students[2].name[strlen("Koki")] = '\0';
    students[2].age = 20;
    students[2].major = Major::KN;*/

    //writeGroupOfStudents(students, 3, "../file.dat");

    Student* students = readGroupOfStudents("../file.dat");
    printStudents(students, 3);
    free(students);

    return 0;

}

