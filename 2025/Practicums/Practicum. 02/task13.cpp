#include <iostream>
#include <fstream>

struct City
{
public:

    char name[64];
    int countOfPeople;

};

struct District
{
public:

    City cities[20];
    int countOfCities;

};

void writeToFileCity(const City& city, std::ofstream& file)
{

    file << city.name << " ";
    file << city.countOfPeople << " ";

}

void writeToFileDistrict(const District& dis, const char* fileName)
{

    std::ofstream file(fileName);

    if (!file.is_open()) return;

    file << dis.countOfCities << " ";

    for (int i = 0; i < dis.countOfCities; i++)
    {

        writeToFileCity(dis.cities[i], file);

    }

    file.close();

}

City readFromFileCity(std::ifstream& file)
{

    City result;
    file >> result.name;
    file >> result.countOfPeople;

    return result;

}

District readFromFileDistrict(const char* fileName)
{

    std::ifstream file(fileName);

    if (!file.is_open()) return {};

    District result;
    file >> result.countOfCities;

    for (int i = 0; i < result.countOfCities; i++)
    {

        result.cities[i] = readFromFileCity(file);

    }

    return result;

}

void printCity(const City& city)
{

    std::cout << city.name << " ";
    std::cout << city.countOfPeople << std::endl;

}

void printDistrict(const District& dis)
{

    for (int i = 0; i < dis.countOfCities; i++)
    {

        printCity(dis.cities[i]);

    }

}

typedef bool (*predicate)(const City& d1, const City& d2);

void sortByPeople(District& dis, predicate function)
{

    for (int i = 0; i < dis.countOfCities - 1; i++)
    {

        for (int j = 0; j < dis.countOfCities - i - 1; j++)
        {

            if (function(dis.cities[j], dis.cities[j + 1]))
            {

                std::swap(dis.cities[j], dis.cities[j + 1]);

            }

        }

    }

}

bool min(const City& c1, const City& c2)
{

    return c1.countOfPeople > c2.countOfPeople;

}

int main()
{

    City c1 = { "Pernik", 1234 };
    City c2 = { "Sofia", 1234 };
    City c3 = { "Borino", 641 };
    City c4 = { "Plovdiv", 876 };
    City c5 = { "Dupnica", 1 };

    District dis = { {c1,c2,c3,c4,c5}, 5 };
    writeToFileDistrict(dis, "../test1.txt");
    District disResult = readFromFileDistrict("../test1.txt");
    printDistrict(disResult);

    std::cout << std::endl;

    sortByPeople(disResult, min);
    printDistrict(disResult);

    return 0;


}
