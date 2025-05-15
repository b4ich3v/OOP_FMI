#include <iostream>
#include "MyString.h"

template <class T>

class Optional 
{
private:

	union 
	{

		T value;
		uint8_t dummyParam;

	};

	bool hasValue = false;

public:

	Optional(): hasValue(false), dummyParam() {}

	Optional(const T& value) 
	{

		set_value(value);

	}

	~Optional() 
	{

		reset();

	}

	const T& operator * () const 
	{

		return value;

	}

	bool has_value() const 
	{

		return hasValue;

	}

	const T& get_value() const 
	{

		return value;

	}

	void set_value(const T& newValue)
	{

		if (has_value()) 
		{

			reset();

		}

		new (&value) T(newValue);
		hasValue = true;

	}
		
	void reset() 
	{

		if (!has_value()) return;
		value.~T();
		hasValue = false;

	}

};

int main() 
{
	
	Optional<int> optInt;
	if (!optInt.has_value()) std::cout << "Empty" << std::endl;

	optInt.set_value(42);
	if (optInt.has_value()) std::cout << "optInt = " << *optInt << std::endl;
	optInt.reset();

	std::cout << optInt.has_value() << std::endl;

	Optional<MyString> optStr("Hello");
	if (optStr.has_value()) std::cout << "optStr = " << optStr.get_value() << std::endl;

	optStr.reset();
	std::cout << optStr.has_value() << std::endl;

	struct Point 
	{
	public:

		int x, y;

		Point(int x, int y) : x(x), y(y) {}

	};

	Optional<Point> optP;
	optP.set_value(Point{ 3, 4 });

	if (optP.has_value()) 
	{

		Point p = *optP;
		std::cout << "optP = (" << p.x << ", " << p.y << ")" << std::endl;

	}

	return 0;

}


