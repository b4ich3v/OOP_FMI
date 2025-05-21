#include <iostream>

struct Point 
{
public:

	int x = 0;
	int y = 0;
	int z = 0;

	Point() = default;

	explicit Point(int x, int y, int z): x(x), y(y), z(z) {}

	friend bool operator != (const Point& p1, const Point& p2) 
	{

		return p1.x != p2.x || p1.y != p2.y || p1.z != p2.z;

	}

	void print() const 
	{

		std::cout << "( ";
		std::cout << x << " " << y << " " << z;
		std::cout << " )" << std::endl;

	}

};

template <class T>

class Vector 
{
private:

	T* data = nullptr;
	size_t capacity = 0;
	size_t size = 0;

	void free() 
	{

		delete[] data;
		data = nullptr;
		size = 0;
		capacity = 0;

	}

	void copyFrom(const Vector& other) 
	{

		this->data = new T[other.capacity]{};
		this->size = other.size;
		this->capacity = other.capacity;

		for (int i = 0; i < size; i++)
		{

			this->data[i] = other.data[i];

		}

	}

	void moveTo(Vector&& other)
	{

		this->data = other.data;
		this->size = other.size;
		this->capacity = other.capacity;

		other.data = nullptr;
		other.size = 0;
		other.capacity = 0;

	}

	void resize(size_t newCapacity) 
	{

		if (newCapacity <= capacity) return;

		T* newData = new T[newCapacity]{};

		for (int i = 0; i < size; i++)
		{

			newData[i] = data[i];

		}
		
		delete[] data;
		data = newData;
		capacity = newCapacity;

	}

public:

	Vector() 
	{

		size = 0;
		capacity = 8;
		data = new T[capacity]{};

	}

	Vector(const Vector& other)
	{

		copyFrom(other);

	}

	Vector(Vector&& other) noexcept 
	{

		moveTo(std::move(other));

	}

	Vector& operator = (const Vector& other)
	{
		
		if (this != &other) 
		{

			free();
			copyFrom(other);

		}

		return *this;

	}

	Vector& operator = (Vector&& other) noexcept
	{

		if (this != &other)
		{

			free();
			moveTo(std::move(other));

		}

		return *this;

	}

	~Vector() 
	{

		free();

	}

	void push_back(const T& element)
	{

		if (size == capacity) resize(capacity * 2);

		data[size] = element;
		size += 1;

	}

	void push_back(T&& element)
	{

		if (size == capacity) resize(capacity * 2);

		data[size] = std::move(element);
		size += 1;

	}

	void pop_back() 
	{

		if (size == 0) throw std::logic_error("Error");

		size -= 1;

	}

	const T& operator [] (size_t index) const 
	{

		if (index >= capacity) throw std::logic_error("Error");
		return data[index];

	}

	T& operator [] (size_t index) 
	{

		if (index >= capacity) throw std::logic_error("Error");
		return data[index];

	}

	size_t getSize() const 
	{

		return size;

	}

	size_t getCapcity() const
	{

		return capacity;

	}

	void publicResize() 
	{

		resize(capacity * 2);

	}

	void incrementSize() 
	{

		size += 1;

	}

};

class ArrayOfPoints 
{
private:

	Vector<Point> data;

public:

	void setPoint(const Point& point, size_t index) 
	{

		if (index >= data.getCapcity()) data.publicResize();

		data[index] = point;
		data.incrementSize();

	}

	size_t getCountOfPoints() const
	{

		return data.getSize();

	}

	friend ArrayOfPoints unionOfTwo(const ArrayOfPoints& arr1, const ArrayOfPoints& arr2)
	{

		struct LocalPair 
		{
		public:

			int index = 0;
			bool used = false;

		};

		ArrayOfPoints result;
		int index = 0;

		for (int i = 0; i < arr1.getCountOfPoints(); i++)
		{

			Vector<LocalPair> forbidenIndexes;

			for (int j = 0; j < arr2.getCountOfPoints(); j++)
			{

				if (arr1.data[i] != arr2.data[j]) continue;
				forbidenIndexes.push_back({i ,true});
				break;

			}

			if (forbidenIndexes[i].used) continue;
			result.setPoint(arr1.data[i], index);
			index += 1;

		}

		for (int i = 0; i < arr2.getCountOfPoints(); i++)
		{

			Vector<LocalPair> forbidenIndexes;

			for (int j = 0; j < arr1.getCountOfPoints(); j++)
			{

				if (arr2.data[i] != arr1.data[j]) continue;
				forbidenIndexes.push_back({ i ,true });
				break;

			}

			if (forbidenIndexes[i].used) continue;
			result.setPoint(arr2.data[i], index);
			index += 1;

		}

		return result;

	}

	void printArray() const 
	{

		for (int i = 0; i < data.getSize(); i++)
		{

			data[i].print();

		}

		std::cout << std::endl;

	}

};

int main() 
{

	Point p1(1, 2, 3), p2(1, 2, 3), p3(4, 5, 6);
	std::cout << (p1 != p2) << std::endl;  
	std::cout << (p1 != p3) << std::endl; 

	ArrayOfPoints a1, a2;
	std::cout << a1.getCountOfPoints() << " " << a2.getCountOfPoints() << std::endl; 

	a1.setPoint(p1, 0);
	a1.setPoint(p2, 1);
	a1.setPoint(p3, 2);
	a1.printArray();

	a2.setPoint(p2, 0);
	a2.setPoint(Point(0, 1, 23), 1);
	a2.setPoint(Point(-11, 1, -2), 2);
	a2.setPoint(Point(-1, -1, -1), 3);
	a2.printArray();

	ArrayOfPoints result = unionOfTwo(a1, a2);
	result.printArray();

	return 0;

}

