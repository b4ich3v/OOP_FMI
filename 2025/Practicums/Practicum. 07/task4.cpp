#include "MyString.h"
#include <iostream>
#include <fstream>

enum class Status
{

	AVAILABLE = 0,
	UNAVAILABLE = 1

};

class Item 
{
private:

	MyString name;
	Status status = Status::AVAILABLE;
	double price = 0;

public:

	Item()
	{

		name = "default";
		status = Status::AVAILABLE;
		price = 0;

	}

	Item(const MyString& name, Status status, double price) 
	{

		this->name = name;
		this->status = status;
		this->price = price;

	}

	MyString getName() const
	{

		return name;

	}

	double getPrice() const 
	{

		return price;

	}

	void printItem() const 
	{

		std::cout << name;
		std::cout << price << " ";
		
		switch ((int)status)
		{

		case 0: std::cout << "AVAILABLE" << std::endl; break;
		case 1: std::cout << "UNAVAILABLE" << std::endl; break;
		default: break;
			
		}

	}

	void saveToBinary(std::ofstream& file) const 
	{

		int sizeOfName = name.getSize();
		int numberMask = (int)status;
		const char* namePtr = name.getData();

		file.write((const char*)&sizeOfName, sizeof(int));
		file.write((const char*)namePtr, sizeOfName * sizeof(char));
		file.write((const char*)&numberMask, sizeof(int));
		file.write((const char*)&price, sizeof(double));

	}

	void readFromBinary(std::ifstream& file) 
	{

		int sizeOfName = 0;
		int numberMask = 0;

		file.read((char*)&sizeOfName, sizeof(int));
		char* charName = new char[sizeOfName + 1];
		file.read((char*)charName, sizeOfName * sizeof(char));
		charName[sizeOfName] = '\0';

		MyString newName(charName);
		name = newName;

		file.read((char*)&numberMask, sizeof(int));
		status = (Status)numberMask;
		file.read((char*)&price, sizeof(double));

	}

};

class ShoppingCart 
{
private:

	Item* items = nullptr;
	int countOfItems = 0;
	int capacity = 8;

	void free() 
	{

		delete[] items;
		items = nullptr;
		countOfItems = 0;
		capacity = 8;

	}

	void copyFrom(const ShoppingCart& other) 
	{

		countOfItems = other.countOfItems;
		capacity = other.capacity;

		for (int i = 0; i < countOfItems; i++)
		{

			items[i] = other.items[i];

		}

	}

	void resize(int newCapacity)
	{

		if (newCapacity <= capacity) return;

		Item* newItems = new Item[newCapacity];

		for (int i = 0; i < countOfItems; i++)
		{

			newItems[i] = items[i];

		}

		delete[] items;
		items = newItems;
		capacity = newCapacity;

	}

public:

	ShoppingCart()
	{

		countOfItems = 0;
		capacity = 8;
		items = new Item[capacity];

	}

	ShoppingCart(const ShoppingCart& other)
	{

		copyFrom(other);

	}

	ShoppingCart& operator = (const ShoppingCart& other) 
	{

		if (this != &other)
		{

			free();
			copyFrom(other);

		}

		return *this;

	}

	~ShoppingCart()
	{

		free();

	}

	void addItem(const Item& item) 
	{

		if (countOfItems == capacity) resize(capacity * 2);

		items[countOfItems] = item;
		countOfItems += 1;

	}

	int itemsCount() const 
	{

		return countOfItems;

	}

	bool exists(const char* name) const 
	{

		for (int i = 0; i < countOfItems; i++)
		{

			if (!strcmp(items[i].getName().getData(), name)) 
			{

				return true;

			}

		}

		return false;

	}

	bool isEmpty() const 
	{

		return countOfItems == 0;

	}

	double getPriceOf(const char* name) const
	{

		for (int i = 0; i < countOfItems; i++)
		{

			if (!strcmp(items[i].getName().getData(), name)) 
			{

				return items[i].getPrice();

			}

		}

		return 0;

	}

	double totalPrice() const
	{

		double total = 0;

		for (int i = 0; i < countOfItems; i++)
		{

			total += items[i].getPrice();

		}

		return total;

	}

	void sortByName() 
	{

		for (int i = 0; i < countOfItems - 1; i++)
		{

			for (int j = 0; j < countOfItems - i - 1; j++)
			{

				if (strcmp(items[j].getName().getData(), items[j + 1].getName().getData()) > 0) 
				{

					std::swap(items[j], items[j + 1]);

				}

			}

		}

	}

	void printShopingCart() const 
	{

		for (int i = 0; i < countOfItems; i++)
		{

			items[i].printItem();
			std::cout << std::endl;

		}

		std::cout << std::endl;

	}

	void saveToBinary(const char* fileName) const
	{

		std::ofstream file(fileName, std::ios::binary);

		if (!file.is_open()) return;

		file.write((const char*)&countOfItems, sizeof(int));
		file.write((const char*)&capacity, sizeof(int));

		for (int i = 0; i < countOfItems; i++)
		{

			items[i].saveToBinary(file);

		}

		file.close();

	}

	void readFromBinary(const char* fileName) 
	{

		free();

		std::ifstream file(fileName, std::ios::binary);

		if (!file.is_open()) return;

		file.read((char*)&countOfItems, sizeof(int));
		file.read((char*)&capacity, sizeof(int));

		items = new Item[capacity];

		for (int i = 0; i < countOfItems; i++)
		{

			items[i].readFromBinary(file);

		}

		file.close();

	}

};

int main()
{

	Item item1("Milk", Status::AVAILABLE, 2);
	Item item2("Eggs", Status::AVAILABLE, 3);
	Item item3("Cola", Status::AVAILABLE, 1.50);
	Item item4("Bread", Status::AVAILABLE, 3.60);
	Item item5("Protein ice cream", Status::AVAILABLE, 4.75);

	ShoppingCart cart;
	cart.addItem(item1);
	cart.addItem(item2);
	cart.addItem(item3);
	cart.addItem(item4);
	cart.addItem(item5);
	cart.printShopingCart();

	std::cout << cart.exists("Cola") << std::endl;
	std::cout << cart.getPriceOf("Eggs") << std::endl;
	std::cout << cart.totalPrice() << std::endl << std::endl;

	cart.sortByName();
	cart.printShopingCart();
	cart.saveToBinary("file.dat");

	ShoppingCart newCart;
	newCart.readFromBinary("file.dat");
	newCart.printShopingCart();

	return 0;

}
