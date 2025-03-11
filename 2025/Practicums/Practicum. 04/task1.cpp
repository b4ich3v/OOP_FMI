#include <iostream>
#include <fstream>
#include <cstring>

namespace CONSTANTS
{

	const int DEFAULT_SIZE_FOR_BRAND = 4;
	const int DEFAULT_MAX_SPEED = 300;
	const int DEFAULT_YEAR = 2014;

}

class Car
{
private:

	char* brand = nullptr;
	int year = CONSTANTS::DEFAULT_YEAR;
	double maxSpeed = CONSTANTS::DEFAULT_MAX_SPEED;
	int* kilometers = nullptr;
	int countOfTrips;

public:

	Car() : brand(nullptr), kilometers(nullptr), year(0), maxSpeed(0.0), countOfTrips(0) {}

	Car(const char* brand, int year, double maxSpeed, int* kilometers, int countOfTrips)
	{

		if (!brand || !kilometers || countOfTrips <= 0)
		{

			this->brand = new char[CONSTANTS::DEFAULT_SIZE_FOR_BRAND + 1];
			strncpy(this->brand, "None", CONSTANTS::DEFAULT_SIZE_FOR_BRAND);
			this->brand[CONSTANTS::DEFAULT_SIZE_FOR_BRAND] = '\0';

			this->kilometers = nullptr;
			this->maxSpeed = CONSTANTS::DEFAULT_MAX_SPEED;
			this->year = CONSTANTS::DEFAULT_YEAR;
			this->countOfTrips = countOfTrips;

		}
		else
		{

			setBrand(brand);
			setKilometers(kilometers, countOfTrips);
			setYear(year);
			setMaxSpeed(maxSpeed);

		}

	}

	~Car()
	{

		delete[] brand;
		delete[] kilometers;
		maxSpeed = 0;
		year = 0;

	}

	void setBrand(const char* brand)
	{

		if (this->brand) delete[] this->brand;

		this->brand = new char[strlen(brand) + 1];
		strncpy(this->brand, brand, strlen(brand));
		this->brand[strlen(brand)] = '\0';

	}

	void setKilometers(int* kilometers, int countOfTrips) 
	{

		if (this->kilometers) delete[] this->kilometers;

		this->countOfTrips = countOfTrips;
		this->kilometers = new int[countOfTrips];

		for (int i = 0; i < countOfTrips; i++) 
		{

			this->kilometers[i] = kilometers[i];

		}

	}

	void setYear(int year)
	{

		this->year = year;

	}

	void setMaxSpeed(double maxSpeed)
	{

		this->maxSpeed = maxSpeed;

	}

	int largetsTrip() const
	{

		if (!kilometers) return 0;

		int result = kilometers[0];

		for (int i = 1; i < countOfTrips; i++)
		{

			result = std::max(result, kilometers[i]);

		}

		return result;

	}

	void printCar() const
	{

		std::cout << brand << " ";
		std::cout << year << " ";
		std::cout << maxSpeed << " ";

		std::cout << "[ ";

		for (int i = 0; i < countOfTrips; i++)
		{

			std::cout << kilometers[i] << " ";

		}

		std::cout << "]" << std::endl;

	}

	int getAllKilometers() const
	{

		if (!kilometers) return 0;

		int result = 0;

		for (int i = 0; i < countOfTrips; i++)
		{

			result += kilometers[i];

		}

		return result;

	}

	void writeToFile(const char* fileName)
	{

		if (!fileName) return;

		std::ofstream file(fileName, std::ios::binary);

		if (!file.is_open()) return;

		int sizeOfBrand = strlen(brand);
		file.write((const char*)&sizeOfBrand, sizeof(int));
		file.write((const char*)brand, sizeOfBrand * sizeof(char));

		file.write((const char*)&year, sizeof(int));
		file.write((const char*)&maxSpeed, sizeof(double));

		file.write((const char*)&countOfTrips, sizeof(int));
		file.write((const char*)kilometers, countOfTrips * sizeof(int));

		file.close();

	}

	Car readFromFile(const char* fileName)
	{

		if (!fileName) return {};

		std::ifstream file(fileName, std::ios::binary);

		if (!file.is_open()) return {};

		Car result;

		int sizeOfBrand = 0;
		file.read((char*)&sizeOfBrand, sizeof(int));

		if (result.brand) delete[] result.brand;
		result.brand = new char[sizeOfBrand + 1];
		file.read((char*)result.brand, sizeOfBrand * sizeof(char));
		result.brand[sizeOfBrand] = '\0';

		file.read((char*)&result.year, sizeof(int));
		file.read((char*)&result.maxSpeed, sizeof(double));

		file.read((char*)&result.countOfTrips, sizeof(int));

		if (result.kilometers) delete[] result.kilometers;
		result.kilometers = new int[result.countOfTrips];
		file.read((char*)result.kilometers, result.countOfTrips * sizeof(int));

		file.close();
		return result;

	}

};

int main()
{

	int kms1[] = { 100, 200, 300 };
	Car car1("BMW", 2025, 250, kms1, 3);
	car1.printCar();

	car1.writeToFile("../file.dat");
	Car car2 = car1.readFromFile("../file.dat");
	car2.printCar();

	return 0;

}
