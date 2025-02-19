#include <iostream>

enum class DrinkIndexes : uint8_t
{

	Whiskey = 0,
	Vodka = 1,
	Cola = 2,
	Fanta = 3,
	Water = 4,
	Wine = 5,
	Rum = 6,
	Juice = 7

};

struct Client
{
public:

	char name[32];
	uint8_t likedDrinks;

};

bool isClientLikesTheDrink(const Client& cl, DrinkIndexes drink) 
{

	return (cl.likedDrinks & (1 << (int)drink)) != 0;

}

void getToIt(Client& cl, DrinkIndexes drink)
{

	cl.likedDrinks |= (1 << (int)drink);

}

void deslike(Client& cl, DrinkIndexes drink)
{

	cl.likedDrinks &= (~(1 << (int)drink));

}

void printAllDrinksHeLike(const Client& cl)
{

	bool pred = false;

	for (int i = 0; i < 8; i++)
	{

		if ((cl.likedDrinks & (1 << i)) != 0)
		{

			pred = true;

			switch (i)
			{

			case 0: std::cout << "Vodka"; break;
			case 1: std::cout << "Wiskey"; break;
			case 2: std::cout << "Cola"; break;
			case 3: std::cout << "Fanta"; break;
			case 4: std::cout << "Water"; break;
			case 5: std::cout << "Wine"; break;
			case 6: std::cout << "Rum"; break;
			case 7: std::cout << "Juice"; break;
			default: break;

			}

		}

	}

	if(pred) std::cout<<"None";

}
