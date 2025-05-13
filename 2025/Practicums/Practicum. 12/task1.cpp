#include <iostream>
#include "MyVector.hpp"

class MaskContainer
{
public:

    virtual bool member(double x) const = 0;

    virtual double operator [] (size_t index) const = 0;

    virtual void write() const = 0;

    virtual int count() const = 0;

    virtual ~MaskContainer() = default;

};

template <class T>

class Container: public MaskContainer 
{
protected:

    MyVector<T> arr;

    void setData(const MyVector<T>& arr) 
    {

        this->arr = arr;

    }

public:

    Container(): arr() {}

    Container(const MyVector<T>& arr) : arr(arr) {}

    int count() const override 
    {

        return arr.size();

    }

};

class Vector: public Container<double>
{
public:

    Vector(const double* arr, int size) : Container<double>(MyVector<double>(arr, size)) {}

    void write() const override 
    {

        for (int i = 0; i < this->arr.size(); i++)
        {

            std::cout << this->arr[i] << " ";

        }

        std::cout << std::endl;

    }

    double operator [] (size_t index) const override 
    {

        return this->arr[index];

    }

    bool member(double x) const override
    {

        for (int i = 0; i < this->arr.size(); i++)
        {

            if (this->arr[i] == x) return true;

        }

        return false;

    }

};

class Matrix: public Container<MyVector<double>>
{
private:

    int countOfRows = 0;
    int countOfCols = 0;

    int getIndex(int i, int j) const 
    {

        return i * countOfRows + j;

    }

    void calcIndexes(int& i, int& j, int index) const 
    {

        for (int currentRowIndex = 0; currentRowIndex < countOfRows; currentRowIndex++)
        {
                
            for (int currentColIndex = 0; currentColIndex < countOfCols; currentColIndex++)
            {

                if (getIndex(currentRowIndex, currentColIndex) == index) 
                {

                    i = currentRowIndex;
                    j = currentColIndex;
                    return;

                }

            }

        }

        i = -1;
        j = -1;

    }

public:

    Matrix(const double** arr, int countOfRows, int countOfCols) 
    {

        if (arr == nullptr || countOfRows < 0 || countOfCols < 0) throw std::logic_error("Error");

        MyVector<MyVector<double>> matrix;

        this->countOfRows = countOfRows;
        this->countOfCols = countOfCols;
        
        for (int i = 0; i < countOfRows; i++)
        {

            MyVector<double> row;

            for (int j = 0; j < countOfCols; j++)
            {

                row.push_back(arr[i][j]);

            }

            matrix.push_back(row);

        }

        setData(matrix);

    }

    double operator [] (size_t index) const override 
    {

        int i, j = 0;
        calcIndexes(i, j, index);

        if (i == -1 && j == -1) throw std::logic_error("Error");

        return arr[i][j];

    }

    void write() const override 
    {

        for (int i = 0; i < countOfRows; i++)
        {

            for (int j = 0; j < countOfCols; j++)
            {

                int index = getIndex(i, j);
                int iMask, jMask = 0;
                calcIndexes(iMask, jMask, index);

                std::cout << this->arr[iMask][jMask] << " ";

            }

            std::cout << std::endl;

        }

        std::cout << std::endl;

    }

    bool member(double x) const override
    {

        for (int i = 0; i < countOfRows; i++)
        {

            for (int j = 0; j < countOfCols; j++)
            {

                if (this->arr[i][j] == x) return true;

            }

        }

        return false;

    }

};

bool intersection(const MaskContainer** arr, size_t size, double target)
{

    for (size_t i = 0; i < size; i++)
    {

        if (arr[i] != nullptr && !arr[i]->member(target)) 
        {

            return false;

        }

    }

    return true;

}

int main() 
{

    double data[] = { 1.1, 2.2, 3.3 };
    Vector vector(data, 3);

    vector.write();
    std::cout << vector[1] << std::endl;
    std::cout << (vector.member(2.2) ? "yes" : "no") << std::endl;

    double row1[] = {1, 2, 3};
    double row2[] = {4, 5, 6};
    const double* matrixData[] = { row1, row2 };

    Matrix matrix(matrixData, 2, 3);
    matrix.write();

    const MaskContainer* containers[] = { &vector, &matrix };
    bool pred = intersection(containers, 2, 1);
    std::cout << pred << std::endl;
    

    return 0;

}
