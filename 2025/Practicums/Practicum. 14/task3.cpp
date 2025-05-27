#include <iostream>

class Base 
{
public:

	virtual Base* clone() const = 0;

	virtual ~Base() = default;

};

class Der1: public Base
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

class Der2: public Base
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

template <class T>

class PolymorphicPtr 
{
private:

	T* data = nullptr;

	void free() 
	{

		delete data;
		data = nullptr;

	}

	void moveTo(PolymorphicPtr&& other)
	{

		data = other.data;
		other.data = nullptr;

	}

	void copyFrom(const PolymorphicPtr& other) 
	{

		this->data = other.data->clone();

	}

public:

	PolymorphicPtr(const T* data) 
	{

		if (data == nullptr) throw std::logic_error("Error");
		this->data = new T(*data);

	}

	PolymorphicPtr(T* data)
	{

		if (data == nullptr) throw std::logic_error("Error");
		this->data = new T(*data);

	}

	PolymorphicPtr(const PolymorphicPtr& other) 
	{

		copyFrom(other);

	}

	PolymorphicPtr& operator = (const PolymorphicPtr& other) 
	{

		if (this != &other) 
		{

			free();
			copyFrom(other);

		}

		return *this;

	}

	PolymorphicPtr(PolymorphicPtr&& other) noexcept 
	{

		moveTo(std::move(other));

	}

	PolymorphicPtr& operator = (PolymorphicPtr&& other) noexcept 
	{

		if (this != &other) 
		{

			free();
			moveTo(std::move(other));

		}

		return *this;

	}

	~PolymorphicPtr() 
	{

		free();

	}

	const T* operator -> () const 
	{

		if (data == nullptr) throw std::logic_error("Error");
		return data;

	}

	T* operator -> () 
	{

		if (data == nullptr) throw std::logic_error("Error");
		return data;

	}

	const T& operator * () const
	{

		if (data == nullptr) throw std::logic_error("Error");
		return *data;

	}

	T& operator * () 
	{

		if (data == nullptr) throw std::logic_error("Error");
		return *data;

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
