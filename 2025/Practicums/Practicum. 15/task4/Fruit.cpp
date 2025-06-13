#include "Fruit.h"

Fruit::Fruit(const MyString& name, const MyString& color,
	double price, size_t calories) :
	StoreItem(ItemType::FRUIT, calories, price), name(name), color(color) {}

StoreItem* Fruit::clone() const 
{

	return new Fruit(*this);

}

void Fruit::setName(const MyString& name) 
{

	this->name = name;

}

void Fruit::setColor(const MyString& color) 
{

	this->color = color;

}

void Fruit::print() const 
{

	std::cout << name << " " << color << " "
		<< (int)getType() << " " << getCalories() << " "
		<< getPrice() << std::endl;

}

bool operator > (const Fruit& left, const Fruit& right) 
{

	return left.getCalories() > right.getCalories();

}

const MyString& Fruit::getName() const 
{

	return name;

}

const MyString& Fruit::getColor() const
{

	return color;

}
