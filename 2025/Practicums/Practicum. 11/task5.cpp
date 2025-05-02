#include <iostream>
#include <cstring>
#include <fstream>
#include "MyString.h"

class Computer 
{
private:

    double powerProcessor = 0;
    char* model = nullptr;
    int powerSuply = 0;
    int ram = 0;

    void free() 
    {

        delete[] model;
        model = nullptr;
        ram = 0;
        powerProcessor = 0;
        powerSuply = 0;

    }

    void copyFrom(const Computer& other) 
    {

        this->powerProcessor = other.powerProcessor;
        this->model = new char[strlen(other.model) + 1];
        strncpy(this->model, other.model, strlen(other.model));
        this->model[strlen(other.model)] = '\0';
        this->powerSuply = other.powerSuply;
        this->ram = other.ram;

    }

    void moveTo(Computer&& other) 
    {

        this->powerProcessor = other.powerProcessor;
        this->model = other.model;
        this->powerSuply = other.powerSuply;
        this->ram = other.ram;

        other.powerProcessor = 0;
        other.model = nullptr;
        other.powerSuply = 0;
        other.ram = 0;

    }

public:

    Computer() = default;

    Computer(double powerProcessor, const char* model, int powerSuply, int ram) 
    {

        if (powerProcessor < 0 || !model ||
            powerSuply < 0 || ram < 0) throw std::logic_error("Error");

        this->powerProcessor = powerProcessor;
        this->model = new char[strlen(model) + 1];
        strncpy(this->model, model, strlen(model));
        this->model[strlen(model)] = '\0';
        this->powerSuply = powerSuply;
        this->ram = ram;

    }

    Computer(const Computer& other) 
    {

        copyFrom(other);

    }

    Computer(Computer&& other) noexcept 
    {

        moveTo(std::move(other));

    }

    Computer& operator = (const Computer& other) 
    {

        if (this != &other) 
        {

            free();
            copyFrom(other);

        }

        return *this;

    }

    Computer& operator = (Computer&& other) noexcept
    {

        if (this != &other)
        {

            free();
            moveTo(std::move(other));

        }

        return *this;

    }

    virtual ~Computer() 
    {

        free();

    }

    double getPowerSupply() const
    {

        return powerProcessor;

    }

    const char* getModel() const 
    {

        return model;

    }

    int getPowerSuply() const
    {

        return powerSuply;

    }

    int getRam() const 
    {

        return ram;

    }

    virtual void printType() const = 0;

    virtual void printPeripheralDevices() const = 0;

};

class PC: public Computer 
{
public:

    PC(double powerProcessor, const char* model, int powerSuply, int ram):
        Computer(powerProcessor, model, powerSuply, ram) {}
    
    void printType() const override 
    {

        std::cout << "PC" << std::endl;

    }

    void printPeripheralDevices() const override 
    {

        std::cout << "Mouse, microphone and headphones" << std::endl;

    }

};

class Laptop: public Computer
{
public:

    Laptop(double powerProcessor, const char* model, int powerSuply, int ram) :
        Computer(powerProcessor, model, powerSuply, ram) {}

    void printType() const override
    {

        std::cout << "Laptop" << std::endl;

    }

    void printPeripheralDevices() const override
    {

        std::cout << "Mousepad, keyboard and monitor" << std::endl;

    }

};

class GamingConsole: public Computer
{
public:

    GamingConsole(double powerProcessor, const char* model, int powerSuply, int ram) :
        Computer(powerProcessor, model, powerSuply, ram) {}

    void printType() const override
    {

        std::cout << "GamingConsole " << std::endl;

    }

    void printPeripheralDevices() const override
    {

        std::cout << "Joystick and monitor" << std::endl;

    }

};

int main() 
{

    Computer* c1 = new PC(3.4, "Intel i5", 500, 16);
    Computer* c2 = new Laptop(2.8, "AMD Ryzen", 150, 8);
    Computer* c3 = new GamingConsole(3.2, "PlayStation 5", 200, 16);

    c1->printType();
    c1->printPeripheralDevices();

    c2->printType();
    c2->printPeripheralDevices();

    c3->printType();
    c3->printPeripheralDevices();

    delete c1;
    delete c2;
    delete c3;

    return 0;

}


