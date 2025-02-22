#include <iostream>
#include <fstream>
#include <cstring>

enum class Major
{

	SI = 0,
	KN = 1,
	None = 2

};

struct Student
{
public:

	char name[10] = "None";
	int id = 0;
	Major major = Major::None;

};

int getFileSize(std::ifstream& file)
{

	int counter = 0;
	char buffer[1024];

	while (true)
	{

		file.getline(buffer, 1024);
		counter += 1;

		if (file.eof()) break;

	}

	file.clear();
	file.seekg(0, std::ios::beg);
	return counter;

}

int stringToInt(const char* number)
{

	int iter = 1;
	int size = strlen(number);

	for (int i = 1; i < size; i++)
	{

		iter *= 10;

	}

	int result = 0;

	while (*number != '\0')
	{

		result += iter * (*number - '0');
		iter /= 10;
		number += 1;

	}

	return result;

}

Student parseStudent(const char* data)
{

	if (!data) return {};

	Student result;
	int counter = 0;
	const char* helper = data;

	while (*data != '\0')
	{

		if (*data == ' ')
		{

			strncpy(result.name, helper, counter);
			result.name[counter] = '\0';
			break;

		}

		counter += 1;
		data += 1;

	}

	counter = 0;
	data += 1;
	helper = data;

	while (*data != '\0')
	{

		if (*data == ' ')
		{

			char* number = new char[counter + 1];
			strncpy(number, helper, counter);
			number[counter] = '\0';
			result.id = stringToInt(number);
			delete[] number;

			break;

		}

		counter += 1;
		data += 1;

	}

	data += 1;

	switch (*data)
	{

	case '0': result.major = Major::SI; break;
	case '1': result.major = Major::KN; break;
	default: result.major = Major::None; break;

	}

	return result;

}

Student* readFromFile(std::ifstream& file, int& size)
{

	if (!file.is_open()) return {};

	size = getFileSize(file);
	Student* result = new Student[size];

	char buffer[1024];
	int currentIndex = 0;

	while (true)
	{

		file.getline(buffer, 1024);
		result[currentIndex] = parseStudent(buffer);
		currentIndex += 1;

		if (file.eof()) break;

	}

	file.close();
	return result;

}

void writeStudent(std::ofstream& file, Student st)
{

	file << st.name << " ";
	file << st.id << " ";
	file << (int)st.major << " ";
	file << std::endl;

}

void writeToFile(std::ofstream& file, Student* students, int size)
{

	if (!students || size <= 0 || !file.is_open()) return;

	for (int i = 0; i < size; i++)
	{

		writeStudent(file, students[i]);

	}

	file.close();

}


int main()
{

	std::ifstream file1("../test1.txt");
	std::ofstream file2("../test2.txt");

	int size = 0;
	Student* students = readFromFile(file1, size);

	writeToFile(file2, students, size);

	delete[] students;
	return 0;

}
