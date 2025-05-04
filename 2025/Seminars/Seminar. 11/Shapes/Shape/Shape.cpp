#include "Shape.h"

void Shape::free() 
{

	delete[] points;
	points = nullptr;

}

void Shape::copyFrom(const Shape& other) 
{

	this->points = new Point[other.size];
	this->size = other.size;

	for (int i = 0; i < size; i++)
	{

		this->points[i] = other.points[i];
		
	}

}

void Shape::moveTo(Shape&& other) 
{

	this->points = other.points;
	this->size = other.size;

	other.points = nullptr;
	other.size = 0;

}

Shape::Shape() 
{

	this->points = new Point[10];
	this->size = 10;

}

Shape::Shape(const Point* points, int size) 
{

	if (!points || size < 0) throw std::logic_error("Error");

	this->points = new Point[size];
	this->size = size;

	for (int i = 0; i < size; i++)
	{

		this->points[i] = points[i];

	}

}

Shape::Shape(const Shape& other) 
{

	copyFrom(other);

}

Shape::Shape(Shape&& other) noexcept 
{

	moveTo(std::move(other));

}

Shape& Shape::operator = (const Shape& other) 
{

	if (this != &other) 
	{

		free();
		copyFrom(other);

	}

	return *this;

}

Shape& Shape::operator = (Shape&& other) noexcept 
{

	if (this != &other)
	{

		free();
		moveTo(std::move(other));

	}

	return *this;

}

Shape::~Shape()
{

	free();

}

double Point::getDistanceBetween(const Point& other) const 
{

	return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));

}

const Point& Shape::getPointAt(int index) const 
{

	if (index < 0 || index >= size) throw std::logic_error("Error");

	return points[index];

}

VectorAnalizator::VectorAnalizator(const Point& point1, const Point& point2) 
{

	this->point1 = point1;
	this->point2 = point2;

}

double operator * (const VectorAnalizator& v1, const VectorAnalizator& v2) 
{

	double xCoords1 = v1.point2.x - v1.point1.x;
	double yCoords1 = v1.point2.y - v1.point1.y;

	double xCoords2 = v2.point2.x - v2.point1.x;
	double yCoords2 = v2.point2.y - v2.point1.y;

	return xCoords1 * xCoords2 + yCoords1 * yCoords2;

}
