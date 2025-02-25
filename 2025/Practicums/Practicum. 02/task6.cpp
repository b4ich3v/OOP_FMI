#include <iostream>
#include <fstream>

const double EPSILON = 1e-9;

struct Vector
{
public:

	int x;
	int y;
	int z;

};

struct VectorSpace
{
public:

	Vector vectors[50];
	int countOfVectors;

};

int gcd(int number1, int number2)
{

	int size = std::min(std::abs(number1), std::abs(number2));

	for (int i = 2; i <= size; i++)
	{

		if ((number1 % i == 0) && (number2 % i == 0)) return i;

	}

	return 1;

}

int getCountOfVectors(std::ifstream& file)
{

	int counter = 0;
	int number = 0;

	while (file >> number) counter += 1;
	counter /= 3;

	file.clear();
	file.seekg(0, std::ios::beg);
	return counter;

}

Vector makeVector()
{

	Vector result;
	std::cin >> result.x >> result.y >> result.z;

	return result;

}

void addVector(VectorSpace& space, const Vector& v)
{

	if (space.countOfVectors == 50) return;

	space.vectors[space.countOfVectors] = v;
	space.countOfVectors += 1;

}

void serializeVector(const Vector& v, std::ofstream& file)
{

	file << v.x << " ";
	file << v.y << " ";
	file << v.z << " ";

}

void serializeVectorSpace(const VectorSpace& space, const char* fileName)
{

	std::ofstream file(fileName);

	if (!file.is_open()) return;

	for (int i = 0; i < space.countOfVectors; i++)
	{

		serializeVector(space.vectors[i], file);

	}

	file.close();

}

Vector deserializeVector(std::ifstream& file)
{

	Vector result;
	file >> result.x >> result.y >> result.z;

	return result;

}

VectorSpace deserializeVectorSpace(const char* fileName)
{

	std::ifstream file(fileName);

	if (!file.is_open()) return {};

	VectorSpace result;
	result.countOfVectors = getCountOfVectors(file);

	for (int i = 0; i < result.countOfVectors; i++)
	{

		result.vectors[i] = deserializeVector(file);

	}

	file.close();
	return result;

}

void printVector(const Vector& v)
{

	std::cout << "(";
	std::cout << v.x << "," << v.y << "," << v.z;
	std::cout << ")";

}

void printVectorSpace(const VectorSpace& space)
{

	std::cout << "{ ";

	for (int i = 0; i < space.countOfVectors; i++)
	{

		printVector(space.vectors[i]);
		std::cout << " ";

	}

	std::cout << "}" << std::endl;

}

int getPower2OfLen(const Vector& v)
{

	return v.x * v.x + v.y * v.y + v.z * v.z;

}

void sortVectorSpace(VectorSpace& space)
{

	for (int i = 0; i < space.countOfVectors - 1; i++)
	{

		for (int j = 0; j < space.countOfVectors - i - 1; j++)
		{

			if (getPower2OfLen(space.vectors[j]) > getPower2OfLen(space.vectors[j + 1]))
			{

				std::swap(space.vectors[j], space.vectors[j + 1]);

			}

		}

	}

}

bool linearDependant(const VectorSpace& space, int i, int j)
{

	if (i < 0 || j < 0 || i >= space.countOfVectors || j >= space.countOfVectors || i == j) return false;

	Vector v1 = space.vectors[i];
	Vector v2 = space.vectors[j];

	Vector crossProduct = { v1.y * v2.z - v1.z * v2.y,
							v1.z * v2.x - v1.x * v2.z,
							v1.x * v2.y - v1.y * v2.x };

	return (std::abs(crossProduct.x) < EPSILON &&
		std::abs(crossProduct.y) < EPSILON &&
		std::abs(crossProduct.z) < EPSILON);

}

bool linearNonDependant(const VectorSpace& space, int i, int j)
{

	return !linearDependant(space, i, j);

}

int scalarMultiplication(const Vector& v1, const Vector& v2)
{

	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;

}

Vector vectorMultiplication(const Vector& v1, const Vector& v2)
{

	Vector result;

	result.x = v1.y * v2.z - v1.z * v2.y;
	result.y = -v1.x * v2.z + v1.z * v2.x;
	result.z = v1.x * v2.y - v1.y * v2.x;

	return result;

}

int mixedMultiplication(const Vector& v1, const Vector& v2, const Vector& v3)
{

	return scalarMultiplication(v1, vectorMultiplication(v2, v3));

}

void simplifyVector(Vector& v)
{

	int GCD = gcd(v.x, gcd(v.y, v.z));
	v.x /= GCD;
	v.y /= GCD;
	v.z /= GCD;

}

void printBasis(const VectorSpace& space)
{

	VectorSpace LND;
	bool* usedIndexes = new bool[space.countOfVectors];
	int index = 0;

	for (int i = 0; i < space.countOfVectors; i++)
	{

		bool isIndependent = true;

		for (int j = 0; j < space.countOfVectors; j++)
		{

			if (!usedIndexes[i] && !usedIndexes[j] && linearDependant(space, i, j))
			{

				isIndependent = false;
				usedIndexes[i] = true;
				usedIndexes[j] = true;
				break;

			}

		}

		if (isIndependent)
		{

			LND.vectors[index] = space.vectors[i];
			index += 1;

		}

	}

	LND.countOfVectors = index;

	for (int i = 0; i < LND.countOfVectors - 2; i++)
	{

		for (int j = i + 1; j < LND.countOfVectors - 1; j++)
		{

			for (int k = j + 1; k < LND.countOfVectors; k++)
			{

				simplifyVector(LND.vectors[i]);
				simplifyVector(LND.vectors[j]);
				simplifyVector(LND.vectors[k]);

				printVector(LND.vectors[i]);
				std::cout << " ";
				printVector(LND.vectors[j]);
				std::cout << " ";
				printVector(LND.vectors[k]);
				std::cout << std::endl;

			}

		}

	}

	delete[] usedIndexes;

}

int main()
{

	Vector v1 = { 1, 1, 1 };
	Vector v2 = { 1 , 2, -3 };
	Vector v3 = { -1 , 2, 11 };
	Vector v4 = { 2 , 4, -6 };
	Vector v5 = { -1 , 34, -6 };
	Vector v6 = { 3 , 18, -6 };

	VectorSpace space = { {v1, v2, v3, v4, v5, v6}, 6 };

	serializeVectorSpace(space, "../test1.txt");
	VectorSpace newSpace = deserializeVectorSpace("../test1.txt");

	printVectorSpace(newSpace);
	sortVectorSpace(newSpace);
	printVectorSpace(newSpace);
	std::cout << std::endl;

	int scalarProduct = scalarMultiplication(v1, v3);
	std::cout << scalarProduct << std::endl;

	Vector vectorProduct = vectorMultiplication(v1, v3);
	printVector(vectorProduct);
	std::cout << std::endl;

	int mixedProduct = mixedMultiplication(v1, v2, v2);
	std::cout << mixedProduct << std::endl;

	std::cout << std::endl;
	printBasis(space);
	std::cout << std::endl;

	if (linearDependant(space, 1, 3)) std::cout << "Yes";
	else std::cout << "No";

	return 0;

}
