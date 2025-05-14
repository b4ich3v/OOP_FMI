#include <iostream>
#include "MyVector.hpp"

namespace ALGS
{

    template <class T>

    void insertionSort(MyVector<T>& arr)
    {

        for (int i = 1; i < arr.size(); i++)
        {

            int key = arr[i];
            int j = i - 1;

            while (j >= 0 && key > arr[j])
            {

                arr[j + 1] = arr[j];
                j--;

            }

            arr[j + 1] = key;

        }

    }

    template <class T>

    void bubbleSort(MyVector<T>& arr)
    {

        for (int i = 0; i < arr.size() - 1; i++)
        {

            for (int j = 0; j < arr.size() - i - 1; j++)
            {

                if (arr[j] > arr[j + 1]) std::swap(arr[j], arr[j + 1]);

            }

        }

    }

    template <class T>

    void selectionSort(MyVector<T>& arr)
    {

        for (int i = 0; i < arr.size(); i++)
        {

            int minIndex = i;

            for (int j = i + 1; j < arr.size(); j++)
            {

                if (arr[j] < arr[minIndex]) minIndex = j;

            }

            if (i != minIndex) std::swap(arr[i], arr[minIndex]);

        }

    }

}

template <class T>

void sort(MyVector<T>& arr) 
{

    ALGS::bubbleSort(arr);

}

template <>

void sort(MyVector<unsigned int>& arr)
{

    ALGS::bubbleSort(arr);

}

template <>

void sort(MyVector<int>& arr)
{

    ALGS::insertionSort(arr);

}

template <>

void sort(MyVector<double>& arr)
{

    ALGS::selectionSort(arr);

}

template <class T>

void printVector(const MyVector<T>& arr) 
{

    for (int i = 0; i < arr.size(); i++)
    {

        std::cout << arr[i] << " ";

    }

    std::cout << std::endl;

}

int main() 
{
    
    MyVector<int> vi;
    vi.push_back(5);
    vi.push_back(3);
    vi.push_back(8);
    vi.push_back(1);
    vi.push_back(4);

    printVector(vi);
    sort(vi);
    printVector(vi);

    MyVector<unsigned int> vui;
    vui.push_back(20);
    vui.push_back(10);
    vui.push_back(30);
    vui.push_back(15);
    vui.push_back(25);

    printVector(vui);
    sort(vui);
    printVector(vui);

    MyVector<double> vd;
    vd.push_back(3.14);
    vd.push_back(2.71);
    vd.push_back(1.41);
    vd.push_back(0.577);
    vd.push_back(1.618);

    printVector(vd);
    sort(vd);
    printVector(vd);

    return 0;

}
