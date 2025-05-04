#include <iostream>
#include <cmath>
#pragma once

struct Point 
{
public:

	int x = 0;
	int y = 0;

	double getDistanceBetween(const Point& other) const;

};

struct VectorAnalizator
{
public:

	Point point1;
	Point point2;

	VectorAnalizator(const Point& point1, const Point& point2);

	friend double operator * (const VectorAnalizator& v1, const VectorAnalizator& v2);

};

class Shape
{
private:

	Point* points = nullptr;
	int size = 0;

	void free();

	void copyFrom(const Shape& other);

	void moveTo(Shape&& other);

public:

	Shape();

	Shape(const Point* points, int size);

	Shape(const Shape& other);

	Shape(Shape&& other) noexcept;

	Shape& operator = (const Shape& other);

	Shape& operator = (Shape&& other) noexcept;

	const Point& getPointAt(int index) const;

	virtual ~Shape();

	virtual bool isInFigure(const Point& point) const = 0;

	virtual double getArea() const = 0;

	virtual double getPerimeter() const = 0;

};


