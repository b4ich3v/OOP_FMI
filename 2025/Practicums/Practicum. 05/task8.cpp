#include <iostream>
#include <cstring>

namespace HELPERS 
{

	const int MAX_SIZE_SHIPS = 30;

}

enum class ClassOfShip
{

	battleship = 0,
	battlecruiser = 1

};

class Ship
{
private:

	char* name = nullptr;
	int yearOfLaunch = 1900;
	ClassOfShip classOfShip = ClassOfShip::battlecruiser;
	int countOfGuns = 0;

	void setName(const char* name) 
	{

		if (!name) return;

		this->name = new char[strlen(name) + 1];
		strncpy(this->name, name, strlen(name));
		this->name[strlen(name)] = '\0';

	}

	void setCountOfGuns(int countOfGuns) 
	{

		if (countOfGuns < 0) return;

		this->countOfGuns = countOfGuns;

	}

	void setYearOfLaunch(int yearOfLaunch) 
	{

		if (yearOfLaunch < 0) return;

		this->yearOfLaunch = yearOfLaunch;

	}

	void setClassofShip(ClassOfShip classOfShip) 
	{

		this->classOfShip = classOfShip;

	}

	void free() 
	{

		delete[] name;
		name = nullptr;

		countOfGuns = 0;
		yearOfLaunch = 0;
		classOfShip = ClassOfShip::battleship;

	}

	void copyFrom(const Ship& other) 
	{

		name = new char[strlen(other.name) + 1];
		strncpy(name, other.name, strlen(other.name));
		name[strlen(other.name)] = '\0';

		yearOfLaunch = other.yearOfLaunch;
		countOfGuns = other.countOfGuns;
		classOfShip = other.classOfShip;

	}

public:

	Ship() = default;

	Ship(const char* name, int countOfGuns, int yearOfLaunch, ClassOfShip classOfShip) 
	{

		setName(name);
		setCountOfGuns(countOfGuns);
		setYearOfLaunch(yearOfLaunch);
		setClassofShip(classOfShip);
		
	}

	Ship(const Ship& other)
	{

		copyFrom(other);

	}

	Ship& operator = (const Ship& other) 
	{

		if (this != &other) 
		{

			free();
			copyFrom(other);

		}

		return *this;

	}

	~Ship() 
	{

		free();

	}

	const char* getName() const 
	{

		return name;

	}

	int getYearOfLaunch() const 
	{

		return yearOfLaunch;

	}

	int getCountOfGuns() const 
	{

		return countOfGuns;

	}

	ClassOfShip getClassOfShip() const 
	{

		return classOfShip;

	}

	void printShip() const
	{

		std::cout << name << " ";
		std::cout << yearOfLaunch << " ";
		std::cout << countOfGuns << " ";

		switch (classOfShip)
		{

		case ClassOfShip::battleship: std::cout << "battleship"; break;
		case ClassOfShip::battlecruiser: std::cout << "battlecruiser"; break;
		default: break;
			
		}

		std::cout << std::endl;

	}

};

class Navy
{
private:

	char* countryName = nullptr;
	Ship ships[HELPERS::MAX_SIZE_SHIPS];
	int countOfShips = 0;

	void copyFrom(const Navy& other) 
	{

		countryName = new char[strlen(other.countryName) + 1];
		strncpy(countryName, other.countryName, strlen(other.countryName));
		countryName[strlen(other.countryName)] = '\0';

		countOfShips = other.countOfShips;

		for (int i = 0; i < countOfShips; i++)
		{

			ships[i] = other.ships[i];

		}

	}

	void free()
	{

		delete[] countryName;
		countryName = nullptr;
		countOfShips = 0;

	}

public:

	Navy() = default;

	Navy(const Navy& other) 
	{

		copyFrom(other);

	}

	Navy& operator = (const Navy& other) 
	{

		if (this != &other) 
		{

			free();
			copyFrom(other);

		}

		return *this;

	}

	~Navy() 
	{

		free();

	}

	void addShip(const Ship& ship) 
	{

		if (countOfShips == HELPERS::MAX_SIZE_SHIPS) return;

		ships[countOfShips] = ship;
		countOfShips += 1;

	}

	void removeShipe(const char* name) 
	{

		for (int i = 0; i < countOfShips; i++)
		{

			if (!strcmp(ships[i].getName(), name)) 
			{

				std::swap(ships[i], ships[countOfShips - 1]);
				countOfShips -= 1;
				break;

			}

		}

	}

	const Ship* const getShipPtrByIndex(int index) 
	{

		if (index < 0 || index >= countOfShips) return nullptr;

		Ship* ptrShip = &ships[index];
		return ptrShip;

	}

	int getCountOfShips() const 
	{

		return countOfShips;

	}

	int getTotalCountOfGuns() const 
	{

		int result = 0;

		for (int i = 0; i < countOfShips; i++)
		{

			result += ships[i].getCountOfGuns();

		}

		return result;

	}

	int compareByCountOfGuns(const Navy& other) const 
	{

		if (getTotalCountOfGuns() < other.getTotalCountOfGuns()) return -1;
		else if (getTotalCountOfGuns() > other.getTotalCountOfGuns()) return 1;
		else return 0;

	}

	void printNavy() const 
	{

		for (int i = 0; i < countOfShips; i++)
		{

			ships[i].printShip();

		}

		std::cout << std::endl;

	}

};

int main() 
{

	Ship ship1("Black Pearl", 30, 341, ClassOfShip::battleship);
	Ship ship2("Silent death", 38, 1891, ClassOfShip::battleship);
	Ship ship3("Vin Dieasel", 0, 2014, ClassOfShip::battlecruiser);

	Ship ship4("Yoan Baychev", 30, 341, ClassOfShip::battleship);
	Ship ship5("Ivo Kunchev", 38, 1891, ClassOfShip::battleship);
	Ship ship6("Ilian Zaprqnov", 576, 201, ClassOfShip::battleship);
	Ship ship7("Kaloyan Markov", 891, 14, ClassOfShip::battlecruiser);
	Ship ship8("Tugay Kafa", 131, 786, ClassOfShip::battleship);

	ship1.printShip();
	ship2.printShip();
	ship3.printShip();

	Navy navy1;
	navy1.addShip(ship1);
	navy1.addShip(ship2);
	navy1.addShip(ship3);
	navy1.printNavy();

	Navy navy2;
	navy2.addShip(ship4);
	navy2.addShip(ship5);
	navy2.addShip(ship6);
	navy2.addShip(ship7);
	navy2.addShip(ship8);
	navy2.printNavy();

	std::cout << std::endl;
	navy2.removeShipe("Ivo Kunchev");
	navy2.printNavy();

	std::cout << navy1.compareByCountOfGuns(navy2);

	return 0;

}
