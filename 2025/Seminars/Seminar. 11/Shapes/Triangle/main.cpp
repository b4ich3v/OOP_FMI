#include <iostream>
#include <vector>
#include "Triangle.h"

int main() 
{

	Point p1 = { 0 ,0 };
	Point p2 = { 6 ,0 };
	Point p3 = { 6 ,4 };

	Point ps1[3] = { p1, p2, p3 };

	Triangle tr(ps1);
	std::cout << tr.getArea() << " " << tr.getPerimeter() << std::endl;


	return 0;

}
