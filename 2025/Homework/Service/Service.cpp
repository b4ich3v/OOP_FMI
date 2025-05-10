#include "Service.h"

Service& Service::instance()
{

    static Service inst;
    return inst;

}

void Service::loadAll() 
{

    loadUsers();
    loadCourses();
    loadAssignments();
    loadSubmissions();
    loadGrades();
    loadMessages();

}

void Service::saveAll() const
{

    saveUsers();
    saveCourses();
    saveAssignments();
    saveSubmissions();
    saveGrades();
    saveMessages();

}

void Service::saveUsers() const 
{

    std::ofstream file("users.day", std::ios::binary);
    const auto& users = Admin::getAllUsers();

    size_t countOfUsers = users.size();
    file.write((const char*)(&countOfUsers), sizeof(countOfUsers));

    auto writeMyString = [&](const MyString& str) 
    {

        int len = str.size();
        file.write((const char*)(&len), sizeof(len));
        file.write(str.getData(), len);

    };

    for (size_t i = 0; i < countOfUsers; i++) 
    {

        User* currentUser = users[i].get();

        int id = currentUser->getId();
        file.write((const char*)(&id), sizeof(id));

        int typeVal = (int)(currentUser->getType());
        file.write((const char*)(&typeVal), sizeof(typeVal));

        writeMyString(currentUser->getFirstName());
        writeMyString(currentUser->getLastName());
        writeMyString(currentUser->getPassword());

    }

}

void Service::loadUsers() 
{

    std::ifstream file("users.dat", std::ios::binary);
    if (!file) return;  

    size_t countOfUsers = 0;
    file.read((char*)(&countOfUsers), sizeof(countOfUsers));

    auto readMyString = [&](std::ifstream& in) 
    {

        int len = 0;
        in.read((char*)(&len), sizeof(len));
        char* buffer = new char[len];
        in.read((char*)buffer, len);
        MyString result(buffer);
        delete[] buffer;

        return result;

    };

    for (size_t i = 0; i < countOfUsers; i++)
    {

        int id = 0;
        int typeValue = 0;

        file.read((char*)(&id), sizeof(id));
        file.read((char*)(&typeValue), sizeof(typeValue));

        MyString firstName = readMyString(file);
        MyString lastName = readMyString(file);
        MyString password = readMyString(file);

        switch ((Type)(typeValue)) 
        {

        case Type::ADMIN: 
        {

            new Admin(id, firstName, lastName, password);
            break;

        }
        case Type::TEACHER: 
        {

            Teacher* teacher = new Teacher(firstName, lastName, password);
            teacher->setId(id);
            break;

        }
        case Type::STUDENT: 
        {

            Student* student = new Student(firstName, lastName, password);
            student->setId(id);
            break;

        }
        default: break;
             
        }

    }

}
