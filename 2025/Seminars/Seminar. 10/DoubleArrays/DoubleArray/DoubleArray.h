#include <iostream>
#pragma once

class DoubleArray
{
private:

	double* array = nullptr;
	int size = 0;
	int capacity = 8;

	void copyFrom(const DoubleArray& other);

	void free();

	void moveTo(DoubleArray&& other);

	void resize(int newCapacity);

	void setArray(double* array, int size);

public:

	DoubleArray();

	DoubleArray(const DoubleArray& other);

	DoubleArray(DoubleArray&& other) noexcept;

	DoubleArray(double* array, int size);

	DoubleArray& operator = (const DoubleArray& other);

	DoubleArray& operator = (DoubleArray&& other) noexcept;

	DoubleArray(int size);

	~DoubleArray();

	bool isEmpty() const;

	int getSize() const;

	double& operator [] (int index);

	const double operator [] (int index) const;

	friend bool operator == (const DoubleArray& arr1, const DoubleArray& arr2);

	friend bool operator != (const DoubleArray& arr1, const DoubleArray& arr2);

};

