#include <iostream>
#include <fstream>
#include <cstring>

namespace CONSTANTS
{

	const int MAX_SIZE_BRAND = 1024;
	const int DEFAULT_PRICE = 0;
	const char* DEFAULT_BRAND = "Unknown";

}

enum class Taste 
{

	BLUEBERRY = 0,
	QUEEN = 1,
	MANGO = 2,
	APPLE = 3,
	COLA = 4

};

class Narga 
{
private:

	double price;
	char brand[CONSTANTS::MAX_SIZE_BRAND + 1];
	Taste taste;

	void setPrice(double price)
	{

		if (price < 0) return;

		this->price = price;

	}

	void setBrand(const char* brand)
	{

		if (!brand) return;

		strncpy(this->brand, brand, strlen(brand));
		this->brand[strlen(brand)] = '\0';

	}

	void setTaste(Taste taste) 
	{

		this->taste = taste;

	}

public:

	Narga()
	{
		
		setPrice(CONSTANTS::DEFAULT_PRICE);
		setBrand(CONSTANTS::DEFAULT_BRAND);
		setTaste(Taste::APPLE);
			
	}

	Narga(double price, const char* brand, Taste taste) 
	{

		setPrice(price);
		setBrand(brand);
		setTaste(taste);

	}

	void readFromConsole()
	{

		std::cin >> price;
		std::cin.ignore();
		std::cin.getline(brand, CONSTANTS::MAX_SIZE_BRAND);
		
		int number = 0;
		std::cin >> number;
		taste = (Taste)number;

	}

	void print() const
	{

		std::cout << price << " ";
		std::cout << brand << " ";

		switch (taste)
		{

		case Taste::BLUEBERRY: std::cout << "BLUEBERRY "; break;
		case Taste::QUEEN: std::cout << "QUEEN "; break;
		case Taste::MANGO: std::cout << "MANGO "; break;
		case Taste::APPLE: std::cout << "APPLE "; break;
		case Taste::COLA: std::cout << "COLA "; break;
		default: break;
			
		}

		std::cout << std::endl;

	}

	const char* getBrand() const 
	{

		return brand;

	}

	double getPrice() const 
	{

		return price;

	}

	Taste getTaste() const 
	{

		return taste;

	}

};

int main() 
{

	Narga n1(27, "Joni", Taste::BLUEBERRY);
	Narga n2(20, "Bravo", Taste::APPLE);

	Narga n3;
	n3.readFromConsole();

	n1.print();
	n2.print();
	n3.print();

	return 0;

}
