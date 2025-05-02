#include <iostream>
#include <cstring>
#include <fstream>
#include "MyString.h"

class Award 
{
private:

    double price = 0;
    int points = 0;

public:

    Award(double price, int points): price(price), points(points) {}

    double getPrice() const
    {

        return price;

    }

    int getPoints() const 
    {

        return points;

    }

    virtual void visualize() const = 0;

    virtual ~Award() = default;

};

class Penguin: public Award 
{
public:

    Penguin(double price): Award(price, 50) {}

    void visualize() const override 
    {

        std::cout << "Penguin" << std::endl;

    }

};

class Pacman: public Award
{
public:

    Pacman(double price) : Award(price, 150) {}

    void visualize() const override
    {

        std::cout << "Pacman" << std::endl;

    }

};

class ComputerBoy : public Award
{
public:

    ComputerBoy(double price) : Award(price, 500) {}

    void visualize() const override
    {

        std::cout << "ComputerBoy" << std::endl;

    }

};

class Squidward: public Award
{
public:

    Squidward(double price): Award(price, 1000) {}

    void visualize() const override
    {

        std::cout << "Squidward" << std::endl;

    }

};

class Sylvester: public Award
{
public:

    Sylvester(double price) : Award(price, 1500) {}

    void visualize() const override
    {

        std::cout << "Sylvester" << std::endl;

    }

};

int main() 
{

    Award* awards[] = 
    {

        new Penguin(9.99),
        new Pacman(14.99),
        new ComputerBoy(29.99),
        new Squidward(49.99),
        new Sylvester(59.99)

    };

    for (int i = 0; i < 5; i++) 
    {

        awards[i]->visualize();
        std::cout << awards[i]->getPrice()
            << " " << awards[i]->getPoints() << std::endl;

    }

    for (int i = 0; i < 5; i++) delete awards[i];

    return 0;

}




