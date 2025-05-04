#include "Rectangle.h"

Rectangle::Rectangle(const Point points[4]): Shape(points, 4) 
{

	const Point& A = getPointAt(0);
	const Point& B = getPointAt(1);
	const Point& C = getPointAt(2);
	const Point& D = getPointAt(3);

	VectorAnalizator AB(A, B);
	VectorAnalizator BC(B, C);
	VectorAnalizator CD(C, D);
	VectorAnalizator DA(D, A);

	if ((AB * BC) || (BC * CD) || (CD * DA) || (AB * DA)) throw std::logic_error("Error");

}

bool Rectangle::isInFigure(const Point& point) const 
{

	const Point& A = getPointAt(0);
	const Point& B = getPointAt(1);
	const Point& C = getPointAt(2);
	const Point& D = getPointAt(3);

	double AB = A.getDistanceBetween(B);
	double BC = B.getDistanceBetween(C);
	double CD = C.getDistanceBetween(D);
	double DA = D.getDistanceBetween(A);

	double AP = A.getDistanceBetween(point);
	double BP = B.getDistanceBetween(point);
	double CP = C.getDistanceBetween(point);
	double DP = D.getDistanceBetween(point);

	return (AB < AP + BP) && (BC < BP + CP) && (CD < DP + CP) && (DA < AP + DP);

}

double Rectangle::getArea() const 
{

	const Point& A = getPointAt(0);
	const Point& B = getPointAt(1);
	const Point& C = getPointAt(2);

	double AB = A.getDistanceBetween(B);
	double BC = B.getDistanceBetween(C);

	return (AB * BC) / 2;

}

double Rectangle::getPerimeter() const 
{

	const Point& A = getPointAt(0);
	const Point& B = getPointAt(1);
	const Point& C = getPointAt(2);
	const Point& D = getPointAt(3);

	double AB = A.getDistanceBetween(B);
	double BC = B.getDistanceBetween(C);
	double CD = C.getDistanceBetween(D);
	double DA = D.getDistanceBetween(A);

	return AB + BC + CD + DA;

}
