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

	std::cout << "(" << point.x << "," << point.y << ")";

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
