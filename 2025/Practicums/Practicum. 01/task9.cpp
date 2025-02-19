#include <iostream>

struct Matrix
{
public:

	int rows;
	int cols;
	int** table;

};

void free(Matrix& matrix)
{

	for (int i = 0; i < matrix.rows; i++)
	{

		delete[] matrix.table[i];

	}

	matrix.rows = 0;
	matrix.cols = 0;
	delete[] matrix.table;
	matrix.table = nullptr;

}

void printMatrix(const Matrix& matrix)
{

	for (int i = 0; i < matrix.rows; i++)
	{

		for (int j = 0; j < matrix.cols; j++)
		{

			std::cout << matrix.table[i][j] << " ";

		}

		std::cout << std::endl;

	}

}

void swapPointers(int*& ptr1, int*& ptr2)
{

	int* temp = ptr1;
	ptr1 = ptr2;
	ptr2 = temp;

}

void custumSwap(Matrix& matrix)
{

	if (matrix.rows == 1) return;
	else if (matrix.rows == 2 || matrix.rows == 3) 
	{

		swapPointers(matrix.table[0], matrix.table[matrix.rows - 1]);

	}
	else
	{

		swapPointers(matrix.table[0], matrix.table[matrix.rows - 1]);
		swapPointers(matrix.table[matrix.rows - 2], matrix.table[2]);

	}

}

Matrix transpose(Matrix& matrix)
{

	Matrix result = { matrix.cols, matrix.rows, nullptr };
	result.table = new int* [result.rows];

	for (int i = 0; i < result.rows; i++)
	{

		result.table[i] = new int[result.cols];

	}

	for (int i = 0; i < matrix.rows; i++)
	{

		for (int j = 0; j < matrix.cols; j++)
		{

			result.table[j][i] = matrix.table[i][j];

		}

	}

	free(matrix);
	custumSwap(result);
	return result;

}
