#include <iostream>

class SwapCounter
{
private:

	static int count;

public:

	static void swap(int& a, int& b)
	{

		int temp = a;
		a = b;
		b = temp;
		count++;

	}

	static int getCount()
	{

		return count;

	}

	static void resetCount()
	{

		count = 0;

	}

};

int SwapCounter::count = 0;

void print(const int* array, int size)
{

	for (int i = 0; i < size; i++)
	{

		std::cout << array[i] << " ";

	}
		
	std::cout << std::endl;

}

void bubbleSort(int* array, int size)
{

	for (int i = 0; i < size - 1; i++)
	{

		for (int j = 0; j < size - 1 - i; j++)
		{

			if (array[j + 1] < array[j])
			{

				SwapCounter::swap(array[j], array[j + 1]);
				
			}

		}

	}

}

void selectionSort(int* array, int size)
{

	for (int i = 0; i < size - 1; i++)
	{

		int minElIndex = i;

		for (int j = i + 1; j < size; j++)
		{

			if (array[j] < array[minElIndex])
			{

				minElIndex = j;

			}
				
		}

		if (minElIndex != i)
		{

			SwapCounter::swap(array[minElIndex], array[i]);

		}
			
	}

}

int main()
{

	{

		int array[10] = { 10,9,8,7,6,5,4,3,2,1 };
		bubbleSort(array, 10);
		std::cout << "Bubble sort swaps: " << SwapCounter::getCount() << std::endl;

	}

	{

		SwapCounter::resetCount();
		int array[10] = { 10,9,8,7,6,5,4,3,2,1 };
		selectionSort(array, 10);
		std::cout << "Selection sort swaps: " << SwapCounter::getCount() << std::endl;


	}

	return 0;

}
