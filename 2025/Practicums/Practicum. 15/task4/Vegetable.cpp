#include "Vegetable.h"

Vegetable::Vegetable(const MyString& name, const MyString& sort,
	double price, size_t calories):
	StoreItem(ItemType::VEGETABLE, calories, price), name(name), sort(sort) {}

StoreItem* Vegetable::clone() const
{

	return new Vegetable(*this);

}

void Vegetable::setName(const MyString& name)
{

	this->name = name;

}

void Vegetable::setSort(const MyString& sort)
{

	this->sort = sort;

}

void Vegetable::print() const
{

	std::cout << name << " " << sort << " "
		<< (int)getType() << " " << getCalories() << " "
		<< getPrice() << std::endl;

}

bool operator == (const Vegetable& left, const Vegetable& right)
{

	return left.getCalories() == right.getCalories();

}

const MyString& Vegetable::getName() const
{

	return name;

}

const MyString& Vegetable::getSort() const
{

	return sort;

}
