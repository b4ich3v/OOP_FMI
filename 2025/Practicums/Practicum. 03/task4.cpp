#include <iostream>
#include <fstream>

namespace HELPERS
{

	const int NAME_MAX_SIZE = 24;
	const int NAME_COUNT_FINES = 20;

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

enum class Brand
{

	AUDI = 0,
	BMW = 1,
	MERCEDES = 2

};

struct Car
{
public:

	Brand brand;
	char name[HELPERS::NAME_MAX_SIZE + 1];
	double speed;
	double fines[HELPERS::NAME_COUNT_FINES];
	int countOfFines;

};

double sumOfAllFinesOfCar(const Car& car)
{

	double result = 0;

	for (int i = 0; i < car.countOfFines; i++)
	{

		result += car.fines[i];

	}

	return result;

}

void addFind(double newFine, Car& car)
{

	if (car.countOfFines == HELPERS::NAME_COUNT_FINES) return;

	car.fines[car.countOfFines] = newFine;
	car.countOfFines += 1;

}

void printCar(const Car& car)
{

	switch (car.brand)
	{

	case Brand::AUDI: std::cout << "AUDI "; break;
	case Brand::BMW: std::cout << "BMW "; break;
	case Brand::MERCEDES: std::cout << "MERCEDES "; break;
	default: break;

	}

	std::cout << car.name << " ";
	std::cout << car.speed << " ";

	for (int i = 0; i < car.countOfFines; i++)
	{

		std::cout << car.fines[i] << " ";

	}

	std::cout << std::endl;

}

void printCars(Car* cars, int countOfCars)
{

	for (int i = 0; i < countOfCars; i++)
	{

		printCar(cars[i]);

	}

}

void writeCarToBinaryFile(const char* fileName, const Car& car)
{

	if (!fileName) return;

	std::ofstream file(fileName, std::ios::binary);

	if (!file.is_open()) return;

	file.write((const char*)&car, sizeof(Car));
	file.close();

}

Car readCarFromBinaryFile(const char* fileName)
{

	if (!fileName) return {};

	std::ifstream file(fileName, std::ios::binary);

	if (!file.is_open()) return{};

	Car result;

	file.read((char*)&result, sizeof(Car));
	file.close();

	return result;

}

void writeCarsToBinaryFile(const char* fileName, Car* cars, int countOfCars)
{

	if (!fileName) return;

	std::ofstream file(fileName, std::ios::binary);

	if (!file.is_open()) return;

	file.write((const char*)cars, sizeof(Car) * countOfCars);
	file.close();

}

Car* readCarsFromBinaryFile(const char* fileName)
{

	if (!fileName) return {};

	std::ifstream file(fileName, std::ios::binary);

	if (!file.is_open()) return {};

	int size = HELPERS::getFileSize(file) / sizeof(Car);
	Car* result = new Car[size];

	file.read((char*)result, size * sizeof(Car));
	file.close();

	return result;

}

int main()
{

	Car car1 = { Brand::AUDI, "Yoan", 300, {},0 };
	Car car2 = { Brand::BMW, "Yoan", 300, {1, 2, 3, 4, 5},5 };
	Car car3 = { Brand::MERCEDES, "Yoan", 300, {},0 };

	Car* cars = new Car[3];
	cars[0] = car1;
	cars[1] = car2;
	cars[2] = car3;
	printCars(cars, 3);
	std::cout << std::endl;

	writeCarsToBinaryFile("../file.dat", cars, 3);
	Car* newCars = readCarsFromBinaryFile("../file.dat");
	printCars(newCars, 3);

	delete[] cars;
	delete[] newCars;

	return 0;

}
