#include <iostream>

template <class T>

class Queue 
{
private:

	T* data = nullptr;

	int get = 0;
	int put = 0;

	int size = 0;
	int capacity = 0;

	void free() 
	{

		delete[] data;
		data = nullptr;
		size = 0;
		get = put = 0;
		capacity = 8;

	}

	void moveTo(Queue&& other) 
	{

		data = other.data;
		size = other.size;
		get = other.get;
		put = other.put;
		capacity = other.capacity;

		other.data = nullptr;
		other.get = 0;
		other.put = 0;
		other.size = 0;
		other.capacity = 8;

	}

	void copyFrom(const Queue& other) 
	{
		
		data = new T[other.capacity];
		size = other.size;
		capacity = other.capacity;

		int index = other.get;

		for (int i = 0; i < other.size; i++)
		{

			data[i] = other.data[index];
			(++index) %= other.capacity;

		}

		get = 0;
		put = other.size;

	}

	void resize(int newCapacity) 
	{

		if (newCapacity <= capacity) return;

		T* newData = new T[newCapacity]{};
		int index = get;

		for (int i = 0; i < size; i++)
		{

			newData[i] = data[index];
			(++index) %= capacity;

		}

		delete[] data;
		data = newData;
		get = 0;
		put = size;
		capacity = newCapacity;

	}

public:

	Queue() 
	{

		get = put = 0;
		capacity = 8;
		data = new T[capacity]{};
		size = 0;

	}

	Queue(const Queue& other) 
	{

		copyFrom(other);

	}

	Queue(Queue&& other) noexcept
	{

		moveTo(std::move(other));

	}
	
	Queue& operator = (const Queue& other) 
	{

		if (this != &other) 
		{

			free();
			copyFrom(other);

		}

		return *this;

	}

	Queue& operator = (Queue&& other) noexcept
	{

		if (this != &other)
		{

			free();
			moveTo(std::move(other));

		}

		return *this;

	}

	~Queue() 
	{

		free();

	}

	void push(const T& element) 
	{

		if (size == capacity) resize(capacity * 2);

		data[put] = element;
		(++put) %= capacity;
		size += 1;

	}

	void pop()
	{

		if (isEmpty()) throw std::logic_error("Error");

		(++get) %= capacity;
		size -= 1;

	}

	bool isEmpty() const 
	{

		return size == 0;

	}

	const T& front() const 
	{

		if (isEmpty()) throw std::logic_error("Error");
		return data[get];

	}

};

int main()
{

	Queue<int> q1;
	
	for (int i = 0; i < 10; i++)
	{

		q1.push(i);

	}

	std::cout << q1.front() << std::endl;
	q1.pop();
	std::cout << q1.front() << std::endl << std::endl;
	
	while (!q1.isEmpty()) 
	{

		std::cout << q1.front() << " ";
		q1.pop();

	}

	return 0;

}

