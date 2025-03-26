#include <iostream>
#pragma once

class Vector
{
private:

	int* array = nullptr;
	int size = 0;
	int capacity = 8;

	void copyFrom(const Vector& other);

	void free();

	void resize(int newCapacity);

	void setArray(int* array, int size);

public:

	Vector();

	Vector(const Vector& other);

	Vector(int* array, int size);

	Vector(int size);

	Vector& operator = (const Vector& other);

	Vector& operator += (const Vector& other);

	Vector& operator -= (const Vector& other);

	Vector& operator *= (double scalar);

	int& operator [] (int index);

	const int operator [] (int index) const;

	friend std::istream& operator >> (std::istream& is, Vector& vector);

	friend std::ostream& operator << (std::ostream& os, const Vector& vector);

	~Vector();

	void push(int number);

	void pop();

	int getSize() const;

	bool isEmpty() const;

};

Vector operator + (const Vector& left, const Vector& right);

Vector operator - (const Vector& left, const Vector& right);

Vector operator * (const Vector& vector, double scalar);

Vector operator * (double scalar, const Vector& vector);
