#include <iostream>
#include <cstring>

namespace HELPERS
{

    const int POINTS_TO_WIN = 150;
    const double PERCENTAGE_FOR_CHARITY = 0.02;
    const double PERCENTAGE_FOR_WIN = 0.01;

    double getPercentageFrom(double target, double percentage) 
    {

        return percentage * target;

    }

}

class SoftwareEngineer
{
private:

    char* name = nullptr;
    char* position = nullptr;
    double salary = 0;

    void setName(const char* name)
    {

        if (!name || this->name == name) return;

        this->name = new char[strlen(name) + 1];
        strncpy(this->name, name, strlen(name));
        this->name[strlen(name)] = '\0';

    }

    void setPosition(const char* position)
    {

        if(!position || this->position == position) return;

        this->position = new char[strlen(position) + 1];
        strncpy(this->position, position, strlen(position));
        this->position[strlen(position)] = '\0';

    }

    void setSalary(double salary) 
    {

        if (salary < 0) return;

        this->salary = salary;

    }

    void copyFrom(const SoftwareEngineer& other) 
    {

        setName(other.name);
        setPosition(other.position);
        setSalary(other.salary);

    }

    void free() 
    {

        delete[] name;
        delete[] position;
        name = nullptr;
        position = nullptr;

        salary = 0;

    }

public:

    SoftwareEngineer() = default;

    SoftwareEngineer(const char* name, const char* position, double salary) 
    {

        setName(name);
        setPosition(position);
        setSalary(salary);

    }

    SoftwareEngineer(const SoftwareEngineer& other) 
    {

        copyFrom(other);

    }

    SoftwareEngineer& operator = (const SoftwareEngineer& other)
    {

        if (this != &other) 
        {

            free();
            copyFrom(other);

        }

        return *this;

    }

    ~SoftwareEngineer() 
    {

        free();

    }

    void printSoftwareEngineer() const 
    {

        std::cout << name << " ";
        std::cout << position << " ";
        std::cout << salary << std::endl;

    }

    double getSalary() const 
    {

        return salary;

    }

};

struct Team 
{
public:

    SoftwareEngineer e1;
    SoftwareEngineer e2;

    double salaryOfBoth = e1.getSalary() + e2.getSalary();

    void printTeam() const 
    {

        e1.printSoftwareEngineer();
        e2.printSoftwareEngineer();
        std::cout << std::endl;

    }

};

struct ResultManager 
{
public:

    int pointsForTeam1 = 0;
    int pointsForTeam2 = 0;

    int winsForTeam1 = 0;
    int winsForTeam2 = 0;

};

class BelotTournament 
{
private:

    Team* teams = nullptr;
    int countOfTeams = 0;
    int capacity = 8;

    double sumForCharity = 0;
    double sumForWinners = 0;

    void resize(int newCapacity) 
    {

        if (newCapacity <= capacity) return;

        Team* newTeams = new Team[newCapacity];

        for (int i = 0; i < countOfTeams; i++)
        {

            newTeams[i] = teams[i];

        }

        delete[] teams;
        teams = newTeams;
        capacity = newCapacity;

    }

    void copyFrom(const BelotTournament& other) 
    {

        teams = new Team[other.capacity];

        for (int i = 0; i < other.countOfTeams; i++)
        {

            teams[i] = other.teams[i];

        }

        countOfTeams = other.countOfTeams;
        capacity = other.capacity;

    }

    void free() 
    {

        delete[] teams;
        teams = nullptr;
        countOfTeams = 0;
        capacity = 8;

    }

public:

    BelotTournament() 
    {

        countOfTeams = 0;
        capacity = 8;
        teams = new Team[capacity];

    }

    BelotTournament(const Team* teams, int countOfTeams) 
    {

        this->countOfTeams = countOfTeams;
        this->capacity = countOfTeams;
        this->teams = new Team[capacity];

        for (int i = 0; i < countOfTeams; i++)
        {

            this->teams[i] = teams[i];

        }

        if (countOfTeams % 2 == 1) removeTeam(countOfTeams - 1);

    }

    BelotTournament& operator = (const BelotTournament& other) 
    {

        if (this != &other) 
        {

            free();
            copyFrom(other);

        }

        return *this;

    }

    BelotTournament(const BelotTournament& other) 
    {

        copyFrom(other);

    }

    ~BelotTournament() 
    {

        free();

    }

    double getMoneyForCharity() const 
    {

        return sumForCharity;

    }

    void removeTeam(int index)
    {

        if (index < 0 || index >= countOfTeams || countOfTeams == 0) return;

        std::swap(teams[index], teams[countOfTeams - 1]);
        countOfTeams -= 1;

    }

    void addTeam(const Team& team) 
    {

        if (countOfTeams == capacity) resize(capacity * 2);

        teams[countOfTeams] = team;
        countOfTeams += 1;

    }

    void printTeams() const 
    {

        for (int i = 0; i < countOfTeams; i++)
        {

            teams[i].printTeam();

        }

        std::cout << std::endl;

    }

    void duel(int i, int j)
    {

        ResultManager manager;

        int counterForTeam1 = 0;
        int counterForTeam2 = 0;

        for (int i = 0; i < 3; i++)
        {

            std::cout << "Round " << i + 1 << std::endl;

            while (true)
            {

                std::cin >> counterForTeam1 >> counterForTeam2;

                manager.pointsForTeam1 += counterForTeam1;
                manager.pointsForTeam2 += counterForTeam2;

                if (manager.pointsForTeam1 >= HELPERS::POINTS_TO_WIN ||
                    manager.pointsForTeam2 >= HELPERS::POINTS_TO_WIN) break;

            }

            if (manager.pointsForTeam1 > manager.pointsForTeam2) manager.winsForTeam1 += 1;
            else manager.winsForTeam2 += 1;

            manager.pointsForTeam1 = 0;
            manager.pointsForTeam2 = 0;

        }

        std::cout << std::endl;

        if (manager.winsForTeam1 > manager.winsForTeam2) 
        {

            double sumForWinnersInThisRound = HELPERS::getPercentageFrom(teams[j].salaryOfBoth, HELPERS::POINTS_TO_WIN);
            sumForCharity += HELPERS::getPercentageFrom(teams[j].salaryOfBoth, HELPERS::PERCENTAGE_FOR_CHARITY);
            sumForWinners += sumForWinnersInThisRound;

            teams[j].salaryOfBoth -= sumForWinnersInThisRound;

            removeTeam(j);

        }
        else
        {

            double sumForWinnersInThisRound = HELPERS::getPercentageFrom(teams[i].salaryOfBoth, HELPERS::POINTS_TO_WIN);
            sumForCharity += HELPERS::getPercentageFrom(teams[i].salaryOfBoth, HELPERS::PERCENTAGE_FOR_CHARITY);
            sumForWinners += sumForWinnersInThisRound;

            teams[i].salaryOfBoth -= sumForWinnersInThisRound;

            removeTeam(i);

        }

    }

    void processTheTournament() 
    {

        int dummyParam = 1;

        while (countOfTeams > 1)
        {

            std::cout << "Duel number " << dummyParam << std::endl;
            dummyParam += 1;

            duel(0, 1);

        }

        std::cout << "The winning team is:" << std::endl;
        printTeams();

        std::cout << "Money for charity: " << sumForCharity << std::endl;
        std::cout << "Money for winning team: " << sumForWinners << std::endl;

    }

};

int main() 
{

    SoftwareEngineer e1("Yoan Baychev", "Pos1", 10000);
    SoftwareEngineer e2("Ivailo Kunchev", "Pos2", 8970);

    SoftwareEngineer e3("Kaloyan Markov", "Pos3", 15000);
    SoftwareEngineer e4("Ilian Zaprqnov", "Pos4", 1234);

    SoftwareEngineer e5("Nikola Topalov", "Pos5", 7689);
    SoftwareEngineer e6("Tugay Kafa", "Pos6", 9000);

    SoftwareEngineer e7("HACKER_1", "Pos7", 13690);
    SoftwareEngineer e8("HACKER_2", "Pos8", 1000);
    
    Team team1 = { e1, e2 };
    Team team2 = { e3, e4 };
    Team team3 = { e5, e6 };
    Team team4 = { e7, e8 };

    Team* teamsPtr1 = new Team[4];
    teamsPtr1[0] = team1;
    teamsPtr1[1] = team2;
    teamsPtr1[2] = team3;
    teamsPtr1[3] = team4;

    BelotTournament tournament(teamsPtr1, 4);
    tournament.printTeams();
    tournament.processTheTournament();

    delete[] teamsPtr1;
    return 0;

}
