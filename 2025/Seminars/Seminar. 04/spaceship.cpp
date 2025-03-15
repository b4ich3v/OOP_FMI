#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <cstdint>

namespace HELPERS
{

    const int MAX_SIZE_BUFFER = 1024;

    int getFileSize(std::ifstream& file)
    {

        int currentPos = file.tellg();
        file.seekg(0, std::ios::end);
        int result = file.tellg();
        file.seekg(currentPos);
        file.clear();

        return result;

    }

}

class Spaceship
{
private:

    char* name = nullptr;
    double maxSpeed = 0;
    double capacity = 0;
    bool alreadyInFile = false;

    void setName(const char* name)
    {

        if (name == nullptr) return;

        this->name = new char[strlen(name) + 1];
        strncpy(this->name, name, strlen(name));
        this->name[strlen(name)] = '\0';

    }

    void setMaxSpeed(double maxSpeed)
    {

        if (maxSpeed < 0) return;

        this->maxSpeed = maxSpeed;

    }

    void setCapacity(double capacity)
    {

        if (capacity < 0) return;

        this->capacity = capacity;

    }

    void free()
    {

        delete[] name;
        name = nullptr;
        setCapacity(0);
        setMaxSpeed(0);

    }

    void copyFrom(const Spaceship& other)
    {

        capacity = other.capacity;
        maxSpeed = other.maxSpeed;

        char* newName = new char[strlen(other.name) + 1];
        strncpy(newName, other.name, strlen(other.name));
        newName[strlen(other.name)] = '\0';

        delete[] name;
        name = newName;

    }

    bool isAlreadyAllocated() const
    {

        return name != nullptr;

    }

public:

    Spaceship()
    {

        name = nullptr;
        maxSpeed = 0;
        capacity = 0;

    }

    Spaceship(const char* name, double maxSpeed, double capacity)
    {

        setName(name);
        setMaxSpeed(maxSpeed);
        setCapacity(capacity);

    }

    Spaceship(const Spaceship& other)
    {

        copyFrom(other);

    }

    Spaceship& operator = (const Spaceship& other)
    {

        if (this != &other)
        {

            free();
            copyFrom(other);

        }

        return *this;

    }

    ~Spaceship()
    {

        free();

    }

    const char* getName() const
    {

        return name;

    }

    int getCapacity() const
    {

        return capacity;

    }

    int getMaxSpeed() const
    {

        return maxSpeed;

    }

    void writeToFile(std::ofstream& file)
    {

        if (alreadyInFile) return;
        if (!file.is_open()) return;

        int sizeOfName = strlen(name);

        file.write((const char*)&sizeOfName, sizeof(int));
        file.write((const char*)name, sizeOfName);
        file.write((const char*)&maxSpeed, sizeof(double));
        file.write((const char*)&capacity, sizeof(double));

        alreadyInFile = true;

    }

    void readFromFile(std::ifstream& file)
    {

        if (!file.is_open()) return;

        if (isAlreadyAllocated()) free();

        int sizeOfName = 0;

        file.read((char*)&sizeOfName, sizeof(int));
        name = new char[sizeOfName + 1];
        file.read((char*)name, sizeOfName);
        name[sizeOfName] = '\0';
        file.read((char*)&maxSpeed, sizeof(double));
        file.read((char*)&capacity, sizeof(double));

    }

    void printSpaceship() const
    {

        std::cout << name << " ";
        std::cout << maxSpeed << " ";
        std::cout << capacity << std::endl;

    }

};

int main()
{

    //Spaceship sp1("Bravo 6", 1000, 100);
    //Spaceship sp2("Omega", 700, 85);
    //Spaceship sp3("Delta 78", 500, 10);

    //std::ofstream file("../file.dat", std::ios::binary | std::ios::app);

    //sp1.writeToFile(file);
    //sp2.writeToFile(file);
    //sp3.writeToFile(file);

    Spaceship sp1;
    Spaceship sp2;
    Spaceship sp3;

    std::ifstream file("../file.dat", std::ios::binary);

    sp1.readFromFile(file);
    sp2.readFromFile(file);
    sp3.readFromFile(file);

    sp1.printSpaceship();
    sp2.printSpaceship();
    sp3.printSpaceship();

    file.close();

    return 0;

}
