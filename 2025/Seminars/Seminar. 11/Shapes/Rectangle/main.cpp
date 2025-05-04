#include <iostream>
#include <vector>
#include "Rectangle.h"

int main() 
{

	Point p1 = { 0 ,0 };
	Point p2 = { 6 ,0 };
	Point p3 = { 6 ,4 };
	Point p4 = { 0 ,4 };

	Point ps2[4] = { p1, p2, p3, p4 };

	Rectangle rc(ps2);
	std::cout << rc.getArea() << " " << rc.getPerimeter() << std::endl;

	return 0;

}
