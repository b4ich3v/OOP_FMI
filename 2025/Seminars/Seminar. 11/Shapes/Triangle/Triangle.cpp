#include "Triangle.h"

Triangle::Triangle(const Point points[3]): Shape(points, 3) {}

bool Triangle::isInFigure(const Point& point) const
{

	const Point& A = getPointAt(0);
	const Point& B = getPointAt(1);
	const Point& C = getPointAt(2);

	double AB = A.getDistanceBetween(B);
	double BC = B.getDistanceBetween(C);
	double AC = A.getDistanceBetween(C);

	double AP = A.getDistanceBetween(point);
	double BP = B.getDistanceBetween(point);
	double CP = C.getDistanceBetween(point);

	return (AB < AP + BP) && (BC < BP + CP) && (AC < AP + CP);

}

double Triangle::getArea() const 
{

	const Point& A = getPointAt(0);
	const Point& B = getPointAt(1);
	const Point& C = getPointAt(2);

	double AB = A.getDistanceBetween(B);
	double BC = B.getDistanceBetween(C);
	double AC = A.getDistanceBetween(C);

	double semiPer = 0.5 * (AB + BC + AC);

	return sqrt(semiPer * (semiPer - AB) * (semiPer - BC) * (semiPer - AC));

}

double Triangle::getPerimeter() const 
{

	const Point& A = getPointAt(0);
	const Point& B = getPointAt(1);
	const Point& C = getPointAt(2);

	double AB = A.getDistanceBetween(B);
	double BC = B.getDistanceBetween(C);
	double AC = A.getDistanceBetween(C);

	return AB + BC + AC;

}
