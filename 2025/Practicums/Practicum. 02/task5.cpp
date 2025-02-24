#include <iostream>
#include <fstream>

struct Point
{
public:

	int x;
	int y;

};

struct Triangle
{
public:

	Point p1;
	Point p2;
	Point p3;

};

int getCountOfLines(std::ifstream& file)
{

	int counter = 0;
	char buffer[1024];

	while (true)
	{

		file.getline(buffer, 1024);
		counter += 1;

		if (file.eof()) break;

	}

	file.seekg(0, std::ios::beg);
	file.clear();

	return counter;

}

void writePointToFile(const Point& p1, std::ofstream& file)
{

	file << p1.x;
	file << p1.y;
	file << " ";

}

void writeTriangleToFile(const Triangle& tr, std::ofstream& file)
{

	writePointToFile(tr.p1, file);
	writePointToFile(tr.p2, file);
	writePointToFile(tr.p3, file);
	file << " ";

}

void writeTrianglesToFile(Triangle* triangles, int size, const char* fileName)
{

	std::ofstream file(fileName);

	if (!file.is_open()) return;

	for (int i = 0; i < size; i++)
	{

		writeTriangleToFile(triangles[i], file);

	}

	file.close();

}

Point readPoint(std::ifstream& file)
{

	int number = 0;
	file >> number;

	int newX = number / 10;
	int newY = number % 10;

	file.clear();
	return { newX, newY };

}

Triangle readTriangle(std::ifstream& file)
{

	Triangle result;

	result.p1 = readPoint(file);
	result.p2 = readPoint(file);
	result.p3 = readPoint(file);

	return result;

}

Triangle* readTrianglesFromFile(const char* fileName, int& size)
{

	std::ifstream file(fileName);

	if (!file.is_open()) return nullptr;

	size = getCountOfLines(file);
	Triangle* result = new Triangle[size];

	for (int i = 0; i < size; i++)
	{

		result[i] = readTriangle(file);

	}

	file.close();
	return result;

}

void printPoint(const Point& p)
{

	std::cout << "(";
	std::cout << p.x << "," << p.y;
	std::cout << ")";
	std::cout << " ";

}

void printTriangle(const Triangle& tr)
{

	printPoint(tr.p1);
	printPoint(tr.p2);
	printPoint(tr.p3);
	std::cout << std::endl;

}

void printTriangles(Triangle* triangles, int size)
{

	for (int i = 0; i < size; i++)
	{

		printTriangle(triangles[i]);

	}

}

int main()
{

	int inputSize = 0;
	std::cin >> inputSize;

	int size = inputSize / 3;
	int index = 0;
	int counter = 0;

	Point* points = new Point[inputSize];
	Triangle* triangles = new Triangle[size];
	Point fictivePoint = { 0,0 };

	for (int i = 0; i < inputSize; i++)
	{

		std::cin >> fictivePoint.x >> fictivePoint.y;
		points[i] = fictivePoint;

		if(counter == 0) triangles[index].p1 = points[counter];
		else if(counter == 1) triangles[index].p2 = points[counter];
		else if(counter == 2) triangles[index].p3 = points[counter];
		else
		{

			counter = 0;
			index += 1;

		}

		counter += 1;

	}

	int fictiveSize = 0;

	std::cout << std::endl;
	printTriangles(triangles, size);
	std::cout << std::endl;

	writeTrianglesToFile(triangles, size, "../test1.txt");
	Triangle* result = readTrianglesFromFile("../test1.txt", fictiveSize);

	printTriangles(result, size);

	delete[] result;
	delete[] points;
	delete[] triangles;

	return 0;

}
