#include <iostream>
#include <stdexcept>
#include <utility>

struct Point 
{
public:

    double x = 0;
    double y = 0;

    Point() = default;

    Point(double x, double y) : x(x), y(y) {}

};

class PointArray 
{
private:

    Point* data = nullptr;
    int size = 0;

    void free()
    {

        delete[] data;
        data = nullptr;
        size = 0;

    }

    void copyFrom(const PointArray& other) 
    {

        size = other.size;
        data = new Point[size];

        for (int i = 0; i < size; i++)
        {

            data[i] = other.data[i];

        }

    }

public:

    PointArray() = default;

    PointArray(const Point* array, int newSize) 
    {

        if (newSize < 0) throw std::logic_error("Error");

        size = newSize;
        data = new Point[size];

        for (int i = 0; i < size; i++)
        {

            data[i] = array[i];

        }

    }

    PointArray(const PointArray& other) 
    {

        copyFrom(other);

    }

    PointArray(PointArray&& other) noexcept 
    {

        data = other.data;
        size = other.size;
        other.data = nullptr;
        other.size = 0;

    }

    PointArray& operator = (const PointArray& other)
    {

        if (this != &other)
        {

            free();
            copyFrom(other);
        }

        return *this;

    }

    PointArray& operator = (PointArray&& other) noexcept 
    {

        if (this != &other) 
        {

            free();
            data = other.data;
            size = other.size;
            other.data = nullptr;
            other.size = 0;

        }

        return *this;

    }

    ~PointArray() 
    {

        free();

    }

    int getSize() const { return size; }

    void translate(int index, double x, double y)
    {

        if (index < 0 || index >= size)
            throw std::out_of_range("Error");

        data[index].x += x;
        data[index].y += y;

    }

    void addAt(int index, const Point& point) 
    {

        if (index < 0 || index > size)
            throw std::out_of_range("Error");

        Point* newData = new Point[size + 1];

        for (int i = 0; i < index; i++) newData[i] = data[i]; 
        newData[index] = point;
        for (int i = index; i < size; i++) newData[i + 1] = data[i];
            
        delete[] data;
        data = newData;
        size += 1;

    }

    void removeAt(int index) 
    {

        if (index < 0 || index >= size)
            throw std::out_of_range("Error");

        Point* newData = new Point[size - 1];

        for (int i = 0; i < index; i++) newData[i] = data[i];
        for (int i = index + 1; i < size; i++) newData[i - 1] = data[i];

        delete[] data;
        data = newData;
        size -= 1;

    }

    void print() const 
    {

        std::cout << "[ ";

        for (int i = 0; i < size; ++i)
            std::cout << "(" << data[i].x << "," << data[i].y << ") ";

        std::cout << "]" << std::endl;

    }

    friend PointArray concat(const PointArray& array1, const PointArray& array2) 
    {

        PointArray result;
        result.size = array1.size + array2.size;
        result.data = new Point[result.size];

        for (int i = 0; i < array1.size; i++) result.data[i] = array1.data[i];
        for (int i = 0; i < array2.size; i++) result.data[array1.size + i] = array2.data[i];

        return result;

    }

};

int main() 
{
    
    Point pts1[] = { {0,0}, {1,2}, {3,4} };
    Point pts2[] = { {5,5}, {6,7} };

    PointArray A(pts1, 3);
    PointArray B(pts2, 2);

    A.print();
    B.print();

    A.translate(1, 10, -1);
    A.print();

    A.addAt(2, Point(9, 9));
    A.print();

    A.removeAt(0);
    A.print();

    PointArray C = concat(A, B);
    C.print();

    std::cout << A.getSize() << " "
        << B.getSize() << " "
        << C.getSize() << std::endl;

    return 0;

}


