#include <iostream>
#include <vector>
#include "Circle.h"

int main() 
{

	Point p1 = { 0 ,0 };

	Point ps3[1] = { p1};

	Circle cr(ps3, 3.75);
	std::cout << cr.getArea() << " " << cr.getPerimeter() << std::endl;

	return 0;

}
