#include <iostream>
#include <cstring>

namespace HELPERS
{

    const int ONE_HUNDRED_KILOMETERS = 100;

}

class Trailer
{
private:

    double maxCargo = 0;
    double area = 0;
    double currentCargo = 0;

    void setArea(double area)
    {

        if (area >= 0) this->area = area;

    }

    void setMaxCargo(double maxCargo)
    {

        if (maxCargo >= 0) this->maxCargo = maxCargo;

    }

    void setCurrentCargo(double currentCargo)
    {

        if (currentCargo >= 0) this->currentCargo = currentCargo;

    }

public:

    Trailer() = default;

    Trailer(double maxCargo, double area, double currentCargo)
    {

        setArea(area);
        setMaxCargo(maxCargo);
        setCurrentCargo(currentCargo);

    }

    void addLoad(double weight)
    {

        if (currentCargo + weight < maxCargo) currentCargo += weight;
        else currentCargo = maxCargo;

    }

    double getArea() const
    {

        return area;

    }

    double getMaxCargo() const
    {

        return maxCargo;

    }

    double getCurrentCargo() const
    {

        return currentCargo;

    }

    void printTrailer() const
    {

        std::cout << maxCargo << " ";
        std::cout << area << " ";
        std::cout << currentCargo << std::endl;

    }

};

class Engine
{
private:

    double power = 0;
    double fuelConsumption = 0;
    double tankVolume = 0;
    double currentFuelLevel = 0;

    void setPower(double power)
    {

        if (power >= 0) this->power = power;

    }

    void setFuelConsumption(double fuelConsumption)
    {

        if (fuelConsumption >= 0) this->fuelConsumption = fuelConsumption;

    }

    void setTankVolume(double tankVolume)
    {

        if (tankVolume >= 0) this->tankVolume = tankVolume;

    }

    void setCurrentFuelLevel(double currentFuelLevel)
    {

        if (currentFuelLevel >= 0) this->currentFuelLevel = currentFuelLevel;

    }

public:

    Engine() = default;

    Engine(double power, double fuelConsumption, double tankVolume, double currentFuelLevel)
    {

        setPower(power);
        setFuelConsumption(fuelConsumption);
        setTankVolume(tankVolume);
        setCurrentFuelLevel(currentFuelLevel);

    }

    double getPower() const
    {

        return power;

    }

    double getFuelConsumption() const
    {

        return fuelConsumption;

    }

    double getTankVolume() const
    {

        return tankVolume;

    }

    double getCurrentFuelLevel() const
    {

        return currentFuelLevel;

    }

    void refuel(double liters)
    {

        if (liters + currentFuelLevel < tankVolume) currentFuelLevel += liters;

    }

    void drive(double km)
    {

        if (currentFuelLevel - (fuelConsumption / HELPERS::ONE_HUNDRED_KILOMETERS) * km <= 0)
        {

            this->currentFuelLevel = 0;
            return;

        }

        currentFuelLevel -= (fuelConsumption / HELPERS::ONE_HUNDRED_KILOMETERS) * km;

    }

    double getRemainingRange() const
    {

        return currentFuelLevel / (fuelConsumption / HELPERS::ONE_HUNDRED_KILOMETERS);

    }

    void printEngine() const
    {

        std::cout << power << " ";
        std::cout << fuelConsumption << " ";
        std::cout << tankVolume << " ";
        std::cout << currentFuelLevel << std::endl;

    }

};

class Truck
{
private:

    char* name = nullptr;
    double weight = 0;
    Trailer* trailer = nullptr;
    bool hasTrailerPred = false;
    Engine* engine = nullptr;

    void copyFrom(const Truck& other)
    {

        this->name = new char[strlen(other.name) + 1];
        strncpy(this->name, other.name, strlen(other.name));
        this->name[strlen(other.name)] = '\0';

        this->weight = other.weight;
        this->trailer = other.trailer;
        this->engine = other.engine;
        this->hasTrailerPred = other.hasTrailerPred;

    }

    void free()
    {

        delete[] name;
        name = nullptr;
        weight = 0;

    }

    void setName(const char* name)
    {

        if (name == nullptr) return;

        this->name = new char[strlen(name)];
        strncpy(this->name, name, strlen(name));
        this->name[strlen(name)] = '\0';

    }

    void setWeight(double weight)
    {

        if (weight > 0) this->weight = weight;

    }

    void setTrailer(Trailer* trailer)
    {

        this->trailer = trailer;

    }

    void setEngine(Engine* engine)
    {

        this->engine = engine;

    }

public:

    Truck() = default;

    Truck(const Truck& other)
    {

        copyFrom(other);

    }

    Truck(const char* name, double weight, Trailer* trailer, Engine* engine)
    {

        setName(name);
        setWeight(weight);
        setTrailer(trailer);
        setEngine(engine);
        this->hasTrailerPred = true;

    }

    Truck& operator = (const Truck& other)
    {

        if (this != &other)
        {

            free();
            copyFrom(other);

        }

        return *this;

    }

    ~Truck()
    {

        free();

    }

    const char* getName() const
    {

        return name;

    }

    double getWeight() const
    {

        return weight;

    }

    Trailer getTrailer() const
    {

        if(hasTrailerPred) return *trailer;

    }

    Engine getEngine() const
    {

        return *engine;

    }

    void attachTrailer(Trailer* trailer)
    {

        if (trailer == nullptr || this->trailer == trailer) return;

        this->trailer = trailer;
        this->hasTrailerPred = true;

    }

    bool hasTrailer() const
    {

        return hasTrailerPred;

    }

    void detachTrailer()
    {

        hasTrailerPred = false;
        trailer = nullptr;

    }

    void drive(double km)
    {

        (*engine).drive(km);

    }

    void loadTruck(double weight)
    {

        if (hasTrailerPred) (*trailer).addLoad(weight);

    }

    void changeEngine(Engine* newEngine)
    {

        this->engine = newEngine;

    }

    void printTruck() const
    {

        std::cout << name << " ";
        std::cout << weight << std::endl;
        if(trailer != nullptr) (*trailer).printTrailer();
        if(engine != nullptr) (*engine).printEngine();
        std::cout << std::endl;

    }

};

int main()
{

    Trailer t1(1000, 100, 800);
    Trailer t2(1000, 450, 400);
    Engine e1(300, 10, 100, 60);
    Engine e2(102, 7, 45, 37);

    Trailer* t1Ptr = &t1;
    Trailer* t2Ptr = &t2;
    Engine* e1Ptr = &e1;
    Engine* e2Ptr = &e2;

    Truck truck("The machine", 10000, t1Ptr, e1Ptr);
    truck.printTruck();
    truck.detachTrailer();

    truck.attachTrailer(t2Ptr);
    truck.printTruck();

    truck.drive(1000);
    truck.printTruck();

    truck.changeEngine(e2Ptr);
    truck.printTruck();

    truck.loadTruck(376);
    truck.printTruck();

    return 0;

}
