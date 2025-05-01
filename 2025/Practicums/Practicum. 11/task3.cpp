#include <iostream>

class IntSet
{
public:

	virtual bool member(int x) const = 0;

	virtual int get(int index) const = 0;

	virtual bool isSubsetOf(const IntSet* other) const = 0;

	virtual bool intersects(const IntSet* other) const = 0;

	virtual void printSet() const = 0;

};

class IntRange: public IntSet 
{
private:

	int start = 0;
	int end = 0;

public:

	IntRange(): IntRange(0,0) {}

	IntRange(int start, int end) 
	{

		if (start >= end) throw std::logic_error("Error");

		this->start = start;
		this->end = end;

	}

	bool member(int number) const override
	{

		return number > start && number < end;

	}

	int get(int index) const override 
	{

		int actualIndex = index + start;

		if (actualIndex >= end) throw std::logic_error("Error");
		else return start + index;

	}

	bool isSubsetOf(const IntSet* other) const override
	{

		for (int i = start + 1; i < end; i++)
		{

			if (!other->member(i)) return false;

		}

		return true;

	}

	bool intersects(const IntSet* other) const override 
	{

		for (int i = start + 1; i < end; i++)
		{

			if (other->member(i)) return true;

		}

		return false;

	}

	void printSet() const override 
	{

		for (int i = start + 1; i < end; i++)
		{

			std::cout << i << " ";

		}

		std::cout << std::endl;

	}

};

struct IntPair 
{
public:

	int value = INT_MAX;
	bool hasValue = false;

};

class ArraySet: public IntSet
{
private:

	IntPair* array = nullptr;
	int size = 0;

	void free() 
	{
		
		delete[] array;
		array = nullptr;
		size = 0;

	}

	void copyFrom(const ArraySet& other) 
	{

		this->array = new IntPair[other.size];
		this->size = other.size;

		for (int i = 0; i < size; i++)
		{

			this->array[i] = other.array[i];

		}

	}
	
	void moveTo(ArraySet&& other) 
	{

		this->array = other.array;
		this->size = other.size;

		other.array = nullptr;
		other.size = 0;

	}

	int findIndex(bool forRemoving = false, int number = INT_MAX) const 
	{

		if (forRemoving) 
		{

			for (int i = 0; i < size; i++)
			{

				if (array[i].value == number && array[i].hasValue) return i;

			}

			return -1;

		}

		for (int i = 0; i < size; i++)
		{

			if (!array[i].hasValue) return i;

		}

		return -1;

	}

public:

	ArraySet(): ArraySet(10) {}

	ArraySet(int number) 
	{

		if (number <= 0) throw std::logic_error("Error");

		this->size = number;
		this->array = new IntPair[number];

	}

	ArraySet(const IntPair* array, int size)
	{

		if (!array || size <= 0) throw std::logic_error("Error");

		this->array = new IntPair[size];
		this->size = size;

		for (int i = 0; i < size; i++)
		{

			this->array[i] = array[i];

		}

	}

	ArraySet(const ArraySet& other) 
	{

		copyFrom(other);

	}

	ArraySet(ArraySet&& other) noexcept
	{

		moveTo(std::move(other));

	}

	ArraySet& operator = (const ArraySet& other) 
	{

		if (this != &other) 
		{

			free();
			copyFrom(other);

		}

		return *this;

	}

	ArraySet& operator = (ArraySet&& other) noexcept
	{

		if (this != &other)
		{

			free();
			moveTo(std::move(other));

		}

		return *this;

	}

	~ArraySet()
	{

		free();

	}

	bool member(int number) const override
	{

		for (int i = 0; i < size; i++)
		{

			if (array[i].value == number && array[i].hasValue) return true;

		}

		return false;

	}

	int get(int index) const override
	{

		if (index >= size || index < 0 || 
			!array[index].hasValue) throw std::logic_error("Error");

		return array[index].value;

	}

	bool isSubsetOf(const IntSet* other) const override
	{

		for (int i = 0; i < size; i++)
		{

			if (!other->member(array[i].value)) return false;

		}

		return true;

	}

	bool intersects(const IntSet* other) const override
	{

		for (int i = 0; i < size; i++)
		{

			if (other->member(array[i].value)) return true;

		}

		return false;

	}

	bool insert(int number) 
	{

		int index = findIndex();
		if (index == -1) return false;

		array[index].value = number;
		array[index].hasValue = true;

		return true;

	}

	bool remove(int number) 
	{

		int index = findIndex(true, number);
		if (index == -1) return false;

		array[index].value = INT_MAX;
		array[index].hasValue = false;

		return true;

	}

	void printSet() const override 
	{

		for (int i = 0; i < size; i++)
		{

			if (array[i].hasValue) std::cout << array[i].value << " ";

		}

		std::cout << std::endl;

	}

};

int main()
{

	ArraySet a(5);
	a.insert(3);
	a.insert(5);
	a.insert(8);
	a.printSet();

	ArraySet b(5);
	b.insert(5);
	b.insert(8);
	b.printSet();

	IntRange r1(2, 6); 
	r1.printSet();

	IntRange r2(10, 15); 
	r2.printSet();

	std::cout << a.member(5) << std::endl;
	std::cout << r1.member(6) << std::endl;

	std::cout << a.intersects(&r1) << std::endl; 
	std::cout << a.intersects(&r2) << std::endl; 

	std::cout << b.isSubsetOf(&a) << std::endl;
	std::cout << a.isSubsetOf(&r1) << std::endl;

	std::cout << std::endl;
	a.remove(5);
	a.printSet();

	std::cout << a.member(5) << std::endl;
	std::cout << a.intersects(&r1) << std::endl;

	return 0;

}



