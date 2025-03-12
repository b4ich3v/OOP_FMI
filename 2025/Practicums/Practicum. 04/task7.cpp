#include <iostream>
#include <cstring>

namespace CONSTANTS
{

	const int MAX_SIZE_NAME = 100;
	const double TOLERANCE = 0.001;
	const int MAX_COUNT_CARS = 1000;
	const char DEFAULT_BRAND[14] = "Default brand";
	const char DEFAULT_MODEL[14] = "Default model";
	const int TEST_DRIVE_DISTANCE = 1;

}

enum class TypeEngine
{

	GASOLINE = 0,
	DIESEL = 1,
	ELECTRICITY = 2

};

class Car
{
private:

	char brand[CONSTANTS::MAX_SIZE_NAME + 1];
	char model[CONSTANTS::MAX_SIZE_NAME + 1];
	TypeEngine engine;

	bool secondHand;
	unsigned int mileage;
	double price;

	void setBrand(const char* newBrand)
	{

		if (!newBrand) strncpy(brand, "No brand\0", strlen("No brand\0"));
		else
		{

			strncpy(brand, newBrand, strlen(newBrand));
			brand[strlen(newBrand)] = '\0';

		}

	}

	void setModel(const char* newModel)
	{

		if (!newModel) strncpy(model, "No model\0", strlen("No model\0"));
		else
		{

			strncpy(model, newModel, strlen(newModel));
			model[strlen(newModel)] = '\0';

		}

	}

	void setEngine(TypeEngine newEngine)
	{

		engine = newEngine;

	}

	void setPrice(double newPrice)
	{

		if (newPrice < 0) price = 0;
		else price = newPrice;

	}

	double calculatePercentage(double percentage) const
	{

		return price * percentage;

	}

	void precalculatePrice(double tolerance, int distance)
	{

		while (distance != 0)
		{

			price -= calculatePercentage(tolerance);
			distance -= 1;

		}

	}

public:

	Car()
	{

		setBrand(CONSTANTS::DEFAULT_BRAND);
		setModel(CONSTANTS::DEFAULT_MODEL);
		setEngine(TypeEngine::DIESEL);
		setPrice(0);

		secondHand = false;
		mileage = 0;

	}

	Car(const char* newBrand, const char* newModel, TypeEngine newEngine, double newPrice)
	{

		setBrand(newBrand);
		setModel(newModel);
		setEngine(newEngine);
		setPrice(newPrice);

		secondHand = false;
		mileage = 0;

	}

	void drive(int kilometers)
	{

		mileage += kilometers;
		secondHand = true;
		precalculatePrice(CONSTANTS::TOLERANCE, kilometers);

	}

	void printCar() const
	{

		std::cout << brand << " ";
		std::cout << model << " ";

		switch (engine)
		{

		case TypeEngine::GASOLINE: std::cout << "GASOLINE "; break;
		case TypeEngine::DIESEL: std::cout << "DIESEL "; break;
		case TypeEngine::ELECTRICITY: std::cout << "ELECTRICITY "; break;
		default: break;

		}

		if (secondHand) std::cout << "SECOND HAND ";
		else std::cout << "FIRST HAND ";

		std::cout << mileage << " ";
		std::cout << price << std::endl;

	}

	TypeEngine getEngine() const
	{

		return engine;

	}

	const char* getModel() const
	{

		return model;

	}

	const char* getBrand() const
	{

		return brand;

	}

	double getPrice() const
	{

		return price;

	}

};

class CarDealership
{
private:

	Car cars[CONSTANTS::MAX_COUNT_CARS];
	int countOfCars;

public:

	CarDealership(Car* cars, int countOfCars)
	{

		if (cars != nullptr)
		{

			this->countOfCars = countOfCars;

			for (int i = 0; i < countOfCars; i++)
			{

				this->cars[i] = cars[i];

			}

		}

	}

	CarDealership(Car* cars, int countOfCars, TypeEngine engine)
	{

		if (cars != nullptr)
		{

			int index = 0;

			for (int i = 0; i < countOfCars; i++)
			{

				if ((int)cars[i].getEngine() == (int)engine)
				{

					this->cars[index] = cars[i];
					index += 1;

				}

			}

			this->countOfCars = index;

		}

	}

	CarDealership(Car* cars, int countOfCars, const char* model)
	{

		if (cars != nullptr && model != nullptr)
		{

			int index = 0;

			for (int i = 0; i < countOfCars; i++)
			{

				if (!strcmp(cars[i].getModel(), model))
				{

					this->cars[index] = cars[i];
					index += 1;

				}

			}

			this->countOfCars = index;

		}

	}

	int getCountOfCars() const
	{

		return countOfCars;

	}

	void printCars() const
	{

		for (int i = 0; i < countOfCars; i++)
		{

			cars[i].printCar();

		}

		std::cout << std::endl;

	}

	void addCar(const Car& car)
	{

		if (countOfCars == CONSTANTS::MAX_COUNT_CARS) return;

		cars[countOfCars] = car;
		countOfCars += 1;

	}

	void removeCar(const char* brand, const char* model)
	{

		if (!brand || !model) return;

		for (int i = 0; i < countOfCars; i++)
		{

			if (!strcmp(cars[i].getBrand(), brand) &&
				!strcmp(cars[i].getModel(), model))
			{

				std::swap(cars[i], cars[countOfCars - 1]);
				countOfCars -= 1;
				break;

			}

		}

	}

	void testDrive()
	{

		for (int i = 0; i < countOfCars; i++)
		{

			cars[i].drive(CONSTANTS::TEST_DRIVE_DISTANCE);

		}

	}

	void printByModel(const char* model) const
	{

		if (!model) return;

		for (int i = 0; i < countOfCars; i++)
		{

			if (!strcmp(cars[i].getModel(), model))
			{

				cars[i].printCar();

			}

		}

	}

	Car getTheMostExpensiveCar() const
	{

		double maxPrice = cars[0].getPrice();
		int resultIndex = 0;

		for (int i = 1; i < countOfCars; i++)
		{

			if (cars[i].getPrice() > maxPrice)
			{

				maxPrice = cars[i].getPrice();
				resultIndex = i;

			}

		}

		return cars[resultIndex];

	}

	double getAvaragePriceByModel(const Car& car) const
	{

		double sum = 0;
		int counter = 0;

		for (int i = 0; i < countOfCars; i++)
		{

			if (!strcmp(cars[i].getModel(), car.getModel()))
			{

				sum += cars[i].getPrice();
				counter += 1;

			}

		}

		return sum / counter;

	}

};

int main()
{

	Car car1("AUDI", "A5", TypeEngine::DIESEL, 20000);
	Car car2("PORSCHE", "CAYENNE", TypeEngine::DIESEL, 20000);
	Car car3("TESLA", "X", TypeEngine::ELECTRICITY, 100000);
	Car car4("FERRARI", "SF90", TypeEngine::GASOLINE, 300000);

	Car* carsPtr = nullptr;
	carsPtr = new Car[4];
	carsPtr[0] = car1;
	carsPtr[1] = car2;
	carsPtr[2] = car3;
	carsPtr[3] = car4;

	CarDealership cars1(carsPtr, 4);
	cars1.testDrive();
	cars1.printCars();

	CarDealership cars2(carsPtr, 4, TypeEngine::DIESEL);
	cars2.printCars();

	CarDealership cars3(carsPtr, 4, "A5");
	cars3.addCar(car3);
	cars3.printCars();
	cars3.removeCar("AUDI", "A5");
	cars3.printCars();

	Car expensive = cars1.getTheMostExpensiveCar();
	expensive.printCar();

	delete[] carsPtr;
	return 0;

}
