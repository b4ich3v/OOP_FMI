#include <iostream>
#include "MyString.h"
#include "HeterogeneousContainer.hpp"

class Device
{
private:

	MyString name;
	double price = 0;

public:

	Device(const MyString& name, double price): name(name), price(price) {}

	virtual void turnOn() const = 0;

	virtual void turnOff() const = 0;

	virtual void printDetails() const = 0;

	virtual Device* clone() const = 0;

	virtual ~Device() = default;

protected:

	const MyString& getName() const
	{

		return name;

	}

	double getPrice() const
	{

		return price;

	}

};

class SmartLight: public Device
{
private:

	int brightnessLevel = 0;

public:

	SmartLight(const MyString& name, double price, int brightnessLevel): Device(name, price)
	{

		this->brightnessLevel = brightnessLevel;

	}

	void turnOn() const override
	{

		std::cout << "The deviced is turned on\n";

	}

	void turnOff() const override
	{

		std::cout << "The deviced is turned off\n";

	}

	void printDetails() const override
	{

		std::cout << getName();
		std::cout << " " << getPrice() << " " << brightnessLevel << '\n';

	}

	Device* clone() const override
	{

		return new SmartLight(*this);

	}

};

class SmartSpeaker : public Device
{
private:

	int powerOfSound = 0;

public:

	SmartSpeaker(const MyString& name, double price, int powerOfSound): Device(name, price)
	{

		this->powerOfSound = powerOfSound;

	}

	void turnOn() const override
	{

		std::cout << "The deviced is turned on\n";

	}

	void turnOff() const override
	{

		std::cout << "The deviced is turned off\n";

	}

	void printDetails() const override
	{

		std::cout << getName();
		std::cout << " " << getPrice() << " " << powerOfSound << '\n';

	}

	Device* clone() const override
	{

		return new SmartSpeaker(*this);

	}

};

class SmartThermostat: public Device
{
private:

	int currentTemperature = 0;
	int wantedTemperature = 0;

public:

	SmartThermostat(const MyString& name, double price, int currentTemperature, int wantedTemperature): Device(name, price)
	{

		this->currentTemperature = currentTemperature;
		this->wantedTemperature = wantedTemperature;

	}

	void turnOn() const override
	{

		std::cout << "The deviced is turned on\n";

	}

	void turnOff() const override
	{

		std::cout << "The deviced is turned off\n";

	}

	void printDetails() const override
	{

		std::cout << getName();
		std::cout << " " << getPrice() << " " << currentTemperature << " " << wantedTemperature << '\n';

	}

	Device* clone() const override
	{

		return new SmartThermostat(*this);

	}

};

struct SmartHome
{
public:

	HeterogeneousContainer<Device> arr;

	void addDevice(Device* device)
	{

		arr.addElement(device);

	}

	void removeDevice(size_t index)
	{

		arr.removeElement(index);

	}

	void printDevices() const
	{

		for (int i = 0; i < arr.getSize(); i++)
		{

			if(arr[i] != nullptr) arr[i]->printDetails();

		}

		std::cout << std::endl;

	}

};

int main()
{

	Device* d1 = new SmartLight("one", 3.14, 3);
	Device* d2 = new SmartSpeaker("two", 3.14, 100);
	Device* d3 = new SmartThermostat("three", 3.14, 10, 23);

	SmartHome home;
	home.addDevice(d1);
	home.addDevice(d2);
	home.addDevice(d3);
	home.printDevices();

	home.removeDevice(1);
	home.printDevices();

	delete d1;
	delete d2;
	delete d3;

	return 0;

}
