#include "Shop.h"
#include "Vegetable.h"
#include "Fruit.h"

int main() 
{

	Fruit f1("Apple", "Red", 3.5, 300);
	Fruit f2("Orange", "Orange", 5.75, 124);
	Fruit f3("Banana", "Yellow", 12, 576);
	Fruit f4("F1", "F1", 5.75, 124);
	Fruit f5("F2", "F2", 12, 576);
	Fruit f6("F3", "F3", 5.75, 124);
	Fruit f7("F4", "F4", 12, 576);

	Vegetable v1("Brokoli", "Green", 4, 50);
	Vegetable v2("Something", "Idk", 10, 430);

	Shop shop;
	shop.addElement(&f1);
	shop.addElement(&f2);
	shop.addElement(&f3);
	shop.addElement(&f4);
	shop.addElement(&f5);
	shop.addElement(&f6);
	shop.addElement(&f7);
	shop.addElement(&v1);
	shop.addElement(&v2);
	shop.print();

	shop.removeElement(4);
	shop.print();

	shop.changeName(0, "Cool Apple");
	shop.print();

	shop.changePrice(0, 0);
	shop.print();

	const Fruit* bestFruit = shop.mostCalories();
	bestFruit->print();

	return 0;

}
