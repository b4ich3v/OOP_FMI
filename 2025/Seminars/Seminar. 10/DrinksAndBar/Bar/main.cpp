#include <iostream>
#include "Bar.h"

int main()
{
    
    Drink* normalDrink1 = new Drink("Water", 0.5);
    Drink* normalDrink2 = new Drink("Juice", 0.3);
    AlcoholicDrink* alcDrink1 = new AlcoholicDrink("Beer", 0.5, 5.0);
    AlcoholicDrink* alcDrink2 = new AlcoholicDrink("Wine", 0.75, 12.5);

    const Drink* drinks[] = { normalDrink1, alcDrink1, normalDrink2, alcDrink2 };
    bool isAlcoholic[] = { false, true, false, true };

    try
    {

        Bar bar(drinks, 2, 2, isAlcoholic);

        std::cout << "Drinks in the bar:" << std::endl;
        bar.printBar();

        std::cout << "Statistics before serving:" << std::endl;
        bar.printStatistic();

        const Drink& selectedDrink = bar.getDrink();
        std::cout << selectedDrink.getName()
            << " " << selectedDrink.getQuantity() << std::endl;

        std::cout << "Statistics after serving:" << std::endl;
        bar.printStatistic();

    }
    catch (const std::exception& e)
    {

        std::cout << e.what() << std::endl;

    }

    delete normalDrink1;
    delete normalDrink2;
    delete alcDrink1;
    delete alcDrink2;

    return 0;

}

