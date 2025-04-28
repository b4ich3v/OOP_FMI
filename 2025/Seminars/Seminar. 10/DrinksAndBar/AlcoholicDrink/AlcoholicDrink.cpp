#include "AlcoholicDrink.h"

AlcoholicDrink::AlcoholicDrink(const char* name, double quantity, 
	double alcPer) : Drink(name, quantity) 
{

	this->alcPer = alcPer;

}

double AlcoholicDrink::getAlcPer() const 
{

	return alcPer;

}

void AlcoholicDrink::print() const 
{

	std::cout << alcPer << " ";
	Drink::print();

}

Drink* AlcoholicDrink::clone() const 
{

	return new AlcoholicDrink(*this);

}
