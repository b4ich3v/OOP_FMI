#include <iostream>
#include "AlcoholicDrink.h"

int main() 
{
    
    AlcoholicDrink wine("Wine", 0.75, 12.5);
    std::cout << wine.getName() << " " << wine.getQuantity() << " "
        << wine.getAlcPer() << std::endl;

    AlcoholicDrink beer("Beer", 0.5, 5.0);

    std::cout << beer.getName() << " " << beer.getQuantity() << " "
        << beer.getAlcPer() << std::endl;

    return 0;

}

