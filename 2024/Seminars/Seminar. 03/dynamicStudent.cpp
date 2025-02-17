#include <iostream>
#include <fstream>
#include <cstring>

#pragma warning(disable : 4996)

struct DynamicStudent 
{

    char* name = nullptr;
    int age = 0;
    int fn = 0;

};

DynamicStudent init(const char* name, int age, int fn) 
{

    DynamicStudent toReturn;

    if (name == nullptr || age == 0 || fn == 0) 
    {

        return toReturn;

    }

    toReturn.name = new char[strlen(name) + 1];
    strcpy(toReturn.name, name);
    toReturn.age = age;
    toReturn.fn = fn;

    return toReturn;

}

void freeStudent(DynamicStudent& st)
{

    delete[] st.name;
    st.name = nullptr;
    st.age = 0;
    st.fn = 0;

}

void saveToBinaryFile(std::ofstream& os, const DynamicStudent& st) 
{

    int sizeOfName = strlen(st.name);

    os.write((const char*)(&sizeOfName), sizeof(int));
    os.write(st.name, sizeOfName);
    os.write((const char*)(&st.age), sizeof(int));
    os.write((const char*)(&st.fn), sizeof(int));

}

DynamicStudent readFromBinaryFile(std::ifstream& is) 
{

    DynamicStudent toReturn;

    int sizeOfName = 0;
    is.read((char*)(&sizeOfName), sizeof(int));

    toReturn.name = new char[sizeOfName + 1];
    is.read(toReturn.name, sizeOfName);
    toReturn.name[sizeOfName] = '\0';

    is.read((char*)(&toReturn.age), sizeof(int));
    is.read((char*)(&toReturn.fn), sizeof(int));

    return toReturn;

}

void printStudent(const DynamicStudent& st)
{

    std::cout << st.name << " " << st.age << " " << st.fn << std::endl;

}

void saveStudentsArrayToFile(DynamicStudent* students, std::ofstream& os, int size)
{

    if (students == nullptr || size < 0 || !os.is_open()) 
    {

        std::cout << "Error" << std::endl;

        return;
    }

    os.write((const char*)(&size), sizeof(int));

    for (int i = 0; i < size; i++) 
    {

        saveToBinaryFile(os, students[i]);

    }

}

DynamicStudent* readStudents(std::ifstream& is, int& size) 
{

    if (!is.is_open()) 
    {

        std::cout << "Error" << std::endl;
        return nullptr;

    }

    is.read((char*)(&size), sizeof(int));

    DynamicStudent* students = new DynamicStudent[size];

    for (int i = 0; i < size; i++) 
    {

        students[i] = readFromBinaryFile(is);

    }

    return students;

}

int main() 
{
   
    DynamicStudent students[] = 
    {

        init("Alice", 20, 12345),
        init("Bob", 21, 23456),
        init("Charlie", 22, 34567)

    };

    int numStudents = 3;

    std::ofstream outFile("students.dat", std::ios::binary);
    saveStudentsArrayToFile(students, outFile, numStudents);
    outFile.close();

    for (int i = 0; i < numStudents; i++) 
    {

        freeStudent(students[i]);

    }

    std::ifstream inFile("students.dat", std::ios::binary);
    int readSize;
    DynamicStudent* readStudentsArray = readStudents(inFile, readSize);
    inFile.close();

    for (int i = 0; i < readSize; i++) 
    {

        printStudent(readStudentsArray[i]);
        freeStudent(readStudentsArray[i]); 

    }

    delete[] readStudentsArray;

    return 0;

}
