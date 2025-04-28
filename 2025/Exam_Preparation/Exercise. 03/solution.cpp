#include <iostream>

class Vector2D 
{
private:

    double x;
    double y;

public:
    
    Vector2D() : x(0), y(0) {}
    
    Vector2D(double x, double y) : x(x), y(y) {}

    Vector2D& operator += (const Vector2D& other)
    {

        x += other.x;
        y += other.y;

        return *this;

    }

    Vector2D operator + (const Vector2D& other) const
    {

        return Vector2D(x + other.x, y + other.y);

    }

    Vector2D operator * (double scalar) const 
    {

        return Vector2D(x * scalar, y * scalar);

    }

    friend Vector2D operator * (double scalar, const Vector2D& v) 
    {

        return v * scalar;

    }

    double operator * (const Vector2D& other) const 
    {

        return x * other.x + y * other.y;

    }

    bool operator == (const Vector2D& other) const
    {

        return x == other.x && y == other.y;

    }

    bool operator != (const Vector2D& other) const 
    {

        return !(*this == other);

    }

    friend std::ostream& operator << (std::ostream& os, const Vector2D& v) 
    {

        os << "(" << v.x << "," << v.y << ")";
        return os;

    }

};

int main() 
{
    
    Vector2D vector1;                
    Vector2D vector2(2, 3);          

    Vector2D vector3 = vector2 * 2.0;      
    Vector2D vector4 = 1.5 * vector2;      

    vector1 += vector2;                    
    Vector2D vector5 = vector1 + vector3;        

    double result = vector2 * vector3;         

    std::cout << vector1 << std::endl;
    std::cout << vector2 << std::endl;
    std::cout << vector3 << std::endl;
    std::cout  << vector4 << std::endl;
    std::cout << vector5 << std::endl;
    std::cout << result << std::endl << std::endl;

    std::cout << (vector1 == vector2) << std::endl;
    std::cout << (vector1 != vector2) << std::endl;

    return 0;

}

