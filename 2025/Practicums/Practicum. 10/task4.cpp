#include <iostream>
#include <cstring>

class CarPart
{
private:

	static int idMask;
	int id = 0;
	char* nameOfManufacturer = nullptr;
	char* description = nullptr;

	void copyFrom(const CarPart& other) 
	{

		this->nameOfManufacturer = new char[strlen(other.nameOfManufacturer) + 1];
		strncpy(this->nameOfManufacturer, other.nameOfManufacturer, strlen(other.nameOfManufacturer));
		this->nameOfManufacturer[strlen(other.nameOfManufacturer)] = '\0';

		this->description = new char[strlen(other.description) + 1];
		strncpy(this->description, other.description, strlen(other.description));
		this->description[strlen(other.description)] = '\0';

		this->id = other.id;

	}

	void moveTo(CarPart&& other) 
	{

		this->id = other.id;
		this->description = other.description;
		this->nameOfManufacturer = other.nameOfManufacturer;

		other.description = nullptr;
		other.nameOfManufacturer = nullptr;
		other.id = 0;

	}

	void free()
	{

		delete[] nameOfManufacturer;
		nameOfManufacturer = nullptr;

		delete[] description;
		description = nullptr;

		id = 0;

	}

public:

	CarPart() 
	{

		this->nameOfManufacturer = new char[strlen("Default") + 1];
		strncpy(this->nameOfManufacturer, "default", strlen("default"));
		this->nameOfManufacturer[strlen("default")] = '\0';

		this->description = new char[strlen("Default") + 1];
		strncpy(this->description, "default", strlen("default"));
		this->description[strlen("default")] = '\0';

		this->id = idMask;
		idMask += 1;

	}

	CarPart(const CarPart& other) 
	{

		copyFrom(other);

	}

	CarPart(const char* description, const char* nameOfManufacturer) 
	{

		if (!description || !nameOfManufacturer) throw std::logic_error("Error");

		this->nameOfManufacturer = new char[strlen(nameOfManufacturer) + 1];
		strncpy(this->nameOfManufacturer, nameOfManufacturer, strlen(nameOfManufacturer));
		this->nameOfManufacturer[strlen(nameOfManufacturer)] = '\0';

		this->description = new char[strlen(description) + 1];
		strncpy(this->description, description, strlen(description));
		this->description[strlen(description)] = '\0';

		this->id = idMask;
		idMask += 1;

	}

	CarPart(CarPart&& other) noexcept 
	{

		moveTo(std::move(other));

	}

	CarPart& operator = (const CarPart& other) 
	{

		if (this != &other) 
		{

			free();
			copyFrom(other);

		}

		return *this;

	}

	CarPart& operator = (CarPart&& other) noexcept
	{

		if (this != &other)
		{

			free();
			moveTo(std::move(other));

		}

		return *this;

	}

	~CarPart() 
	{

		free();

	}

	void print() const
	{

		std::cout << nameOfManufacturer << " ";
		std::cout << description << " ";
		std::cout << id << " ";

	}

	friend std::ostream& operator << (std::ostream& os, const CarPart& tires)
	{

		os << tires.nameOfManufacturer << " ";
		os << tires.description << " ";
		os << tires.id << " ";

		return os;

	}

};

int CarPart::idMask = 0;

class Tires: public CarPart 
{
private:

	unsigned int width = 0;
	unsigned int profile = 0;
	unsigned int diameter = 0;

public:

	Tires(const char* description, const char* nameOfManufacturer, 
		unsigned int width, unsigned int profile, unsigned int diameter) : CarPart(description, nameOfManufacturer)
	{

		if (width < 155 || width > 365) throw std::logic_error("Error");
		if (profile < 30 || profile > 80) throw std::logic_error("Error");
		if (diameter < 13 || diameter > 21) throw std::logic_error("Error");

		this->width = width;
		this->profile = profile;
		this->diameter = diameter;

	}

	void print() const
	{

		CarPart::print();

		std::cout << width << " ";
		std::cout << profile << " ";
		std::cout << diameter << std::endl;

	}

	friend std::ostream& operator << (std::ostream& os, const Tires& tires) 
	{

		const CarPart* ptr = &tires;

		os << *ptr;
		os << tires.width << " ";
		os << tires.profile << " ";
		os << tires.diameter;

		return os;

	}

};

class Engine: public CarPart
{
private:

	unsigned int horsepower = 0;

public:

	Engine(const char* description, const char* nameOfManufacturer,
		unsigned int horsepower) : CarPart(description, nameOfManufacturer)
	{

		this->horsepower = horsepower;

	}

	void print() const
	{

		CarPart::print();

		std::cout << horsepower << std::endl;

	}

	friend std::ostream& operator << (std::ostream& os, const Engine& engine)
	{

		const CarPart* ptr = &engine;
		os << *ptr;
		os << engine.horsepower;

		return os;

	}

	unsigned int getHourPower() const 
	{

		return horsepower;

	}

};

class Accumulator: public CarPart 
{
private:

	int capacity = 0;
	char* batteryId = nullptr;

	void copyFrom(const Accumulator& other)
	{

		this->capacity = other.capacity;
		this->batteryId = new char[strlen(other.batteryId) + 1];
		strncpy(this->batteryId, other.batteryId, strlen(other.batteryId));
		this->batteryId[strlen(other.batteryId)] = '\0';

	}

	void moveTo(Accumulator&& other) 
	{

		this->capacity = other.capacity;
		this->batteryId = other.batteryId;

		other.batteryId = nullptr;
		other.capacity = 0;

	}

	void free() 
	{

		delete[] batteryId;
		batteryId = nullptr;
		capacity = 0;

	}

public:

	Accumulator(): CarPart() {}

	Accumulator(const Accumulator& other) : CarPart(other) 
	{

		copyFrom(other);

	}

	Accumulator(const char* description, const char* nameOfManufacturer,
		int capacity, const char* batteryId) : CarPart(description, nameOfManufacturer) 
	{

		this->capacity = capacity;
		this->batteryId = new char[strlen(batteryId) + 1];
		strncpy(this->batteryId, batteryId, strlen(batteryId));
		this->batteryId[strlen(batteryId)] = '\0';
			
	}

	Accumulator(Accumulator&& other) noexcept: CarPart(std::move(other))
	{

		moveTo(std::move(other));

	}

	Accumulator& operator = (const Accumulator& other) 
	{

		if (this != &other) 
		{

			CarPart::operator=(other);
			free();
			copyFrom(other);

		}

		return *this;

	}

	Accumulator& operator = (Accumulator&& other) noexcept
	{

		if (this != &other)
		{

			CarPart::operator=(std::move(other));
			free();
			moveTo(std::move(other));

		}

		return *this;

	}

	~Accumulator() 
	{

		free();

	}

	friend std::ostream& operator << (std::ostream& os, const Accumulator& accumulator)
	{

		const CarPart* ptr = &accumulator;
		os << *ptr;
		os << accumulator.capacity << " ";
		os << accumulator.batteryId;

		return os;

	}

};

class FuelTank
{
private:

	double capacity = 0;
	double currentLitres = 0;

public:

	FuelTank(int capacity): capacity(capacity), currentLitres(capacity) {}

	void use(double toUse)
	{

		if (toUse > currentLitres) currentLitres = 0;
		else currentLitres -= toUse;
			
	}

	void fill(double toFill) 
	{

		if (currentLitres + toFill >= capacity) currentLitres = capacity;
		else currentLitres += toFill;
		
	}

	bool isEmpty() const 
	{

		return currentLitres == 0;

	}

};

class Car 
{
private:

	FuelTank& fuel;
	Engine& engine;
	Tires* tires[4];
	Accumulator& accumulator;

	int kilometresTraveled = 0;
	int weight = 0;

public:

	Car(FuelTank& fuel, Engine& engine, Tires** tires, Accumulator& accumulator, int kilometresTraveled, int weight)
		: fuel(fuel), engine(engine), accumulator(accumulator)
	{

		for (int i = 0; i < 4; i++)
		{

			this->tires[i] = tires[i];

		}

		this->kilometresTraveled = kilometresTraveled;
		this->weight = weight;

	}

	const FuelTank& getFuelTank() 
	{

		return fuel;

	}

	void drive(double km) 
	{

		fuel.use(km);

	}

	friend Car* dragRace(Car* car1, Car* car2) 
	{

		car1->drive(0.4);
		car2->drive(0.4);

		if ((car1->fuel.isEmpty()) && (car2->fuel.isEmpty()))
		{

			if (car1->engine.getHourPower() / car1->weight > car2->engine.getHourPower()) 
			{

				return car1;

			}
			else 
			{

				return car2;

			}

		}
		else if (car1->fuel.isEmpty()) 
		{

			return car2;

		}
		else if(car2->fuel.isEmpty())
		{

			return car1;

		}

		return nullptr;

	}

};

int main() 
{
	
	Tires* tires1[4] = 
	{

		new Tires("Tire FL", "Michelin", 195, 55, 16),
		new Tires("Tire FR", "Michelin", 195, 55, 16),
		new Tires("Tire RL", "Michelin", 195, 55, 16),
		new Tires("Tire RR", "Michelin", 195, 55, 16)

	};

	Tires* tires2[4] = 
	{

		new Tires("Tire FL", "Pirelli", 205, 50, 17),
		new Tires("Tire FR", "Pirelli", 205, 50, 17),
		new Tires("Tire RL", "Pirelli", 205, 50, 17),
		new Tires("Tire RR", "Pirelli", 205, 50, 17)

	};

	Engine engine1("Sport engine", "Ford", 300);
	Engine engine2("Racing engine", "Ferrari", 350);

	Accumulator acc1("Standard Acc", "Varta", 60, "A123B");
	Accumulator acc2("High Power", "Bosch", 70, "B456C");

	FuelTank fuel1(5);  
	FuelTank fuel2(6);

	Car car1(fuel1, engine1, tires1, acc1, 10000, 1400);
	Car car2(fuel2, engine2, tires2, acc2, 12000, 1500);

	Car* winner = dragRace(&car1, &car2);

	if (winner == &car1) 
	{

		std::cout << "Car 1 wins!" << std::endl;

	}
	else if (winner == &car2) 
	{

		std::cout << "Car 2 wins!" << std::endl;

	}
	else 
	{

		std::cout << "It's a draw or both cars have fuel left." << std::endl;

	}

	for (int i = 0; i < 4; i++)
	{

		delete tires1[i];
		delete tires2[i];

	}

	return 0;

}
