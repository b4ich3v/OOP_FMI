#include "Shape.h"
#pragma once

constexpr double PI = 3.14;

class Circle: public Shape
{
private:

	double radius = 0;

public:

	Circle(const Point centre[1], double radius);

	bool isInFigure(const Point& point) const override;

	double getArea() const override;

	double getPerimeter() const override;

};

