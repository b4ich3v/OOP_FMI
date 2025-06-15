#include <iostream>

template <class T>

class MyVector 
{
private:

	T* data = nullptr;
	size_t size = 0;
	size_t capacity = 0;

	void free() 
	{

		delete[] data;
		data = nullptr;
		size = capacity = 0;

	}

	void copyFrom(const MyVector& other) 
	{

		data = new T[other.capacity];

		for (int i = 0; i < other.size; i++)
		{

			data[i] = other.data[i];

		}

		size = other.size;
		capacity = other.capacity;

	}

	void resize(size_t newCapacity) 
	{

		if (newCapacity <= capacity) return;

		T* newData = new T[newCapacity];

		for (int i = 0; i < size; i++)
		{

			newData[i] = data[i];

		}
		
		delete[] data;
		data = newData;
		capacity = newCapacity;

	}

	void moveTo(MyVector&& other) 
	{

		data = other.data;
		size = other.size;
		capacity = other.capacity;

		other.data = nullptr;
		other.size = 0;
		other.capacity = 0;

	}

public:

	MyVector() 
	{

		capacity = 8;
		size = 0;
		data = new T[capacity];

	}

	MyVector(const MyVector& other) 
	{

		copyFrom(other);

	}

	MyVector(MyVector&& other) noexcept 
	{

		moveTo(std::move(other));

	}

	MyVector& operator = (const MyVector& other) 
	{

		if (this != &other) 
		{

			free();
			copyFrom(other);

		}
		
		return *this;

	}

	MyVector& operator = (MyVector&& other) noexcept
	{

		if (this != &other)
		{

			free();
			moveTo(std::move(other));

		}

		return *this;

	}

	~MyVector() 
	{

		free();

	}

	const T& operator [](size_t index) const 
	{

		if (index >= size || index < 0) throw std::logic_error("Error");
		return data[index];

	}

	T& operator [](size_t index)
	{

		if (index >= size || index < 0) throw std::logic_error("Error");
		return data[index];

	}

	void push_back(const T& element) 
	{

		if (size == capacity) resize(capacity * 2);

		data[size++] = element;

	}

	void push_back(T&& element) noexcept
	{

		if (size == capacity) resize(capacity * 2);

		data[size++] = std::move(element);

	}

	void pop_back() 
	{

		if (size == 0) throw std::logic_error("Error");
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

class ArrayTransormer 
{
public:

	virtual void transform(int* arr, size_t size) const = 0;

	virtual ArrayTransormer* clone() const = 0;

	virtual ~ArrayTransormer() = default;

};

class ScalarTransformer: public ArrayTransormer
{
private:

	size_t scalar = 0;

public:

	ScalarTransformer(size_t scalar): ArrayTransormer(), scalar(scalar) {}

	void transform(int* arr, size_t size) const override
	{

		if (!arr) throw std::logic_error("Error");

		for (int i = 0; i < size; i++)
		{

			arr[i] *= scalar;

		}

	}

	ArrayTransormer* clone() const override 
	{

		return new ScalarTransformer(*this);

	}

};

class SwapTransformer: public ArrayTransormer
{
private:

	size_t left = 0;
	size_t right = 0;

public:

	SwapTransformer(size_t left, size_t right) : ArrayTransormer(), left(left), right(right) {}

	void transform(int* arr, size_t size) const override
	{

		if (!arr) throw std::logic_error("Error");
		if (left < 0 || right < 0 || left > right 
			|| left >= size || right >= size) throw std::logic_error("Error");
		
		std::swap(arr[left], arr[right]);

	}

	ArrayTransormer* clone() const override
	{

		return new SwapTransformer(*this);

	}

};

struct Pair 
{
public:

	size_t index = 0;
	int value = 0;

};

class ReplaceTransformer: public ArrayTransormer
{
private:

	MyVector<Pair> data;

	static bool validateIndex(size_t index, size_t size) 
	{

		return index >= 0 && index < size;

	}

public:

	ReplaceTransformer(const MyVector<Pair>& data): ArrayTransormer(), data(data) {}

	void transform(int* arr, size_t size) const override
	{

		if (!arr) throw std::logic_error("Error");
		
		for (int i = 0; i < data.getSize(); i++)
		{

			size_t index = data[i].index;
			int value = data[i].value;

			if (!validateIndex(index, size)) continue;
			arr[index] = value;

		}

	}

	ArrayTransormer* clone() const override
	{

		return new ReplaceTransformer(*this);

	}

};

template <class T>

class CriteriaTransformer: public ArrayTransormer
{
private:

	T object;

public:

	CriteriaTransformer(const T& object): ArrayTransormer(), object(object) {}

	void transform(int* arr, size_t size) const override
	{

		if (!arr) throw std::logic_error("Error");

		for (int i = 0; i < size; i++)
		{

			if (!object(arr[i])) arr[i] = -1;

		}

	}

	ArrayTransormer* clone() const override
	{

		return new CriteriaTransformer(*this);

	}

};

class Transformers 
{
private:

	ArrayTransormer** data = nullptr;
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

	void copyFrom(const Transformers& other) 
	{

		data = new ArrayTransormer * [other.capacity] {nullptr};
		size = other.size;
		capacity = other.capacity;

		for (int i = 0; i < capacity; i++)
		{

			if (other.data[i] == nullptr) continue;
			data[i] = other.data[i]->clone();

		}

	}

	void moveTo(Transformers&& other) 
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

		ArrayTransormer** newData = new ArrayTransormer * [newCapacity] {nullptr};

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

	Transformers() 
	{
		
		size = 0;
		capacity = 8;
		data = new ArrayTransormer * [capacity] {nullptr};

	}

	Transformers(const Transformers& other) 
	{

		copyFrom(other);

	}

	Transformers(Transformers&& other) noexcept
	{

		moveTo(std::move(other));

	}

	Transformers& operator = (Transformers&& other) noexcept
	{

		if (this != &other) 
		{

			free();
			moveTo(std::move(other));

		}

		return *this;

	}

	Transformers& operator = (const Transformers& other)
	{

		if (this != &other)
		{

			free();
			copyFrom(other);

		}

		return *this;

	}

	~Transformers() 
	{

		free();

	}

	void add(ArrayTransormer* tr) 
	{

		if (!tr) throw std::logic_error("Error");

		data[size++] = tr->clone();

	}

	void allTransformation(int* arr, size_t size) const
	{

		for (int i = 0; i < capacity; i++)
		{

			if (data[i] == nullptr) continue;
			data[i]->transform(arr, size);

		}

	}

	void intervalTransformation(int* arr, size_t size, size_t left, size_t right) const
	{

		if (left > right || left < 0 || right > capacity || !arr) throw std::logic_error("Error");

		for (int i = left; i < right; i++)
		{

			if (data[i] == nullptr) continue;
			data[i]->transform(arr, size);

		}

	}

	Transformers slice(size_t begin, size_t end) const 
	{

		if (begin > end || begin < 0 || end > capacity || end < 0) throw std::logic_error("Error");

		Transformers result;

		for (int i = begin; i < end; i++)
		{

			if (data[i] == nullptr) continue;
			result.add(data[i]);

		}

		return result;

	}

};

struct A 
{
public:

	bool operator ()(int number) const 
	{

		return number > 4;
			
	}

};

int main() 
{

	int arr[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	MyVector<Pair> pairs;
	pairs.push_back({ 1 , 15 });
	pairs.push_back({ 2 , 21 });
	pairs.push_back({ 3, -1 });

	A object;

	ArrayTransormer* scalarTransformer = new ScalarTransformer(7);
	ArrayTransormer* swapTransformer = new SwapTransformer(2, 5);
	ArrayTransormer* replaceTransformer = new ReplaceTransformer(pairs);
	ArrayTransormer* criteriaTransformer = new CriteriaTransformer<A>(object);

	Transformers transformers;
	transformers.add(scalarTransformer);
	transformers.add(swapTransformer);
	transformers.add(replaceTransformer);
	transformers.add(criteriaTransformer);
	transformers.allTransformation(arr, 10);

	Transformers sliced = transformers.slice(0, 1);

	for (int i = 0; i < 10; i++)
	{

		std::cout << arr[i] << " ";

	}

	delete scalarTransformer;
	delete swapTransformer;
	delete replaceTransformer;
	delete criteriaTransformer;

	return 0;

}
