#include "studentCollection.h"

void StudentCollection::free()
{

	for (int i = 0; i < capacity; i++)
	{

		if(data[i] != nullptr)
		{

			delete data[i];

		}

	}

	delete[] data;

}

void StudentCollection::copyFrom(const StudentCollection& other)
{

	size = other.size;
	capacity = other.capacity;

	data = new Student* [capacity] {};

	for (size_t i = 0; i < capacity; i++)
	{

		if (other.data[i] != nullptr)
		{

			data[i] = new Student(*other.data[i]);

		}

	}

}

void StudentCollection::move(StudentCollection&& other)
{

	size = other.size;
	capacity = other.capacity;

	data = other.data;
	other.data = nullptr;

}

void StudentCollection::resize(int newCapacity)
{
	if (newCapacity <= capacity)
	{

		return;

	}

	Student** newData = new Student * [newCapacity] {};

	for (int i = 0; i < capacity; i++) 
	{

		newData[i] = data[i];

	}

	delete[] data;
	data = newData;
	capacity = newCapacity;

}

int StudentCollection::getFirstFreeIndex() const
{
	
	int index = 0;

	while (data[index] != nullptr)
	{

		index++;

	}

	if (index == capacity)
	{

		return capacity;

	}

	return index;

}

StudentCollection::StudentCollection()
{

	data = new Student* [capacity] {};
	size = 0;
	capacity = 25;

}

StudentCollection::StudentCollection(const StudentCollection& other)
{

	copyFrom(other);

}

StudentCollection& StudentCollection::operator = (const StudentCollection& other)
{

	if (this != &other)
	{

		free();
		copyFrom(other);

	}

	return *this;

}

void StudentCollection::pushAt(int index, const Student& other)
{

	if (index > capacity || index < 0)
	{

		return;

	}

	if (data[index] == nullptr)
	{

		data[index] = new Student(other);
		size++;

	}
	else
	{

		*data[index] = other;

	}

}

void StudentCollection::pushAt(int index, Student&& other) 
{

	if (index > capacity || index < 0)
	{

		return;

	}

	if (data[index] == nullptr)
	{

		data[index] = new Student(std::move(other));
		size++;

	}
	else
	{

		*data[index] = std::move(other);

	}

}

void StudentCollection::push(const Student& student)
{

	int index = getFirstFreeIndex();

	if (index == capacity)
	{

		resize(capacity + capacity / 2);

	}

	pushAt(index, student);

}

void StudentCollection::push(Student&& student)
{

	int index = getFirstFreeIndex();

	if (index == capacity)
	{

		resize(capacity + capacity / 2);

	}

	pushAt(index, std::move(student));

}

void StudentCollection::removeAt(int index) 
{

	if (index > capacity || index < 0)
	{

		return;

	}

	delete data[index];
	data[index] = nullptr;
	size--;

}

bool StudentCollection::contains(int index) const
{

	return data[index] != nullptr;

}

int StudentCollection::getSize() const 
{

	return size;

}

int StudentCollection::getCapacity() const 
{

	return capacity;

}

const Student& StudentCollection::at(int index) const
{

	if (!contains(index))
	{

		throw std::runtime_error("Error");

	}

	return *data[index];

}

StudentCollection& StudentCollection::operator = (StudentCollection&& other) noexcept 
{

	if (this != &other)
	{

		free();
		move(std::move(other));

	}

	return *this;

}

StudentCollection::StudentCollection(StudentCollection&& other) noexcept
{

	move(std::move(other));

}

StudentCollection::~StudentCollection() 
{

	free();

}
