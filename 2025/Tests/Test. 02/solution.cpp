#include <iostream>
#include <cstring>
#include <cmath>

namespace HELPERS 
{

	static bool isDigit(char ch) 
	{

		return ch >= '0' && ch <= '9';

	}

}

class Vector2D 
{
private:

	double x = 0;
	double y = 0;

public:

	Vector2D(): x(0), y(0) {}

	Vector2D(double x, double y) : x(x), y(y) {}

	Vector2D& operator += (const Vector2D& other) 
	{

		x += other.getX();
		y += other.getY();

		return *this;

	}

	friend Vector2D operator + (const Vector2D& v1, const Vector2D& v2)
	{

		double newX = v1.getX() + v2.getX();
		double newY = v1.getY() + v2.getY();

		return Vector2D(newX, newY);

	}

	friend Vector2D operator * (const Vector2D& v1, double scalar) 
	{

		double newX = v1.getX() * scalar;
		double newY = v1.getY() * scalar;

		return Vector2D(newX, newY);

	}

	friend Vector2D operator * (double scalar, const Vector2D& v1)
	{

		double newX = v1.getX() * scalar;
		double newY = v1.getY() * scalar;

		return Vector2D(newX, newY);

	}

	friend double operator ^ (const Vector2D& v1, const Vector2D& v2)
	{

		return sqrt(v1.getX() * v2.getX() + v1.getY() * v2.getY());

	}

	friend bool operator == (const Vector2D& v1, const Vector2D& v2) 
	{

		return (v1.getX() == v2.getX()) && (v1.getY() == v2.getY());
			 
	}

	friend bool operator != (const Vector2D& v1, const Vector2D& v2)
	{

		return !(v1 == v2);

	}

	double getX() const 
	{

		return x;

	}

	double getY() const
	{

		return y;

	}

};

class MyCustomString
{
private:

	char* data = nullptr;
	size_t size = 0;
	size_t capacity = 0;

	void free()
	{

		delete[] data;
		data = nullptr;
		size = capacity = 0;

	}

	void copyFrom(const MyCustomString& other)
	{

		data = new char[other.capacity];
		strcpy(data, other.data);
		size = other.size;
		capacity = other.capacity;

	}

	void moveTo(MyCustomString&& other)
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

		char* newData = new char[newCapacity];
		strcpy(newData, data);

		delete[] data;
		data = newData;
		capacity = newCapacity;

	}

public:

	MyCustomString() : MyCustomString("") {}

	MyCustomString(const char* str)
	{

		if (!str) throw std::logic_error("Error");

		capacity = strlen(str) * 2;
		size = strlen(str);
		data = new char[capacity];
		strcpy(data, str);

	}

	MyCustomString(const MyCustomString& other)
	{

		copyFrom(other);

	}

	MyCustomString(MyCustomString&& other) noexcept
	{

		moveTo(std::move(other));

	}

	MyCustomString& operator = (const MyCustomString& other)
	{

		if (this != &other)
		{

			free();
			copyFrom(other);

		}

		return *this;

	}

	MyCustomString& operator = (MyCustomString&& other) noexcept
	{

		if (this != &other)
		{

			free();
			moveTo(std::move(other));

		}

		return *this;

	}

	~MyCustomString()
	{

		free();

	}

	const char& operator [](size_t index) const
	{

		if (index >= size) throw std::logic_error("Error");
		return data[index];

	}

	char& operator [](size_t index)
	{

		if (index >= size) throw std::logic_error("Error");
		return data[index];

	}

	size_t getSize() const 
	{

		return size;

	}

	friend std::ostream& operator << (std::ostream& os, const MyCustomString& str)
	{

		os << str.data;
		return os;

	}

};

class Peak 
{
protected:

	MyCustomString nameOfMontain;
	double height;

public:

	Peak(const MyCustomString& nameOfMontain, double height): nameOfMontain(nameOfMontain), height(height) {}

	virtual void print() const = 0;

	virtual ~Peak() = default;

};

class TPeak: public Peak 
{
private:

	MyCustomString nameOfPeak;

public:

	TPeak(const MyCustomString& nameOfMontain, double height, const MyCustomString& nameOfPeak):
		Peak(nameOfMontain, height), nameOfPeak(nameOfPeak) {}

	void print() const override 
	{

		std::cout << nameOfMontain << " " << nameOfPeak << " " << height << std::endl;

	}

};

class MPeak: public Peak
{
private:

	MyCustomString numberOfKota;

	bool static validateFormat(const MyCustomString& str)  
	{

		bool digitFound = false;

		for (int i = 0; i < str.getSize(); i++)
		{

			if (HELPERS::isDigit(str[i])) 
			{

				digitFound = true;

				while (i < str.getSize()) 
				{

					if (!HELPERS::isDigit(str[i])) return false;

					i += 1;

				}

				break;

			}

		}

		return digitFound;

	}

public:

	MPeak(const MyCustomString& nameOfMontain, double height, const MyCustomString& numberOfKota) :
		Peak(nameOfMontain, height), numberOfKota(numberOfKota) 
	{

		if (!validateFormat(numberOfKota)) throw std::logic_error("Error");

	}

	void print() const override
	{

		std::cout << nameOfMontain << " " << numberOfKota << " " << height << std::endl;

	}

};

int main() 
{

	Vector2D v1(0, 1);
	Vector2D v2(1, 0);
	Vector2D v3 = v1 + v2;
	Vector2D v4 = v3 * 3.14;

	double result = v3 ^ v1;

	std::cout << v3.getX() << " " << v3.getY() << std::endl;
	std::cout << v4.getX() << " " << v4.getY() << std::endl;
	std::cout << result << std::endl;

	Peak* peak1 = new TPeak("Rila", 2925, "Musala");
	Peak* peak2 = new MPeak("Stara Planina", 2014, "Kota 54291");

	peak1->print();
	peak2->print();

	delete peak1;
	delete peak2;

	return 0;

}
