#include "PolymorphicPtr.hpp"

class Base
{
public:

	virtual Base* clone() const = 0;

	virtual ~Base() = default;

};

class Der1 : public Base
{
public:

	void der1() const
	{

		std::cout << "Der1" << std::endl;

	}

	Base* clone() const override
	{

		return new Der1();

	}

};

class Der2 : public Base
{
public:

	void der2() const
	{

		std::cout << "Der2" << std::endl;

	}

	Base* clone() const override
	{

		return new Der2();

	}

};

int main()
{

	PolymorphicPtr<Der1> ptr1(new Der1());
	ptr1->der1();

	PolymorphicPtr<Der2> ptr2(new Der2());
	ptr2->der2();

	return 0;

}

