#include "Vector.hpp"
#pragma once

template<class T>

class Matrix 
{
private:

	Vector<Vector<T>> matrix;
	size_t countOfRows = 0;
	size_t countOfCols = 0;

public:

	Matrix();

	Matrix(const Vector<Vector<T>>& matrix, size_t rows, size_t cols);

	void setAt(unsigned int x, unsigned int y, T element);

	const T& getAt(unsigned int x, unsigned int y) const;

	T& getAt(unsigned int x, unsigned int y);

	void transpose();

};

template<class T>

Matrix<T>::Matrix() 
{

	countOfRows = 2;
	countOfCols = 2;

	Vector<Vector<T>> endMatrix(countOfRows);

	for (int i = 0; i < countOfRows; i++)
	{

		for (int j = 0; j < countOfCols; j++)
		{

			endMatrix[i].push_back(0);

		}

	}

	matrix = endMatrix;

}

template<class T>

Matrix<T>::Matrix(const Vector<Vector<T>>& matrix, size_t rows, size_t cols) 
{

	this->matrix = matrix;
	this->countOfRows = rows;
	this->countOfCols = cols;

}

template<class T>

void Matrix<T>::setAt(unsigned int x, unsigned int y, T element) 
{

	if (x < 0 || x >= countOfRows ||
		y < 0 || y >= countOfCols) throw std::logic_error("Error");

	matrix[x][y] = element;

}

template<class T>

const T& Matrix<T>::getAt(unsigned int x, unsigned int y) const 
{

	if (x < 0 || x >= countOfRows ||
		y < 0 || y >= countOfCols) throw std::logic_error("Error");

	return matrix[x][y];

}

template<class T>

T& Matrix<T>::getAt(unsigned int x, unsigned int y) 
{

	if (x < 0 || x >= countOfRows || 
		y < 0 || y >= countOfCols) throw std::logic_error("Error");

	return matrix[x][y];

}

template<class T>

void Matrix<T>::transpose() 
{

	for (int i = 0; i < countOfRows; i++)
	{ 
		
		for (int j = i + 1; j < countOfCols; j++)
		{

			std::swap(matrix[i][j], matrix[j][i]);

		}

	}

}
