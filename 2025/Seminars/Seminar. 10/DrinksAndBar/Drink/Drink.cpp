#include "Drink.h"

Drink::Drink() 
{

	this->name = new char[strlen("default") + 1];
	strncpy(this->name, "default", strlen("default"));
	this->name[strlen("default")] = '\0';

	this->quantity = 0;

}

Drink::Drink(const Drink& other) 
{

	copyFrom(other);

}

Drink::Drink(const char* name, double quantity) 
{

	if (this->name == name || !name) throw std::logic_error("Error");

	this->name = new char[strlen(name) + 1];
	strncpy(this->name, name, strlen(name));
	this->name[strlen(name)] = '\0';

	if (quantity < 0) throw std::logic_error("Error");

	this->quantity = quantity;

}

Drink::Drink(Drink&& other) noexcept 
{

	moveTo(std::move(other));

}

Drink& Drink::operator = (const Drink& other) 
{

	if (this != &other) 
	{

		free();
		copyFrom(other);

	}

	return *this;

}

Drink& Drink::operator = (Drink&& other) noexcept
{

	if (this != &other)
	{

		free();
		moveTo(std::move(other));

	}

	return *this;

}

Drink::~Drink() 
{

	free();

}

void Drink::free() 
{

	delete[] name;
	name = nullptr;
	quantity = 0;

}

void Drink::copyFrom(const Drink& other) 
{

	this->name = new char[strlen(other.name) + 1];
	strncpy(this->name, other.name, strlen(other.name));
	this->name[strlen(other.name)] = '\0';

	this->quantity = other.quantity;

}

void Drink::moveTo(Drink&& other)
{

	this->name = other.name;
	this->quantity = other.quantity;

	other.name = nullptr;
	other.quantity = 0;
	
}

const char* Drink::getName() const
{

	return name;

}

double Drink::getQuantity() const 
{

	return quantity;

}

void Drink::print() const 
{

	std::cout << name << " ";
	std::cout << quantity << std::endl;

}

Drink* Drink::clone() const 
{

	return new Drink(*this);

}
