#include "StoreItem.h"
#include "MyString.h"
#pragma once

class Vegetable: public StoreItem
{
private:

	MyString name;
	MyString sort;

	void setName(const MyString& name) override;

	void setSort(const MyString& color);

public:

	Vegetable(const MyString& name, const MyString& color,
		double price, size_t calories);

	StoreItem* clone() const override;

	void print() const override;

	friend bool operator == (const Vegetable& left, const Vegetable& right);

	const MyString& getName() const;

	const MyString& getSort() const;

};

