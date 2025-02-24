#include <iostream>
#include <fstream>

//За тази задача използвайте структурите, които написахме предния път -
//Point, Triangle.Напишете програма, която чете масив от точки от стандартния вход,
//след което го записва във файл.След като точките са записани във файла,
//трябва да прочетете същия файл, интерпретиран като масив от триъгълници.
//Ако броят точки не се дели точно на 3, прочетете толкова триъгълници за колкото стигат точките.

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
	file << std::endl;

}

void writeTrianglesToFile(Triangle* triangles, int size, const char* fileName)
{

	std::ofstream file(fileName);

	if (!file.is_open()) return;

	for (int i = 0; i < size; i++)
	{

		writeTriangleToFile(triangles[i], file);

	}

}

Point readPoint(std::ifstream& file)
{

	char data[5];
	file >> data;

	file.clear();
	return { (data[0] - '0'), (data[1] - '0') };

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

	/*Triangle triangles[3] =
	{

		{{0, 0}, {0, 1}, {1, 0}},
		{{0, 0}, {0, 2}, {2, 0}},
		{{0, 0}, {0, 3}, {3, 0}}

	};

	writeTrianglesToFile(triangles, 3, "../test1.txt");*/

	int size = 0;
	Triangle* triangles = readTrianglesFromFile("../test1.txt", size);

	printTriangles(triangles, size);
	delete[] triangles;

	return 0;

}
