#include <iostream>
#include <cstring>
#include <fstream>

template <class T>

class MyCustomVector
{
private:

public:

    T* data = nullptr;
    size_t sizeOfData = 0;
    size_t capacity = 8;

    void free() 
    {

        delete[] data;
        data = nullptr;
        sizeOfData = 0;
        capacity = 8;

    }

    void copyFrom(const MyCustomVector& other) 
    {

        data = new T[other.capacity];
        sizeOfData = other.sizeOfData;
        capacity = other.capacity;

        for (size_t i = 0; i < sizeOfData; i++) data[i] = other.data[i];

    }

    void moveTo(MyCustomVector&& other) 
    {

        data = other.data;
        sizeOfData = other.sizeOfData;
        capacity = other.capacity;

        other.data = nullptr;
        other.sizeOfData = 0;
        other.capacity = 8;

    }

    void resize(size_t newCapacity) 
    {

        if (newCapacity <= capacity) return;
        if (newCapacity < 1) newCapacity = 1;

        T* newData = new T[newCapacity]{};

        for (size_t i = 0; i < sizeOfData; i++) newData[i] = data[i];

        delete[] data;
        data = newData;
        capacity = newCapacity;

    }

public:

    MyCustomVector() 
    {

        capacity = 8;
        sizeOfData = 0;
        data = new T[capacity]{};

    }

    MyCustomVector(const T* data, size_t sizeOfData) 
    {

        data = new T[capacity];
        for (size_t i = 0; i < sizeOfData; i++) this->data[i] = data[i];

    }

    MyCustomVector(const MyCustomVector& other) 
    {

        copyFrom(other);

    }

    MyCustomVector(MyCustomVector&& other) noexcept 
    {

        moveTo(std::move(other));

    }

    MyCustomVector& operator = (const MyCustomVector& other) 
    {

        if (this != &other)
        {

            free();
            copyFrom(other);

        }

        return *this;

    }

    MyCustomVector& operator = (MyCustomVector&& other) noexcept 
    {

        if (this != &other)
        {

            free();
            moveTo(std::move(other));

        }

        return *this;

    }

    ~MyCustomVector() 
    {

        free();

    }

    const T& operator [] (size_t index) const 
    {

        if (index < 0 || index >= sizeOfData) throw std::out_of_range("Vector index out of range");
        return data[index];

    }

    T& operator [] (size_t index) 
    {

        if (index < 0 || index >= sizeOfData) throw std::out_of_range("Vector index out of range");
        return data[index];

    }

    void pop_back() 
    {

        if (!sizeOfData) throw std::out_of_range("pop_back() on empty Vector");
        sizeOfData -= 1;

    }

    void push_back(const T& element) 
    {

        if (sizeOfData >= capacity) resize(capacity * 2);
        data[sizeOfData++] = element;

    }

    void push_back(T&& element) noexcept 
    {

        if (sizeOfData >= capacity) resize(capacity * 2);
        data[sizeOfData++] = std::move(element);

    }

    size_t getSize() const 
    {

        return sizeOfData;

    }

};

class Statistics 
{
private:

    MyCustomVector<double> stats;

public:

    Statistics() = default;

    Statistics(const double* arr, size_t size): stats(arr, size) {}

    void load(const char* fileName) 
    {

        std::ifstream file(fileName);
        if (!file.is_open()) return;

        double currentNumber = 0;
        MyCustomVector<double> newStats;

        while (true) 
        {

            file >> currentNumber;
            if (file.eof()) break;

            newStats.push_back(currentNumber);

        }

        stats = newStats;
        file.close();

    }

    void write(const char* fileName) const
    {

        std::ofstream file(fileName);
        if (!file.is_open()) return;

        double currentNumber = 0;

        for (int i = 0; i < stats.getSize(); i++)
        {

            file << stats[i] << " ";

        }

        file.close();

    }

    void print() const 
    {

        for (int i = 0; i < stats.getSize(); i++)
        {

            std::cout << stats[i] << " ";

        }

        std::cout << std::endl;

    }

};

int main() 
{

    //double arr[5] = { 1, 2 , 3 ,4 ,5 };
    //std::ofstream file("file.txt");
    //for (int i = 0; i < 5; i++) file << arr[i] << " ";

    Statistics st;
    st.load("file.txt");
    st.print();
    st.write("result.txt");

	return 0;

}

