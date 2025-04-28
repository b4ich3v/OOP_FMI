#include "Bar.h"

int Bar::countOfSoldAlcDrinks = 0;
int Bar::countOfSoldNorDrinks = 0;

Bar::Bar(const Drink* const* drinks,
	int countOfNormalDrinks, int countOfAlcoholicDrinks, const bool* isAlcAtIndex) 
{

	this->capacity = 100;
	this->countOfDrinks = countOfNormalDrinks + countOfAlcoholicDrinks;
	this->overallCountOfSoldDrinks = 0;
	this->countOfAlcDrinks = countOfAlcoholicDrinks;
	this->countOfNorDrinks = countOfNormalDrinks;

	if (countOfAlcoholicDrinks + countOfNormalDrinks >= this->capacity)
		throw std::logic_error("Error");

	if(!drinks || !isAlcAtIndex) throw std::logic_error("Error");

	this->drinks = new Drink * [this->capacity] {nullptr};

	for (int i = 0; i < this->countOfDrinks; i++)			  
	{

		if (isAlcAtIndex[i]) this->drinks[i] = drinks[i]->clone();
		else this->drinks[i] = drinks[i]->clone();

	}

}

Bar::Bar(const Bar& other) 
{

	copyFrom(other);

}

Bar::Bar(Bar&& other) noexcept 
{

	moveTo(std::move(other));

}

Bar& Bar::operator = (const Bar& other) 
{

	if (this != &other) 
	{

		free();
		copyFrom(other);

	}

	return *this;

}

Bar& Bar::operator = (Bar&& other) noexcept 
{

	if (this != &other)
	{

		free();
		moveTo(std::move(other));

	}

	return *this;

}

Bar::~Bar() 
{

	free();
	
}

void Bar::printBar() const 
{

	for (int i = 0; i < countOfDrinks; i++)
	{

		drinks[i]->print();

	}

	std::cout << std::endl;

}

void Bar::free() 
{

	for (int i = 0; i < capacity; i++)
	{

		delete drinks[i];
		drinks[i] = nullptr;

	}

	delete[] drinks;
	drinks = nullptr;

	countOfDrinks = 0;
	overallCountOfSoldDrinks = 0;
	capacity = 100;
	countOfAlcDrinks = 0;
	countOfNorDrinks = 0;

}

void Bar::copyFrom(const Bar& other) 
{

	this->capacity = 100;
	this->countOfDrinks = other.countOfDrinks;
	this->overallCountOfSoldDrinks = other.overallCountOfSoldDrinks;
	this->countOfNorDrinks = other.countOfNorDrinks;
	this->countOfAlcDrinks = other.countOfAlcDrinks;

	this->drinks = new Drink * [this->capacity] { nullptr };

	for (int i = 0; i < this->countOfDrinks; i++)
	{

		this->drinks[i] = other.drinks[i]->clone();

	}

}

void Bar::moveTo(Bar&& other)
{

	this->drinks = other.drinks;
	this->countOfDrinks = other.countOfDrinks;
	this->countOfNorDrinks = other.countOfNorDrinks;
	this->countOfAlcDrinks = other.countOfAlcDrinks;
	this->overallCountOfSoldDrinks = other.overallCountOfSoldDrinks;
	this->capacity = other.capacity;

	other.drinks = nullptr;
	other.countOfDrinks = 0;
	other.countOfNorDrinks = 0;
	other.countOfAlcDrinks = 0;
	other.overallCountOfSoldDrinks = 0;
	other.capacity = 100;

}

void Bar::printStatistic() const 
{

	std::cout << "Count of Alc: " << countOfSoldAlcDrinks << std::endl;
	std::cout << "Count of Nor: " << countOfSoldNorDrinks << std::endl;
	std::cout << "Count of Ove: " << overallCountOfSoldDrinks << std::endl;
	std::cout << std::endl;

}

const Drink& Bar::getDrink()
{

	if (countOfAlcDrinks > countOfNorDrinks) 
	{

		for (int i = 0; i < countOfDrinks; i++)
		{

			if (AlcoholicDrink* resultDrink = dynamic_cast<AlcoholicDrink*>(drinks[i])) 
			{

				countOfSoldAlcDrinks += 1;
				overallCountOfSoldDrinks += 1;

				return *drinks[i];

			}

		}

		throw std::runtime_error("Error");

	}
	else
	{

		for (int i = 0; i < countOfDrinks; i++)
		{

			if (AlcoholicDrink* resultDrink = dynamic_cast<AlcoholicDrink*>(drinks[i]))
			{

				continue;

			}
			else
			{

				countOfSoldNorDrinks += 1;
				overallCountOfSoldDrinks += 1;

				return *drinks[i];

			}

		}

		throw std::runtime_error("Error");

	}

}
