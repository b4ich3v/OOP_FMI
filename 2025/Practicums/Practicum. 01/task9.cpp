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
	return result;

}



