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
		data = new T*[capacity]{ nullptr };

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
