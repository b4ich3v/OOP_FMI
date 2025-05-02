#include <iostream>
#include <cstring>
#include <fstream>
#include "MyString.h"

enum class Stars
{

    ONE = 1,
    TWO = 2,
    THREE = 3,
    FOUR = 4,
    FIVE  = 5

};

struct PointStarTable 
{
public:

    int points = 0;
    Stars stars = Stars::ONE;
    bool hasPrevStar = false;

    bool canLevel(const PointStarTable& other) const
    {

        return other.points >= points && other.hasPrevStar;

    }

};

static PointStarTable staticTableDefault[5]
{

    {1, Stars::ONE, false},
    {256, Stars::TWO, true},
    {512, Stars::THREE, true},
    {1024, Stars::FOUR, true},
    {2048, Stars::FIVE, true}

};

static PointStarTable staticTablePremium[5]
{

    {1, Stars::ONE, false},
    {256, Stars::TWO, true},
    {256, Stars::THREE, true},
    {256, Stars::FOUR, true},
    {256, Stars::FIVE, true}

};

class Player 
{
private:

    int id = 0;
    static int maskId;
    int points;
    Stars stars;

public:

    Player() 
    {
       
        stars = Stars::ONE;
        points = 0;
        id = maskId;

        maskId += 1;

    }

    int getId() const 
    {

        return id;

    }

    int getPointsCop() const 
    {

        return points;

    }

    int& getPointsRef()
    {

        return points;

    }

    Stars getStartsCop() const 
    {

        return stars;

    }

    Stars& getStartsRef()
    {

        return stars;

    }

    virtual bool levelUp()
    {

        std::cout << "Enter wanted level: " << std::endl;

        int number = 0;
        std::cin >> number;
        Stars input = (Stars)number;

        PointStarTable table = { points, input, (int)stars + 1 == (int)input };

        for (int i = 0; i < 5; i++)
        {

            if (staticTableDefault[i].canLevel(table)) 
            {

                stars = (Stars)((int)stars + 1);
                points -= staticTableDefault[i].points;
                return true;

            }

        }

        return false;

    }

    virtual ~Player() = default;

};

int Player::maskId = 0;

class Guest: public Player
{
private:

    int leftTime = 0;

public:

    Guest(int leftTime) : Player() { this->leftTime = leftTime; };

    bool levelUp() override 
    {

        return false;

    }

};

class LoggedPlayer: public Player
{
private:

    char password[9];
    int id = 0;

public:

    LoggedPlayer(const char* password) : Player() 
    {

        if (strlen(password) > 8) throw std::logic_error("Error");

        this->id = getId();
        strncpy(this->password, password, strlen(password));
        this->password[strlen(password)] = '\0';

    }

    bool levelUp() override
    {

        std::cout << "Enter wanted level: " << std::endl;

        int number = 0;
        std::cin >> number;
        Stars input = (Stars)number;

        PointStarTable table = { getPointsCop(), input, (int)getStartsCop() + 1 == (int)input};

        for (int i = 0; i < 5; i++)
        {

            if (staticTableDefault[i].canLevel(table))
            {

                getStartsRef() = (Stars)((int)getStartsCop() + 1);
                getPointsRef() -= staticTableDefault[i].points;
                return true;

            }

        }

        return false;

    }

};

class PremiumPlayer: public Player 
{
private:

    char* name = nullptr;

    void free() 
    {

        delete[] name;
        name = nullptr;

    }

    void copyFrom(const PremiumPlayer& other) 
    {

        this->name = new char[strlen(other.name) + 1];
        strncpy(this->name, other.name, strlen(other.name));
        this->name[strlen(other.name)] = '\0';

    }

    void moveTo(PremiumPlayer&& other) 
    {

        this->name = other.name;
        other.name = nullptr;
        
    }

public:

    PremiumPlayer(const char* name): Player() 
    {

        if (!name) throw std::logic_error("Error");

        this->name = new char[strlen(name) + 1];
        strncpy(this->name, name, strlen(name));
        this->name[strlen(name)] = '\0';

    }

    PremiumPlayer(const PremiumPlayer& other): Player(other)
    {

        copyFrom(other);

    }

    PremiumPlayer(PremiumPlayer&& other) noexcept: Player(std::move(other))
    {

        moveTo(std::move(other));

    }

    PremiumPlayer& operator = (const PremiumPlayer& other) 
    {

        if (this != &other) 
        {

            Player::operator=(other);
            free();
            copyFrom(other);

        }

        return *this;

    }

    PremiumPlayer& operator = (PremiumPlayer&& other) noexcept
    {

        if (this != &other)
        {

            Player::operator=(std::move(other));
            free();
            moveTo(std::move(other));

        }

        return *this;

    }

    ~PremiumPlayer() 
    {

        free();

    }

    bool levelUp() override
    {

        std::cout << "Enter wanted level: " << std::endl;

        int number = 0;
        std::cin >> number;
        Stars input = (Stars)number;

        PointStarTable table = { getPointsCop(), input, (int)getStartsCop() + 1 == (int)input };

        for (int i = 0; i < 5; i++)
        {

            if (staticTablePremium[i].canLevel(table))
            {

                getStartsRef() = (Stars)((int)getStartsCop() + 1);
                getPointsRef() -= staticTablePremium[i].points;
                return true;

            }

        }

        return false;

    }

};

int main() 
{

    PremiumPlayer p1("Yoan Baychev");
    LoggedPlayer l1("12345678");
    Guest g1(30);

    p1.getPointsRef() = 300;
    l1.getPointsRef() = 300;

    p1.levelUp();  
    l1.levelUp();
    g1.levelUp();  

    return 0;

}


