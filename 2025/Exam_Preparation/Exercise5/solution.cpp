#include <iostream>
#include <cstring>
#include <cmath>

struct Point 
{
public:

    double x = 0;
    double y = 0;

    Point(double x, double y): x(x), y(y) {}

    double getDistanceBetween(const Point& point) const
    {

        return sqrt(pow(x - point.x, 2) + pow(y - point.y, 2));

    }

};

class Circle
{
private:

    Point centre = { 0, 0 };
    double radius = 0;

public:

    Circle(): centre(0,0), radius(1) {}

    Circle(const Point& centre, double radius): centre(centre), radius(radius) {}

    Circle(const Point& p1, const Point& p2) 
    {

        centre = p1;
        radius = p1.getDistanceBetween(p2);

    }

    Circle operator += (const Circle& other) 
    {

        Point newCentre(centre.x + other.centre.x, centre.y + other.centre.y);
        double newRadius = radius + other.radius;

        Circle result(newCentre, newRadius);
        *this = result;

        return *this;

    }

    bool isIn(const Point& point) const 
    {

        if (point.getDistanceBetween(point) <= radius) return true;
        return false;

    }

    bool isIn(double x, double y) const
    {

        return isIn(Point(x, y));

    }

    friend bool operator == (const Circle& c1, const Circle& c2)
    {

        return ((c1.centre.x == c2.centre.x) && (c1.centre.y == c2.centre.y) 
            && (c1.radius == c2.radius));

    }

    friend bool operator != (const Circle& c1, const Circle& c2)
    {

        return !(c1 == c2);

    }

    friend bool operator < (const Circle& c1, const Circle& c2)
    {

        double centreDist = c1.centre.getDistanceBetween(c2.centre);
        return centreDist + c1.radius <= c2.radius;

    }

    friend bool operator > (const Circle& c1, const Circle& c2)
    {

        double centreDist = c1.centre.getDistanceBetween(c2.centre);
        return centreDist + c1.radius > c2.radius;

    }

    friend bool operator >= (const Circle& c1, const Circle& c2)
    {

        return !(c1 < c2);

    }

    friend bool operator <= (const Circle& c1, const Circle& c2)
    {

        return !(c1 > c2);

    }

};

Circle operator + (const Circle& c1, const Circle& c2)
{

    Circle result(c1);
    result += c2;

    return result;

}

int main() 
{

    Circle c1;                       
    Circle c2(Point(0, 0), 1);       

    std::cout << (c1 == c2) << std::endl;
    std::cout << (c1 != c2) << std::endl << std::endl;

    Circle c3(Point(1, 1), Point(4, 5));  
    Circle c4(Point(2, 2), 2.5);         

    std::cout << c3.isIn(1, 6) << std::endl;
    std::cout << c3.isIn(4, 5) << std::endl << std::endl;

    Circle sum1 = c1 + c4;  
    Circle expect1(Point(2, 2), 3.5);
    std::cout << (sum1 == expect1) << std::endl;

    c1 += c3;              
    Circle expect2(Point(1, 1), 6);
    std::cout << (c1 == expect2) << std::endl << std::endl;

    std::cout << (c4 < c3) << std::endl;  
    std::cout << (c3 > c4) << std::endl;
    std::cout << (c4 <= c3) << std::endl;
    std::cout << (c4 >= c3) << std::endl << std::endl;

    return 0;

}

