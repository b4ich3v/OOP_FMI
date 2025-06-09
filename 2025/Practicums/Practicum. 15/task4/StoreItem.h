#include <iostream>
#include "MyString.h"
#pragma once

enum class ItemType
{

	FRUIT = 0,
	VEGETABLE = 1

};

class StoreItem
{
private:

	ItemType type;
	size_t calories = 0;
	double price = 0;

public:

	StoreItem(ItemType type, size_t calories, double price);

	virtual StoreItem* clone() const = 0;

	virtual ~StoreItem() = default;

	void setType(ItemType type);

	void setPrice(double price);

	void setCalories(size_t calories);

	ItemType getType() const;

	size_t getCalories() const;

	double getPrice() const;

	virtual void setName(const MyString& name) = 0;

	virtual void print() const = 0;

};

