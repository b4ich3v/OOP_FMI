#include <iostream>
#include <fstream>

void bubbleSort(int* array, int size) 
{

	for (int i = 0; i < size - 1; i++)
	{

		for (int j = 0; j < size - i - 1; j++)
		{

			if (array[j] < array[j + 1]) 
			{ 

				std::swap(array[j], array[j + 1]);

			}

		}

	}

}

int countOfElementsInFile(std::ifstream& file) 
{

	int count = 0;
	int number;

	while (file >> number)
	{

		count++;

	}
	
	file.clear();
	file.seekg(0);
	return count;

}

void mergeSortedNumbers(const char* fileName1, const char* fileName2, const char* fileName3)
{

	std::ifstream file1(fileName1);
	std::ifstream file2(fileName2);
	std::ofstream result(fileName3);

	if (!file1.is_open() || !file2.is_open() || !result.is_open()) 
	{

		std::cout << "Error";
		return;

	}

	int countFile1 = countOfElementsInFile(file1);
	int countFile2 = countOfElementsInFile(file2);
	int size = countFile1 + countFile2;

	std::cout << countFile1 << " " << countFile2;

	int* array = new int[size];

	for (int i = 0; i < countFile1; i++) 
	{

		if (file1.bad()) 
		{

			std::cout << "Error: Reading from file " << fileName1 << " failed." << std::endl;
			delete[] array;
			return;

		}

		file1 >> array[i];

	}

	for (int i = 0; i < countFile2; i++) 
	{

		if (file2.bad()) 
		{

			std::cout << "Error: Reading from file " << fileName2 << " failed." << std::endl;
			delete[] array;
			return;

		}

		file2 >> array[countFile1 + i];

	}

	bubbleSort(array, size);

	for (int i = 0; i < size; i++)
	{

		result << array[i] << " ";

	}

	delete[] array;

	file1.close();
	file2.close();
	result.close();

	return;

}

int main() 
{

	const char first[] = "first.txt";
	const char second[] = "second.txt";
	const char result[] = "result.txt";

	mergeSortedNumbers(first, second, result);

	return 0;

}
