#include "Person.h"

const int ID_SIZE = 10;

class Student: public Person
{
private:

    char id[ID_SIZE + 1] = "0MI060032";

public:

    Student() = default;

    Student(const char* name, int age, const char* id);

    const char* getStudentName() const;

    int getStudentAge() const;

    const char* getStudentId() const;

};

