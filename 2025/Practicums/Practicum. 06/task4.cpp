#include <iostream>

namespace HELPERS 
{

	const int MAX_COUNT_OF_COLS = 100;
	const int MAX_COUNT_OF_ROWS = 100;

}

class Matrix 
{
private:

	int** matrix = nullptr;
	int countOfRows = 0;
	int countOfCols = 0;

	void copyFrom(const Matrix& other) 
	{

		countOfRows = other.countOfRows;
		countOfCols = other.countOfCols;

		matrix = new int* [other.countOfRows];

		for (int i = 0; i < countOfRows; i++)
		{

			matrix[i] = new int[other.countOfCols] {0};

		}

		for (int i = 0; i < countOfRows; i++)
		{

			for (int j = 0; j < countOfCols; j++)
			{

				matrix[i][j] = other.matrix[i][j];

			}

		}

	}

	void free() 
	{

		for (int i = 0; i < countOfRows; i++)
		{

			delete[] matrix[i];
			matrix[i] = nullptr;

		}

		delete[] matrix;
		matrix = nullptr;
		countOfRows = 0;
		countOfCols = 0;

	}

public:

	Matrix() 
	{

		countOfRows = 2;
		countOfCols = 2;

		matrix = new int* [countOfRows];

		for (int i = 0; i < countOfRows; i++)
		{

			matrix[i] = new int[countOfCols] {0};

		}

	}

	Matrix(int countOfRows, int countOfCols)
	{

		this->countOfRows = countOfRows;
		this->countOfCols = countOfCols;

		matrix = new int* [countOfRows];

		for (int i = 0; i < countOfRows; i++)
		{

			matrix[i] = new int[countOfCols] {0};

		}

	}

	Matrix(int matrix[][100], int countOfRows, int countOfCols)
	{

		this->countOfRows = countOfRows;
		this->countOfCols = countOfCols;

		this->matrix = new int*[countOfRows];

		for (int i = 0; i < countOfRows; i++)
		{

			this->matrix[i] = new int[countOfCols];

		}

		for (int i = 0; i < countOfRows; i++)
		{

			for (int j = 0; j < countOfCols; j++)
			{

				this->matrix[i][j] = matrix[i][j];

			}

		}

	}

	Matrix(const Matrix& other)
	{

		copyFrom(other);

	}

	Matrix& operator = (const Matrix& other) 
	{

		if (this != &other) 
		{

			free();
			copyFrom(other);

		}

		return *this;

	}

	Matrix& operator += (const Matrix& other) 
	{

		if (countOfRows != other.countOfRows || 
			countOfCols != other.countOfCols) throw std::logic_error("Error");

		for (int i = 0; i < countOfRows; i++)
		{

			for (int j = 0; j < countOfCols; j++)
			{

				matrix[i][j] += other.matrix[i][j];

			}

		}

		return *this;

	}

	Matrix& operator -= (const Matrix& other)
	{

		if (countOfRows != other.countOfRows ||
			countOfCols != other.countOfCols) throw std::logic_error("Error");

		for (int i = 0; i < countOfRows; i++)
		{

			for (int j = 0; j < countOfCols; j++)
			{

				matrix[i][j] -= other.matrix[i][j];

			}

		}

		return *this;

	}

	Matrix& operator *= (const Matrix& other) 
	{

		if(countOfCols != other.countOfRows) throw std::logic_error("Error");

		Matrix newMatrix(countOfRows, other.countOfCols);

		for (int i = 0; i < countOfRows; i++)
		{

			for (int j = 0; j < other.countOfCols; j++)
			{

				newMatrix.matrix[i][j] = 0;

				for (int k = 0; k < countOfCols; k++)
				{

					newMatrix.matrix[i][j] += matrix[i][k] * other.matrix[k][j];

				}

			}

		}

		*this = newMatrix;

		return *this;

	}

	Matrix& operator *= (int scalar)
	{

		for (int i = 0; i < countOfRows; i++)
		{

			for (int j = 0; j < countOfCols; j++)
			{

				matrix[i][j] *= scalar;

			}

		}

		return *this;

	}

	int*& operator [] (int index)
	{

		if (index < 0 || index >= countOfRows) throw std::logic_error("Error");

		return matrix[index];

	}

	const int* operator [] (int index) const
	{

		if (index < 0 || index >= countOfRows) throw std::logic_error("Error");

		return matrix[index];

	}

	~Matrix() 
	{

		free();

	}

	int getCountOfRows() const 
	{

		return countOfRows;

	}

	int getCountOfCols() const
	{

		return countOfCols;

	}

	void printMatrix() const 
	{

		for (int i = 0; i < countOfRows; i++)
		{

			for (int j = 0; j < countOfCols; j++)
			{

				std::cout << matrix[i][j] << " ";

			}

			std::cout << std::endl;

		}

		std::cout << std::endl;

	}

};

Matrix operator + (const Matrix& m1, const Matrix& m2) 
{

	Matrix result(m1);
	result += m2;

	return result;

}

Matrix operator - (const Matrix& m1, const Matrix& m2)
{

	Matrix result(m1);
	result -= m2;

	return result;

}

Matrix operator * (const Matrix& m1, const Matrix& m2)
{

	Matrix result(m1);
	result *= m2;

	return result;

}

Matrix operator * (const Matrix& m, int scalar)
{

	Matrix result(m);
	result *= scalar;

	return result;

}

Matrix operator * (int scalar, const Matrix& m)
{

	Matrix result(m);
	result *= scalar;

	return result;

}

bool operator == (const Matrix& m1, const Matrix& m2) 
{

	if (m1.getCountOfRows() != m2.getCountOfRows() ||
		m1.getCountOfCols() != m2.getCountOfCols()) return false;

	for (int i = 0; i < m1.getCountOfRows(); i++)
	{

		const int* ptr1 = m1[i];
		const int* ptr2 = m2[i];

		for (int j = 0; j < m1.getCountOfCols(); j++)
		{

			if (ptr1[j] != ptr2[j]) return false;

		}

	}

	return true;

}

bool operator != (const Matrix& m1, const Matrix& m2) 
{

	return !(m1 == m2);

}

int main()
{

	int matrix1[HELPERS::MAX_COUNT_OF_ROWS][HELPERS::MAX_COUNT_OF_COLS] =
	{

		{1, 2, 3, 4},
		{1, 1, 1, -41},
		{0, 12, 0, 7}

	};

	int rows1 = 3;
	int cols1 = 4;

	int matrix2[HELPERS::MAX_COUNT_OF_ROWS][HELPERS::MAX_COUNT_OF_COLS] =
	{

		{1},
		{111},
		{17},
		{-3}

	};

	int rows2 = 4;
	int cols2 = 1;

	Matrix m1(matrix1, rows1, cols1);
	Matrix m2(matrix2, rows2, cols2);

	Matrix multiplication = m1 * m2;
	multiplication.printMatrix();

	Matrix m1Copy(m1);
	m1Copy.printMatrix();

	std::cout << (m1Copy == m1) << std::endl << std::endl;

	m1Copy += m1;
	m1Copy.printMatrix();

	return 0;

}
