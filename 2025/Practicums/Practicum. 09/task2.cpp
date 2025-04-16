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
	Registration registration = HELPERS::DEFAULT_REGISTER;

	void free()
	{

		delete[] description;
		description = nullptr;

	}

	void moveTo(Vehicle&& other) 
	{

		this->description = other.description;
		this->registration = other.registration;

		other.description = nullptr;
		other.registration = HELPERS::DEFAULT_REGISTER;

	}

	void copyFrom(const Vehicle& other) 
	{

		if (!other.description || this->description == other.description) throw std::logic_error("Error");

		this->description = new char[strlen(other.description) + 1];
		strncpy(this->description, other.description, strlen(other.description));
		this->description[strlen(other.description)] = '\0';

		this->registration = other.registration;

	}

public:

	Vehicle() = delete;

	Vehicle(const char* description, Registration registration) 
	{

		if (!description || this->description == description) throw std::logic_error("Error");

		this->description = new char[strlen(description) + 1];
		strncpy(this->description, description, strlen(description));
		this->description[strlen(description)] = '\0';

		this->registration = registration;

	}

	Vehicle(const Vehicle& other) 
	{

		copyFrom(other);

	}

	Vehicle(Vehicle&& other) noexcept 
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

};

int main()
{

	Vehicle v1("Neshto si versiq 1", "PK7777PK");
	Vehicle v2("Neshto si versiq 2", "A1234AK");

	v1.printVehicle();
	v2.printVehicle();

	return 0;

}

