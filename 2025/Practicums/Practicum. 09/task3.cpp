#include <iostream>
#include <fstream>
#include <cstring>

namespace HELPERS 
{

	const int SIZE_FOR_REGISTER = 8;

	const char DEFAULT_REGISTER[9] = "PK1747AA";

	bool isDigit(char ch) 
	{

		return ch >= '0' && ch <= '9';

	}

	bool isUpper(char ch)
	{

		return ch >= 'A' && ch <= 'Z';

	}

}

class Registration 
{
private:

	char data[HELPERS::SIZE_FOR_REGISTER + 1];

	bool validation(const char* data) const
	{

		if (!(strlen(data) == HELPERS::SIZE_FOR_REGISTER || strlen(data) == HELPERS::SIZE_FOR_REGISTER - 1)) return false;
		if (!HELPERS::isUpper(data[0]) || !HELPERS::isUpper(data[strlen(data) - 1]) || !HELPERS::isUpper(data[strlen(data) - 2])) return false;
		
		bool pred = strlen(data) == HELPERS::SIZE_FOR_REGISTER;

		if (pred) 
		{


			for (int i = 2; i <= 5; i++)
			{

				if (!HELPERS::isDigit(data[i])) return false;
				
			}

			return true;

		}

		for (int i = 1; i <= 4; i++)
		{

			if (!HELPERS::isDigit(data[i])) return false;

		}

		return true;

	}

public:

	Registration() = delete;

	Registration(const char* data) 
	{

		if (!validation(data)) throw std::logic_error("Error");

		strncpy(this->data, data, strlen(data));
		this->data[strlen(data)] = '\0';

	}

	const char* getData() const 
	{

		return data;

	}

	friend bool operator == (const Registration& r1, const Registration& r2) 
	{

		return strcmp(r1.getData(), r2.getData()) == 0;

	}

	friend bool operator != (const Registration& r1, const Registration& r2)
	{

		return !(r1 == r2);

	}

};

class Vehicle
{
private:

	char* description = nullptr;
	Registration& registration;

	void free()
	{

		delete[] description;
		description = nullptr;

	}

	void moveTo(Vehicle&& other) 
	{

		this->description = other.description;
		other.description = nullptr;

	}

	void copyFrom(const Vehicle& other) 
	{

		if (!other.description) throw std::logic_error("Error");
			
		this->description = new char[strlen(other.description) + 1];
		std::strncpy(description, other.description, strlen(other.description));
		this->description[strlen(other.description)] = '\0';

	}

public:

	Vehicle() = delete;

	Vehicle(const char* description, Registration& registration): registration(registration)
	{

		if (!description || this->description == description) throw std::logic_error("Error");

		this->description = new char[strlen(description) + 1];
		strncpy(this->description, description, strlen(description));
		this->description[strlen(description)] = '\0';

	}

	Vehicle(const Vehicle& other): registration(other.registration)
	{

		copyFrom(other);

	}

	Vehicle(Vehicle&& other) noexcept: registration(other.registration)
	{

		moveTo(std::move(other));

	}

	Vehicle& operator = (const Vehicle& other) 
	{
			
		if (this != &other) 
		{

			free();
			copyFrom(other);

		}
	
		return *this;

	}

	Vehicle& operator = (Vehicle&& other) noexcept
	{

		if (this != &other)
		{

			free();
			moveTo(std::move(other));

		}

		return *this;

	}

	~Vehicle() 
	{

		free();

	}

	void printVehicle() const 
	{

		std::cout << description << " ";
		std::cout << registration.getData() << std::endl;

	}

	const char* getReNumber() const 
	{

		return registration.getData();

	}

};

class VehicleList 
{
private:

	Vehicle** ves = nullptr;
	int count = 0;
	int capacity = 8;

	void free() 
	{

		for (int i = 0; i < count; i++)
		{

			delete ves[i];
			ves[i] = nullptr;

		}

		delete[] ves;
		ves = nullptr;
		capacity = 8;
		count = 0;
	
	}

	void copyFrom(const VehicleList& other)
	{

		this->ves = new Vehicle * [other.capacity] {nullptr};
		this->count = other.count;
		this->capacity = other.capacity;

		for (int i = 0; i < count; i++)
		{

			this->ves[i] = new Vehicle(*other.ves[i]);

		}

	}

	void moveTo(VehicleList&& other) 
	{

		this->ves = other.ves;
		this->capacity = other.capacity;
		this->count = other.count;

		other.ves = nullptr;
		other.capacity = 8;
		other.count = 0;

	}

	void resize(int newCapacity) 
	{

		if (newCapacity <= capacity) return;

		Vehicle** newVes = new Vehicle * [newCapacity] {nullptr};

		for (int i = 0; i < count; i++)
		{

			newVes[i] = ves[i];

		}

		delete[] ves;
		ves = newVes;
		capacity = newCapacity;

	}

public:

	VehicleList()
	{

		count = 0;
		capacity = 8;
		ves = new Vehicle * [capacity] {nullptr};

	}

	VehicleList(const VehicleList& other) 
	{

		copyFrom(other);

	}

	VehicleList(VehicleList&& other) noexcept
	{

		moveTo(std::move(other));

	}

	VehicleList& operator = (const VehicleList& other) 
	{

		if (this != &other) 
		{

			free();
			copyFrom(other);

		}

		return *this;

	}

	VehicleList& operator = (VehicleList&& other) noexcept
	{

		if (this != &other)
		{

			free();
			moveTo(std::move(other));

		}

		return *this;

	}

	~VehicleList() 
	{

		free();

	}

	const Vehicle& operator [] (int index) const 
	{

		if (index < 0 || index >= count) throw std::logic_error("Error");

		return *ves[index];

	}
	
	Vehicle& operator [] (int index)
	{

		if (index < 0 || index >= count) throw std::logic_error("Error");

		return *ves[index];

	}

	bool isEmpty() const 
	{

		return count == 0;

	}

	void addVehicle(const Vehicle& v) 
	{

		if (count == capacity) resize(capacity * 2);

		ves[count] = new Vehicle(v);
		count += 1;

	}

	void print() const 
	{

		for (int i = 0; i < count; i++)
		{

			ves[i]->printVehicle();

		}

		std::cout << std::endl;

	}

	const Vehicle& findByNumber(const char* reNumber) const 
	{

		for (int i = 0; i < count; i++)
		{

			if (!strcmp(ves[i]->getReNumber(), reNumber)) 
			{

				return *ves[i];

			}

		}

		throw std::logic_error("Not found");

	}

};

int main()
{

	Registration r1("PK7777PK");
	Registration r2("A1234AK");
	Registration r3("SA1135PR");
	Registration r4("PE1198AA");

	Vehicle v1("Neshto si versiq 1", r1);
	Vehicle v2("Neshto si versiq 2", r2);
	Vehicle v3("Neshto si versiq 3", r3);
	Vehicle v4("Neshto si versiq 4", r4);

	VehicleList ves;
	ves.addVehicle(v1);
	ves.addVehicle(v2);
	ves.addVehicle(v3);
	ves.addVehicle(v4);
	ves.print();
	std::cout << ves.isEmpty() << std::endl;

	try
	{

		const Vehicle& ref1 = ves.findByNumber("PK7777PK");
		ref1.printVehicle();

		const Vehicle& ref2 = ves.findByNumber("SIKE");
		ref2.printVehicle();

	}
	catch (const std::exception& e)
	{

		std::cout << e.what() << std::endl;

	}

	return 0;

}

