#include <iostream>
#include "nVector.h"

void Nvector::copyFrom(const Nvector& other)
{

	size = other.size;
	data = new int[size];

	for (int i = 0; i < size; i++)
	{

		data[i] = other.data[i];

	}

}

void Nvector::free() 
{

	delete[] data;
	data = nullptr;
	size = 0;

}

Nvector::Nvector()
{

	data = nullptr;
	size = 0;

}

Nvector::Nvector(const Nvector& other) 
{

	copyFrom(other);

}

Nvector::Nvector(int size) 
{

	this->size = size;
	data = new int[size];

}

Nvector& Nvector::operator = (const Nvector& other)
{

	if (this != &other)
	{

		free();
		copyFrom(other);

	}

	return *this;

}

Nvector::~Nvector()
{

	free();

}

Nvector& Nvector::operator += (const Nvector& other)
{

	if (size != other.size) 
	{

		throw std::logic_error("The vectors should have the same size!");

	}

	for (int i = 0; i < size; i++)
	{

		data[i] += other.data[i];

	}

	return *this;

}

Nvector& Nvector::operator -= (const Nvector& other)
{

	if (size != other.size)
	{

		throw std::logic_error("The vectors should have the same size!");

	}

	for (int i = 0; i < size; i++)
	{

		data[i] -= other.data[i];

	}

	return *this;

}

Nvector& Nvector::operator *= (int scalar)
{

	for (int i = 0; i < size; i++)
	{

		data[i] *= scalar;

	}

	return *this;

}

Nvector operator + (const Nvector& lhs, const Nvector& rhs)
{

	Nvector result(lhs);
	result += rhs;

	return result;

}

Nvector operator - (const Nvector& lhs, const Nvector& rhs)
{

	Nvector result(lhs);
	result -= rhs;

	return result;

}

Nvector operator * (const Nvector& rhs, int scalar)
{

	return rhs * scalar;

}

Nvector operator * (int scalar, const Nvector& lhs)
{

	return lhs * scalar;

}

int Nvector::lenOfVector() const
{

	return size;

}

int Nvector::operator [] (int index) const 
{

	if (index >= size || index < 0)
	{

		throw std::logic_error("The vectors should have the same size!");

	}

	return data[index];

}

int& Nvector::operator [] (int index) 
{

	if (index >= size || index < 0)
	{

		throw std::logic_error("The vectors should have the same size!");

	}

	return data[index];

}

bool operator || (const Nvector& lhs, const Nvector& rhs)
{

	if (lhs.lenOfVector() != rhs.lenOfVector())
	{

		return false;

	}

	int specialScalar = lhs[0] / rhs[0];

	for (int i = 0; i < lhs.lenOfVector(); i++)
	{

		if ((lhs[i] / rhs[i]) != specialScalar)
		{

			return false;
			break;

		}

	}

	return true;

}

bool operator |= (const Nvector& lhs, const Nvector& rhs)
{

	if (lhs.lenOfVector() != rhs.lenOfVector())
	{

		return false;

	}

	int dotProduct = 0;

	for (int i = 0; i < lhs.lenOfVector(); i++)
	{

		dotProduct += lhs[i] * rhs[i];

	}

	return dotProduct == 0;

}

std::istream& operator >> (std::istream& is, Nvector& other)
{

	int size = 0;
	is >> size;
	other.free();
	other.size = size;
	other.data = new int[size];

	for (int i = 0; i < size; i++)
	{

		is >> other.data[i];

	}

	return is;

}

std::ostream& operator << (std::ostream& os, const Nvector& vector)
{

	os << vector.lenOfVector();
	os << " ";

	for (int i = 0; i < vector.size; i++) 
	{

		os << vector[i] << " ";

	}
		
	return os;

}
