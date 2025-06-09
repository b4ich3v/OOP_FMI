#include "StoreItem.h"

StoreItem::StoreItem(ItemType type, size_t calories, double price):
	type(type), calories(calories), price(price) {}

void StoreItem::setType(ItemType type)
{

	this->type = type;

}

void StoreItem::setPrice(double price) 
{

	if (price < 0) throw std::logic_error("Error");

	this->price = price;

}

void StoreItem::setCalories(size_t calories) 
{

	this->calories = calories;

}

ItemType StoreItem::getType() const 
{

	return type;

}

size_t StoreItem::getCalories() const 
{

	return calories;

}

double StoreItem::getPrice() const 
{

	return price;
	
}
