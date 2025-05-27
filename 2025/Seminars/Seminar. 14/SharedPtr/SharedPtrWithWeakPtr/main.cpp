#include "SharedPtr.hpp"

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

	SharedPtr<int> ptr1(new int(47));
	SharedPtr<int> ptr2 = ptr1;
	SharedPtr<int> ptr3 = ptr1;
	SharedPtr<int> ptr4 = ptr1;

	std::cout << ptr1.getRefCount() << " " << ptr2.getRefCount() << " "
		<< ptr3.getRefCount() << " " << ptr4.getRefCount() << std::endl;

	std::cout << *ptr1 << std::endl;
	std::cout << *ptr2 << std::endl;
	std::cout << *ptr3 << std::endl;
	std::cout << *ptr4 << std::endl;

	SharedPtr<Example> ptr(new Example());
	ptr->fictiveMethod();


	return 0;

}
