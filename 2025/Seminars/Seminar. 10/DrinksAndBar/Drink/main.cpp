#include <iostream>
#include "Drink.h" 

int main() 
{
    
    Drink water("Water", 0.5);
    std::cout << water.getName() << " " << water.getQuantity() << std::endl;

    Drink juice = water;
    std::cout << juice.getName() << " " << juice.getQuantity() << std::endl;

    Drink soda = Drink("Soda", 1.0);
    std::cout << soda.getName() << " " << soda.getQuantity() << std::endl;

    Drink coffee;
    coffee = water;
    std::cout << coffee.getName() << " " << coffee.getQuantity() << std::endl;

    Drink tea;
    tea = Drink("Tea", 0.3);
    std::cout << tea.getName() << " " << tea.getQuantity() << std::endl;

    return 0;

}

