#include <iostream>
#include <fstream>

class Base 
{
public:

	virtual Base* clone() const = 0;

	virtual void print() const = 0;

	virtual ~Base() = default;

};

class Der1: public Base 
{
public:

	void print() const override 
	{

		std::cout << "Der1" << std::endl;

	}

	Base* clone() const override 
	{

		return new Der1(*this);

	}

};

class Der2: public Base
{
public:

	void print() const override
	{

		std::cout << "Der2" << std::endl;

	}

	Base* clone() const override
	{

		return new Der2(*this);

	}

};

template <class T>

class PolyContainer
{
private:

	T** data = nullptr;
	size_t size = 0;
	size_t capacity = 0;

	void free()
	{

		for (int i = 0; i < capacity; i++)
		{

			if (data[i] == nullptr) continue;

			delete data[i];
			data[i] = nullptr;

		}

		delete[] data;
		data = nullptr;
		size = capacity = 0;

	}

	void copyFrom(const PolyContainer& other)
	{

		data = new T * [other.capacity] {nullptr};
		size = other.size;
		capacity = other.capacity;

		for (int i = 0; i < capacity; i++)
		{

			if (other.data[i] == nullptr) continue;

			data[i] = other.data[i]->clone();

		}

	}

	void moveTo(PolyContainer&& other)
	{

		data = other.data;
		size = other.size;
		capacity = other.capacity;

		other.data = nullptr;
		other.size = 0;
		other.capacity = 0;

	}

	void resize(size_t newCapacity)
	{

		if (newCapacity <= capacity) return;

		T** newData = new T * [newCapacity] {nullptr};

		for (int i = 0; i < capacity; i++)
		{

			newData[i] = data[i];
			data[i] = nullptr;

		}

		delete[] data;
		data = newData;
		capacity = newCapacity;

	}

public:

	PolyContainer()
	{

		capacity = 8;
		size = 0;
		data = new T * [capacity] { nullptr };

	}

	PolyContainer(const PolyContainer& other)
	{

		copyFrom(other);

	}

	PolyContainer(PolyContainer&& other) noexcept
	{

		moveTo(std::move(other));

	}

	PolyContainer& operator = (const PolyContainer& other)
	{

		if (this != &other)
		{

			free();
			copyFrom(other);

		}

		return *this;

	}

	PolyContainer& operator = (PolyContainer&& other) noexcept
	{

		if (this != &other)
		{

			free();
			moveTo(std::move(other));

		}

		return *this;

	}

	~PolyContainer()
	{

		free();

	}

	const T* operator [](size_t index) const
	{

		if (index >= size || data[index] == nullptr) throw std::logic_error("Error");
		return data[index];

	}

	T*& operator [](size_t index)
	{

		if (index >= size || data[index] == nullptr) throw std::logic_error("Error");
		return data[index];

	}

	void push_back(T* element)
	{

		if (!element) throw std::logic_error("Error");
		if (size == capacity) resize(capacity * 2);

		data[size++] = element->clone();

	}

	void push_back(T* element, size_t index)
	{

		if (!element || index >= capacity) throw std::logic_error("Error");
		if (size == capacity) resize(capacity * 2);

		data[index] = element->clone();
		size += 1;

	}

	void pop_back()
	{

		if (!size) throw std::logic_error("Error");
		delete data[size - 1];
		data[size - 1] = nullptr;
		size -= 1;

	}

	size_t getSize() const
	{

		return size;

	}

	size_t getCapacity() const
	{

		return capacity;

	}

};

int main() 
{

	Base* d1 = new Der1();
	Base* d2 = new Der2();

	PolyContainer<Base> container;
	container.push_back(d1);
	container.push_back(d2);

	container[0]->print();
	container[1]->print();

	container.pop_back();
	container[0]->print();

	try
	{

		container[1]->print();

	}
	catch (const std::exception& e)
	{

		std::cout << "Deleted" << std::endl;

	}

	return 0;

}
