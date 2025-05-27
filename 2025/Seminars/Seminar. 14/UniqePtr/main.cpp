#include "UniqePtr.hpp"

struct Example
{
public:

	Example() = default;

	void fictiveMethod() const
	{

		std::cout << "OOP" << std::endl;

	}

};

int main()
{

	UniqePtr<int> ptr1(new int(47));

	std::cout << *ptr1 << std::endl;
	*ptr1 = 7;
	std::cout << *ptr1 << std::endl;

	UniqePtr<Example> ptr(new Example());
	ptr->fictiveMethod();


	return 0;

}
