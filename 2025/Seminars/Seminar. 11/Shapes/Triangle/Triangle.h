#include "Shape.h"
#pragma once

class Triangle: public Shape
{
public:

	Triangle(const Point points[3]);

	bool isInFigure(const Point& point) const override;

	double getArea() const override;

	double getPerimeter() const override;

};

