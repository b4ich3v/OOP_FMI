#include "StoreItem.h"
#include "Fruit.h"
#include "MyString.h"
#pragma once

class Shop
{
private:

	StoreItem** items = nullptr;
	size_t size = 0;
	size_t capacity = 8;

	void free();

	void copyFrom(const Shop& other);

	void moveTo(Shop&& other);

	void resize(size_t newCapacity);

public:

	Shop();

	Shop(const Shop& other);

	Shop(Shop&& other) noexcept;

	Shop& operator = (const Shop& other);

	Shop& operator = (Shop&& other) noexcept;

	~Shop();

	void addElement(StoreItem* item);
	
	void removeElement(size_t index);

	void changePrice(size_t index, double newPrice);

	void changeName(size_t index, const MyString& newName);

	void print() const;

	const Fruit* mostCalories() const;

};

