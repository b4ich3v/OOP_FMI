#include <iostream>

enum class Choice
{

	CHAR = 0,
	INT = 1,
	DOUBLE = 2,
	RUN_TIME_ERROR = 3,
	OUT_OF_RANGE = 4,
	LOGIC_ERROR = 5

};

void throwSomething() 
{

	std::cout << "0 is for CHAR" << std::endl;
	std::cout << "1 is for INT" << std::endl;
	std::cout << "2 is for DOUBLE" << std::endl;
	std::cout << "3 is for RUN_TIME_ERROR" << std::endl;
	std::cout << "4 is for OUT_OF_RANGE" << std::endl;
	std::cout << "5 is for LOGIC_ERROR" << std::endl;

	int clientChoice = 0;
	std::cin >> clientChoice;
	Choice realChoice = (Choice)clientChoice;

	switch (realChoice)
	{

	case Choice::CHAR: throw 'a'; break;
	case Choice::INT: throw - 1; break;
	case Choice::DOUBLE: throw - 1.0; break;
	case Choice::RUN_TIME_ERROR: throw std::runtime_error("Error"); break;
	case Choice::OUT_OF_RANGE: throw std::out_of_range("Error"); break;
	case Choice::LOGIC_ERROR: throw std::logic_error("Error"); break;
	default: break;
		
	}

}

void caller()
{

	try
	{

		throwSomething();

	}
	catch (int)
	{

		std::cout << "Caught int" << std::endl;

	}
	catch (double) 
	{

		std::cout << "Caught dobule" << std::endl;

	}

}

int main()
{


	try
	{

		caller();

	}
	catch (const std::out_of_range& e)
	{

		std::cout << "Caught out_of_range" << std::endl;

	}
	catch (const std::exception& e)
	{

		std::cout << "Caught exception" << std::endl;

	}
	catch (...)
	{

		std::cout << "Caught ..." << std::endl;

	}

	return 0;

}
