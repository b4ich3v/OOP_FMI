#include "Person.h"
#include <iostream>

int main()
{

	Person p1("Yoan Baychev", 20);
	Person p2("Ilian Zaprqnov", 21);
	Person p3("Kaloqn Markov", 21);
	Person p4("Ivailo Kunchev", 20);

	std::cout << p1.getName() << " " << p1.getAge() << std::endl;
	std::cout << p2.getName() << " " << p1.getAge() << std::endl;
	std::cout << p3.getName() << " " << p1.getAge() << std::endl;
	std::cout << p4.getName() << " " << p1.getAge() << std::endl;

	return 0;

}
