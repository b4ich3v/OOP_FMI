#include <iostream>
#include "Matrix.hpp"

int main()
{

	Vector<int> v1;
	for (int i = 0; i < 5; i++) v1.push_back(i);

	Vector<Vector<int>> inputMatrix;
	for (int i = 0; i < 5; i++) inputMatrix.push_back(v1);

	Matrix<int> matrix(inputMatrix, 5, 5);
	
	for (int i = 0; i < 5; i++)
	{

		for (int j = 0; j < 5; j++)
		{

			std::cout << matrix.getAt(i ,j) << " ";

		}

		std::cout << std::endl;

	}

	matrix.setAt(0, 0, 100);
	matrix.transpose();
	std::cout << std::endl;

	for (int i = 0; i < 5; i++)
	{

		for (int j = 0; j < 5; j++)
		{

			std::cout << matrix.getAt(i, j) << " ";

		}

		std::cout << std::endl;

	}

	return 0;

}

