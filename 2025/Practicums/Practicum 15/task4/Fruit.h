#include "StoreItem.h"
#include "MyString.h"
#pragma once

class Fruit: public StoreItem
{
private:

	MyString name;
	MyString color;

	void setName(const MyString& name) override;

	void setColor(const MyString& color);

public:

	Fruit(const MyString& name, const MyString& color,
		double price, size_t calories);

	StoreItem* clone() const override;

	void print() const override;

	friend bool operator > (const Fruit& left, const Fruit& right);

	const MyString& getName() const;

	const MyString& getColor() const;

};


