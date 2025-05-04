#include "Shape.h"
#pragma once

class Rectangle: public Shape
{
public:

	Rectangle(const Point points[4]);

	bool isInFigure(const Point& point) const override;

	double getArea() const override;

	double getPerimeter() const override;

};

