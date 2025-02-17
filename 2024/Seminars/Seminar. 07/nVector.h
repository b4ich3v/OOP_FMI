#pragma once
#include <fstream>

class Nvector
{
private:

	int* data;
	int size;

	void copyFrom(const Nvector& other);

	void free();

public:

	Nvector();

	Nvector(const Nvector& other);

	Nvector(int size);

	Nvector& operator = (const Nvector& other);

	Nvector& operator += (const Nvector& other);

	Nvector& operator -= (const Nvector& other);

	Nvector& operator *= (int scalar);

	~Nvector();

	int lenOfVector() const;

	int operator [] (int index) const;

	int& operator [] (int index);

	friend std::istream& operator >> (std::istream& is, Nvector& other);

	friend std::ostream& operator << (std::ostream& os, const Nvector& other);

};

Nvector operator + (const Nvector& lhs, const Nvector& rhs);

Nvector operator - (const Nvector& lhs, const Nvector& rhs);

bool operator || (const Nvector& lhs, const Nvector& rhs);

bool operator |= (const Nvector& lhs, const Nvector& rhs);
