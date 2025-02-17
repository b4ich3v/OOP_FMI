#include <iostream>

struct Point
{
public:

	int x;
	int y;

};

Point readPoint()
{

	Point result;
	std::cin >> result.x >> result.y;

	return result;

}

void printPoint(const Point& point)
{

	std::cout << "(" << point.x << "," << point.y << ")" << " ";

}

int getDistanceFromCent(const Point& point)
{

	return sqrt(point.x * point.x + point.y * point.y);

}

int getDistanceBetweenTwo(const Point& point1, const Point& point2)
{

	int dist1 = point1.x - point2.x;
	int dist2 = point1.y - point2.y;

	return sqrt(dist1 * dist1 + dist2 * dist2);

}

struct Triangle 
{
public:

	Point p1;
	Point p2;
	Point p3;

};

Triangle readTriangle()
{

	Triangle result;
	result.p1 = readPoint();
	result.p2 = readPoint();
	result.p3 = readPoint();

	return result;

}

void printTriangle(const Triangle& triangle)
{

	printPoint(triangle.p1);
	printPoint(triangle.p2);
	printPoint(triangle.p3);

}

int getArea(const Triangle& triangle)
{

	int A = getDistanceBetweenTwo(triangle.p1, triangle.p2);
	int B = getDistanceBetweenTwo(triangle.p1, triangle.p3);
	int C = getDistanceBetweenTwo(triangle.p3, triangle.p2);
	int semiPerimetur = 0.5 * (A + B + C);

	return sqrt((semiPerimetur - A) * (semiPerimetur - B) * (semiPerimetur - C));

}

int getPerimetur(const Triangle& triangle)
{

	int A = getDistanceBetweenTwo(triangle.p1, triangle.p2);
	int B = getDistanceBetweenTwo(triangle.p1, triangle.p3);
	int C = getDistanceBetweenTwo(triangle.p3, triangle.p2);

	return A + B + C;

}

void checkTriangle(const Triangle& triangle) 
{

	int A = getDistanceBetweenTwo(triangle.p1, triangle.p2);
	int B = getDistanceBetweenTwo(triangle.p1, triangle.p3);
	int C = getDistanceBetweenTwo(triangle.p3, triangle.p2);

	if (A == B && B == C) 
	{

		std::cout << "Equivalence";
		return;

	}
	else if ((A == B && B != C) ||
			 (B == C && C != A) ||
			 (A == C && C != B))
	{

		std::cout << "Isosceles";
		return;

	}
	else 
	{

		std::cout << "Versatile";
		return;

	}

	std::cout << "Error";

}

void sortTriangles(Triangle* triangles, int size)
{

	for (int i = 0; i < size - 1; i++)
	{

		for (int j = 0; j < size - i - 1; j++)
		{

			if (getArea(triangles[i]) > getArea(triangles[j]))
			{

				std::swap(triangles[i], triangles[j]);

			}

		}

	}

}
