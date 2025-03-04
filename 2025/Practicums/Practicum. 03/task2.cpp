#include <iostream>
#include <fstream>
#include <cstring>

namespace CONSTANTS
{

    const int CLIENT_NAME_MAX_SIZE = 51;
    const int PHONE_NUMBER_MAX_SIZE = 21;
    const int ADDRESS_MAX_SIZE = 101;

}

enum class TypeOfPizza
{

    MARGARITA = 0,
    CHICAGO = 1,
    CREEK = 2

};

enum class SizeOfPizza
{

    S = 0,
    M = 1,
    L = 2

};

struct Pizza
{
public:


    TypeOfPizza type;
    SizeOfPizza size;
    double price;

};

struct ClientInfo
{
public:

    char clientName[CONSTANTS::CLIENT_NAME_MAX_SIZE];
    char phoneNumber[CONSTANTS::PHONE_NUMBER_MAX_SIZE];
    char address[CONSTANTS::ADDRESS_MAX_SIZE];

};

struct Order
{
public:

    Pizza* ps;
    int countOfPs;
    ClientInfo info;
    double price;

};

void printPizza(const Pizza& pizza)
{

    switch (pizza.type)
    {

    case TypeOfPizza::MARGARITA: std::cout << "MARGARITA "; break;
    case TypeOfPizza::CHICAGO: std::cout << "CHICAGO "; break;
    case TypeOfPizza::CREEK: std::cout << "CREEK "; break;
    default: break;

    }

    switch (pizza.size)
    {

    case SizeOfPizza::S: std::cout << "S "; break;
    case SizeOfPizza::M: std::cout << "M "; break;
    case SizeOfPizza::L: std::cout << "L "; break;
    default: break;

    }

    std::cout << pizza.price << std::endl;

}

void printClientInfo(const ClientInfo& info)
{

    std::cout << info.clientName << " ";
    std::cout << info.phoneNumber << " ";
    std::cout << info.address << std::endl;

}

void printOrder(const Order& order)
{

    for (int i = 0; i < order.countOfPs; i++)
    {

        printPizza(order.ps[i]);

    }

    printClientInfo(order.info);
    std::cout << order.price << std::endl;

}

void writeOrderToFile(const char* fileName, const Order& order)
{

    std::ofstream file(fileName, std::ios::binary);

    if (!file.is_open()) return;

    file.write((const char*)&order.countOfPs, sizeof(int));
    file.write((const char*)order.ps, order.countOfPs * sizeof(Pizza));

    file.write((const char*)order.info.clientName, sizeof(order.info.clientName));
    file.write((const char*)order.info.phoneNumber, sizeof(order.info.phoneNumber));
    file.write((const char*)order.info.address, sizeof(order.info.address));
    file.write((const char*)&order.price, sizeof(double));

    file.close();

}

Order readOrderFromFile(const char* fileName)
{

    std::ifstream file(fileName, std::ios::binary);

    if (!file.is_open()) return {};

    Order result;

    file.read((char*)&result.countOfPs, sizeof(int));
    result.ps = new Pizza[result.countOfPs];
    file.read((char*)result.ps, result.countOfPs * sizeof(Pizza));

    file.read((char*)result.info.clientName, sizeof(result.info.clientName));
    file.read((char*)result.info.phoneNumber, sizeof(result.info.phoneNumber));
    file.read((char*)result.info.address, sizeof(result.info.address));
    file.read((char*)&result.price, sizeof(double));

    file.close();
    return result;

}

int main()
{

    Pizza* ps = new Pizza[3];
    ps[0] = { TypeOfPizza::MARGARITA, SizeOfPizza::S, 5.00 };
    ps[1] = { TypeOfPizza::CHICAGO, SizeOfPizza::L, 7.50 };
    ps[2] = { TypeOfPizza::CREEK, SizeOfPizza::M, 6.00 };

    ClientInfo info = { "Yoan Baychev", "087...", "Pernik" };
    Order order = { ps, 3, info, ps[0].price + ps[1].price + ps[2].price };

    printOrder(order);
    writeOrderToFile("../file.dat", order);
    Order result = readOrderFromFile("../file.dat");
    printOrder(result);

    delete[] ps;
    return 0;

}
