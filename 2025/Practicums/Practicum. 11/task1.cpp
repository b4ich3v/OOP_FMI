#include <iostream>
#include <cstring>
#include "MyString.h"

class Device 
{
private:

	MyString name;
	double price = 0;

public:

	Device(): Device("No name", 0.00) {}

	Device(const MyString& str, double price): name(str), price(price) {}

	const MyString& getName() const 
	{

		return name;

	}

	double getPrice() const 
	{

		return price;

	}

	virtual void turnOn() const = 0;

	virtual void turnOff() const = 0;

	virtual void printDetails() const = 0;

	virtual Device* clone() const = 0;

	virtual ~Device() = default;

};

class SmartLight: public Device 
{
private:

	int brightnessLevel = 0;

public:

	SmartLight(const MyString& str, int price, int brightnessLevel): Device(str, price) 
	{

		this->brightnessLevel = brightnessLevel;

	}

	void turnOn() const override 
	{

		std::cout << "SmartLight has been turned on" << std::endl;

	}

	void turnOff() const override 
	{

		std::cout << "SmartLight has been turned off" << std::endl;

	}

	void printDetails() const override 
	{

		std::cout << getName() << " " << getPrice() << " " << brightnessLevel << std::endl;

	}

	Device* clone() const override 
	{

		return new SmartLight(getName(), getPrice(), brightnessLevel);

	}

};

class SmartThermostat: public Device 
{
private:

	int currentTemperature = 0;
	int wantedTemperature = 0;

public:

	SmartThermostat(const MyString& str, int price, 
		int currentTemperature, int wantedTemperature) : Device(str, price)
	{

		this->currentTemperature = currentTemperature;
		this->wantedTemperature = wantedTemperature;

	}

	void turnOn() const override
	{

		std::cout << "SmartThermostat has been turned on" << std::endl;

	}

	void turnOff() const override
	{

		std::cout << "SmartThermostat has been turned off" << std::endl;

	}

	void printDetails() const override
	{

		std::cout << getName() << " " << getPrice() << " " << 
			currentTemperature << " " << wantedTemperature << std::endl;

	}

	Device* clone() const override
	{

		return new SmartThermostat(getName(), getPrice(),
			currentTemperature, wantedTemperature);

	}

};

class SmartSpeaker: public Device 
{
private:

	int powerOfSound = 0;

public:

	SmartSpeaker(const MyString& str, int price, int powerOfSound) : Device(str, price)
	{

		this->powerOfSound = powerOfSound;

	}

	void turnOn() const override
	{

		std::cout << "SmartSpeaker has been turned on" << std::endl;

	}

	void turnOff() const override
	{

		std::cout << "SmartSpeaker has been turned off" << std::endl;

	}

	void printDetails() const override
	{

		std::cout << getName() << " " << getPrice() << powerOfSound << std::endl;

	}

	Device* clone() const override
	{

		return new SmartSpeaker(getName(), getPrice(), powerOfSound);

	}

};

class SmartHome 
{
private:

	Device** devices = nullptr;
	int size = 0;
	int capacity = 8;

	void resize(int newCapacity) 
	{

		if (newCapacity <= capacity) return;

		Device** newDevices = new Device * [newCapacity] {nullptr};

		for (int i = 0; i < newCapacity; i++)
		{

			newDevices[i] = devices[i];

		}

		delete[] devices;
		devices = newDevices;
		capacity = newCapacity;

	}

	void free() 
	{

		for (int i = 0; i < capacity; i++)
		{

			delete devices[i];
			devices[i] = nullptr;

		}

		delete[] devices;
		devices = nullptr;
		size = 0;
		capacity = 8;

	}

	void copyFrom(const SmartHome& other) 
	{

		this->devices = new Device * [other.capacity] {nullptr};
		this->capacity = other.capacity;
		this->size = other.size;

		for (int i = 0; i < capacity; i++)
		{

			if (other.devices[i] == nullptr) continue;
			this->devices[i] = other.devices[i]->clone();

		}

	}

	void moveTo(SmartHome&& other) 
	{

		this->devices = other.devices;
		this->size = other.size;
		this->capacity = other.capacity;

		other.devices = nullptr;
		other.size = 0;
		other.capacity = 8;

	}

public:

	SmartHome(): SmartHome(8) {}

	SmartHome(int capacity) 
	{

		this->devices = new Device * [capacity] {nullptr};
		this->capacity = capacity;
		this->size = 0;

	}

	SmartHome(const SmartHome& other) 
	{

		copyFrom(other);

	}

	SmartHome(SmartHome&& other) noexcept 
	{

		moveTo(std::move(other));

	}
	
	SmartHome& operator = (const SmartHome& other) 
	{

		if (this != &other) 
		{

			free();
			copyFrom(other);

		}

		return *this;

	}

	SmartHome& operator = (SmartHome&& other) noexcept
	{

		if (this != &other)
		{

			free();
			moveTo(std::move(other));

		}

		return *this;

	}

	~SmartHome() 
	{

		free();

	}

	void addDevice(const Device* device) 
	{

		if (size == capacity) resize(capacity * 2);

		devices[size] = device->clone();
		size += 1;

	}

	void removeDevice()
	{

		if (size == 0) return;

		delete devices[size - 1];
		devices[size - 1] = nullptr;
		size -= 1;

	}

	void print() const 
	{

		for (int i = 0; i < capacity; i++)
		{

			if (devices[i] == nullptr) continue;
			devices[i]->printDetails();

		}

		std::cout << std::endl;

	}

	void turnOnDevice(int index) const 
	{

		if (index < 0 || index > size) throw std::logic_error("Error");

		devices[index]->turnOn();

	}

	void turnOffDevice(int index) const
	{

		if (index < 0 || index > size) throw std::logic_error("Error");

		devices[index]->turnOff();

	}

	double getAvaragePrice(const char* name) const
	{

		if (!name) throw std::logic_error("Error");

		double result = 0;
		int counter = 0;

		for (int i = 0; i < size; i++)
		{

			if (!strcmp(name, devices[i]->getName().getData())) 
			{

				counter += 1;
				result += devices[i]->getPrice();

			}

		}

		if (!counter) return 0;

		return result / counter;

	}

};

int main() 
{
	
	MyString lightName("Living Room Light");
	SmartLight light(lightName, 49, 75);

	MyString speakerName("Kitchen Speaker");
	SmartSpeaker speaker(speakerName, 89, 50);

	MyString thermoName("Bedroom Thermostat");
	SmartThermostat thermostat(thermoName, 120, 22, 25);

	SmartHome home;
	home.addDevice(&light);
	home.addDevice(&speaker);
	home.addDevice(&thermostat);

	home.print();
	std::cout << std::endl;
	home.turnOnDevice(0);
	home.turnOffDevice(2);

	std::cout << lightName << " " << home.getAvaragePrice("Living Room Light") << std::endl;

	home.removeDevice();
	std::cout << std::endl;
	home.print();

	return 0;

}
