#include "Circle.h"

Circle::Circle(const Point centre[1], double radius): Shape(centre, 1)
{

	if (radius < 0) throw std::logic_error("Error");

	this->radius = radius;

}

bool Circle::isInFigure(const Point& point) const 
{

	const Point& centre = getPointAt(0);
	return centre.getDistanceBetween(point) < radius;

}

double Circle::getArea() const 
{

	return PI * pow(radius, 2);

}

double Circle::getPerimeter() const 
{

	return 2 * PI * radius;

}
