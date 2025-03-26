#include <iostream>
#include <cstring>
#include <cmath>

class Nvector
{
private:

	int* coordinates = nullptr;
	int size = 0;

	void copyFrom(const Nvector& other) 
	{

		coordinates = new int[other.size];
		size = other.size;

		for (int i = 0; i < size; i++)
		{

			coordinates[i] = other.coordinates[i];

		}

	}

	void free()
	{

		delete[] coordinates;
		coordinates = nullptr;
		size = 0;

	}

public:

	Nvector()
	{

		size = 3;
		coordinates = new int[size] {0};

	}

	Nvector(const Nvector& other) 
	{

		copyFrom(other);

	}

	Nvector(int* coordinates, int size) 
	{

		this->coordinates = new int[size];
		this->size = size;

		for (int i = 0; i < size; i++)
		{

			this->coordinates[i] = coordinates[i];

		}

	}

	Nvector& operator = (const Nvector& other) 
	{

		if (this != &other)
		{

			free();
			copyFrom(other);

		}

		return *this;

	}

	Nvector& operator += (const Nvector& other) 
	{
		
		if (size != other.size) throw std::logic_error("Error");

		for (int i = 0; i < size; i++)
		{

			coordinates[i] += other.coordinates[i];

		}

		return *this;

	}

	Nvector& operator -= (const Nvector& other)
	{

		if (size != other.size) throw std::logic_error("Error");

		for (int i = 0; i < size; i++)
		{

			coordinates[i] -= other.coordinates[i];

		}

		return *this;

	}

	Nvector& operator *= (int scalar)
	{

		for (int i = 0; i < size; i++)
		{

			coordinates[i] *= scalar;

		}

		return *this;

	}

	int& operator [] (int index) 
	{

		if (index < 0 || index >= size) throw std::logic_error("Error");

		return coordinates[index];

	}

	const int operator [] (int index) const
	{

		if (index < 0 || index >= size) throw std::logic_error("Error");

		return coordinates[index];

	}

	~Nvector() 
	{

		free();

	}

	double getLen() const 
	{

		int result = 0;

		for (int i = 0; i < size; i++)
		{

			result += coordinates[i] * coordinates[i];

		}

		return std::sqrt(result);

	}

	friend std::ostream& operator << (std::ostream& os, const Nvector& v) 
	{

		os << v.size << std::endl;
		os << '(';

		for (int i = 0; i < v.size; i++)
		{

			os << v.coordinates[i] << ' ';

		}

		os << ')' << std::endl;

		return os;

	}

	friend std::istream& operator >> (std::istream& is, Nvector& v)
	{

		v.free();

		is >> v.size;
		v.coordinates = new int[v.size];

		for (int i = 0; i < v.size; i++)
		{

			is >> v.coordinates[i];

		}

		return is;

	}

};

Nvector operator + (const Nvector& v1, const Nvector& v2) 
{

	Nvector result(v1);
	result += v2;

	return result;

}

Nvector operator - (const Nvector& v1, const Nvector& v2)
{

	Nvector result(v1);
	result -= v2;

	return result;

}

Nvector operator * (const Nvector& v, int scalar)
{

	Nvector result(v);
	result *= scalar;

	return result;

}

Nvector operator * (int scalar, const Nvector& v)
{

	Nvector result(v);
	result *= scalar;

	return result;

}

int main()
{

	int* coords1 = new int[5] {1, 2, 0, 0, 3};
	int* coords2 = new int[5] {-1, 21, 11, 5, 7};

	Nvector v1(coords1, 5);
	Nvector v2(coords2, 5);

	Nvector add = v1 + v2;
	Nvector diff = v1 - v2;

	std::cout << add << diff;

	Nvector v1Copy = v1;
	std::cout << v1Copy;
	v1Copy = v2;
	std::cout << v1Copy;

	delete[] coords1;
	delete[] coords2;

	return 0;

}
