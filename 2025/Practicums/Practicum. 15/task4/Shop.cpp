#include "Shop.h"

void Shop::free() 
{

	for (int i = 0; i < capacity; i++)
	{

		if (items[i] != nullptr)
			delete items[i];

		items[i] = nullptr;

	}

	delete[] items;
	items = nullptr;
	size = 0;
	capacity = 8;

}

void Shop::copyFrom(const Shop& other) 
{

	size = other.size;
	capacity = other.capacity;
	items = new StoreItem * [capacity] {nullptr};

	for (int i = 0; i < capacity; i++)
	{

		items[i] = other.items[i]->clone();

	}

}

void Shop::moveTo(Shop&& other) 
{

	items = other.items;
	size = other.size;
	capacity = other.capacity;

	other.items = nullptr;
	other.size = 0;
	other.capacity = 0;

}

void Shop::resize(size_t newCapacity) 
{

	if (newCapacity <= capacity) return;

	StoreItem** newItems = new StoreItem * [newCapacity] {nullptr};

	for (int i = 0; i < capacity; i++)
	{

		newItems[i] = items[i];

	}

	delete[] items;
	items = newItems;
	capacity = newCapacity;

}

Shop::Shop() 
{

	size = 0;
	capacity = 8;
	items = new StoreItem * [capacity] {nullptr};

}

Shop::Shop(const Shop& other) 
{

	copyFrom(other);

}

Shop::Shop(Shop&& other) noexcept 
{

	moveTo(std::move(other));

}

Shop& Shop::operator = (const Shop& other) 
{

	if (this != &other) 
	{

		free();
		copyFrom(other);

	}

	return *this;

}

Shop& Shop::operator = (Shop&& other) noexcept 
{

	if (this != &other)
	{

		free();
		moveTo(std::move(other));

	}

	return *this;

}

Shop::~Shop() 
{

	free();

}

void Shop::addElement(StoreItem* item) 
{

	if (size == capacity) resize(capacity * 2);

	items[size++] = item->clone();

}

void Shop::removeElement(size_t index) 
{

	if (index > capacity || items[index] == nullptr || size == 0) throw std::logic_error("Error");

	delete items[index];
	items[index] = nullptr;
	size -= 1;

}

void Shop::changePrice(size_t index, double newPrice) 
{

	if (index > capacity || items[index] == nullptr || size == 0) throw std::logic_error("Error");

	items[index]->setPrice(newPrice);

}

void Shop::changeName(size_t index, const MyString& newName) 
{

	if (index > capacity || items[index] == nullptr || size == 0) throw std::logic_error("Error");

	items[index]->setName(newName);

}

void Shop::print() const
{

	for (int i = 0; i < capacity; i++)
	{

		if (items[i] != nullptr)
			items[i]->print();

	}

	std::cout << std::endl;

}

const Fruit* Shop::mostCalories() const 
{

	const Fruit* result = nullptr;
	size_t bestCalories = 0;

	for (int i = 0; i < capacity; i++)
	{

		if (items[i] != nullptr) 
		{

			if ((int)items[i]->getType() == 0 && items[i]->getCalories() > bestCalories)
			{

				bestCalories = items[i]->getCalories();
				result = const_cast<const Fruit*>(dynamic_cast<Fruit*>(items[i]));

			}

		}

	}

	return result;

}
